#define USE_FILE_IO
// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <stack>
#include <string>
#include <random>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

#ifndef USE_FILE_IO
#include <iostream>
using std::cin;
using std::cout;
#else
static ifstream cin("tree.in");
static ofstream cout("tree.out");
#endif  // IFNDEF USE_FILE_IO

inline void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
};

static random_device rd;

// #define SEED 20000926
#define SEED (rd())

struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
};  // struct MyRandom

static MyRandom randint;

template <typename TKey, typename TValue>
struct Node {
    typedef TKey KeyType;
    typedef TValue ValueType;

    Node(int _key = 0, int _value = 0, Node *_left = NULL,
         Node *_right = NULL) {
        key = _key;
        value = _value;
        left = _left;
        right = _right;
        size = 1;
        weight = randint();
    }

    ~Node() {
        if (!left)
            delete left;
        if (!right)
            delete right;
    }

    void update() {
        size = 1 + (left == NULL ? 0 : left->size) +
               (right == NULL ? 0 : right->size);
    }

    KeyType key;
    ValueType value;
    int weight;
    size_t size;
    Node *left;
    Node *right;

    std::string to_string() {
        stringstream buffer;
        buffer << this << ": {key = " << this->key << ", size = " << this->size
               << ", left = " << this->left << ", right = " << this->right
               << "}";

        return buffer.str();
    }

    std::string to_dot_code() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key << ": " << value << "\"]";
        buffer << ";";

        if (left != nullptr) {
            buffer << key << ":sw -> " << left->key << ";";
        }

        if (right != nullptr) {
            buffer << key << ":se -> " << right->key << ";";
        }

        return buffer.str();
    }
};  // struct Node

typedef Node<int, int> TreapNode;
typedef TreapNode *Treap;
typedef pair<Treap, Treap> TreapPair;
typedef pair<int, int> NodeData;

static Treap tree;

static void _print(Treap h) {
    if (h == NULL)
        return;

    _print(h->left);
    cout << h->to_string() << endl;
    _print(h->right);
}

static void print(Treap h) {
    cout << "Printing " << h << "..." << endl;
    _print(h);
}

static void _show(Treap h, stringstream &buffer) {
    if (!h)
        return;

    buffer << h->to_dot_code();
    _show(h->left, buffer);
    _show(h->right, buffer);
}

static void show(Treap h) {
    stringstream buffer;

    buffer << "digraph{node[shape=circle]";
    _show(h, buffer);
    buffer << "}";

    fstream file("/tmp/tree.tmp.dot", ios::trunc | ios::out);
    file << buffer.str();
    file.close();
    system("showdot /tmp/tree.tmp.dot");
}

Treap rebuild(vector<NodeData> &data);
Treap merge(Treap a, Treap b);
TreapPair split(Treap h, int k);
int rank_key(Treap h, int key);
Treap query(Treap h, int key);
Treap insert(Treap h, int key, int value);
Treap remove(Treap h, int key);
Treap get_kth(Treap h, int k);
void slice(Treap h, int left, int right);  // [left, right]
bool contain(Treap h, int key);

int main() {
    initialize();

    char command;
    int key, value;

    while (cin >> command) {
        switch (command) {
            case 'Q':
                cin >> key;
                cout << query(tree, key)->value << '\n';

                break;

            case 'D':
                cin >> key;
                tree = remove(tree, key);

                break;

            case 'A':
                cin >> key >> value;

                tree = insert(tree, key, value);

                break;
        }  // switch to command
    }      // while

    return 0;
}  // function main

inline size_t size(Treap h) {
    if (!h)
        return 0;
    else
        return h->size;
}

Treap rebuild(vector<NodeData> &data) {
    sort(data.begin(), data.end());

    stack<Treap> s;

    for (auto &e : data) {
        int key = e.first;
        int value = e.second;
        Treap node = new TreapNode(key, value);

        while (!s.empty() && s.top()->weight >= node->weight) {
            s.top()->right = node->left;
            s.top()->update();
            node->left = s.top();
            s.pop();
        }

        node->update();
        if (!s.empty())
            s.top()->right = node;
        s.push(node);
    }  // foreach in data

    while (s.size() > 1)
        s.pop();

    return s.top();
}

Treap merge(Treap a, Treap b) {
    if (!a)
        return b;
    if (!b)
        return a;

    if (a->weight < b->weight) {
        a->right = merge(a->right, b);
        a->update();

        return a;
    } else {
        b->left = merge(a, b->left);
        b->update();

        return b;
    }
}

TreapPair split(Treap h, int k) {
    if (h == NULL)
        return TreapPair(NULL, NULL);

    TreapPair result;
    if (k <= size(h->left)) {
        result = split(h->left, k);
        h->left = result.second;
        h->update();
        result.second = h;
    } else {
        result = split(h->right, k - size(h->left) - 1);
        h->right = result.first;
        h->update();
        result.first = h;
    }

    return result;
}

int rank_key(Treap h, int key) {
    if (h == NULL)
        return 1;

    if (key < h->key)
        return rank_key(h->left, key);
    else if (key > h->key)
        return size(h->left) + 1 + rank_key(h->right, key);
    else
        return size(h->left) + 1;
}

Treap query(Treap h, int key) {
    if (h == NULL)
        return NULL;

    if (key < h->key)
        return query(h->left, key);
    else if (key > h->key)
        return query(h->right, key);
    else
        return h;
}

Treap insert(Treap h, int key, int value) {
    if (h == NULL)
        return new TreapNode(key, value);

    int k = rank_key(h, key);
    TreapPair a = split(h, k - 1);
    TreapPair b = split(a.second, 1);
    if (b.second && b.second->key == key) {
        b.second->value = value;

        return merge(a.first, merge(b.first, b.second));
    } else {
        a.second = merge(b.first, b.second);
        Treap node = new TreapNode(key, value);

        return merge(merge(a.first, node), a.second);
    }
}

Treap remove(Treap h, int key) {
    int k = rank_key(h, key);

    TreapPair a = split(h, k - 1);
    TreapPair b = split(a.second, 1);
    // delete b.first;

    return merge(a.first, b.second);
}

Treap get_kth(Treap h, int k) {
    TreapPair a = split(h, k);
    TreapPair b = split(a.first, k - 1);
    Treap node = b.second;

    merge(merge(b.first, b.second), a.second);

    return node;
}

void slice(Treap h, int left, int right) {
    TreapPair a = split(h, left - 1);
    TreapPair b = split(a.second, right - left + 1);

    show(b.first);
    merge(a.first, merge(b.first, b.second));
}

bool contain(Treap h, int key) {
    if (!h)
        return false;

    if (key < h->key)
        return contain(h->left, key);
    else if (key > h->key)
        return contain(h->right, key);
    else
        return true;
}
