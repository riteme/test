#define USE_FILE_IO
// #define NDEBUG
#define NPROFILE

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

#ifndef NDEBUG
#include <gperftools/profiler.h>
#endif  // IFNDEF NDEBUG

using namespace std;

#ifndef USE_FILE_IO
#include <iostream>
using std::cin;
using std::cout;
#else
static ifstream cin("interval.in");
static ofstream cout("interval.out");
#endif  // IFNDEF USE_FILE_IO

inline void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
};

typedef long long ntype;

struct Node;
int size_of(Node *);
int rank_of(Node *);
ntype sum_of(Node *);

#define TOLERANCE 1

struct Node {
    Node(int _key = 0, ntype _value = 0, Node *_left = nullptr,
         Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , sum(_value)
            , mark(0)
            , rank(1)
            , size(1)
            , left(_left)
            , right(_right) {}

    int key;
    int value;
    ntype sum;
    ntype mark;
    ntype rank;
    int size;
    Node *left;
    Node *right;

    void pushdown() {
        if (mark != 0) {
            sum += mark * size;
            value += mark;

            if (left)
                left->mark += mark;
            if (right)
                right->mark += mark;

            mark = 0;
        }
    }

    void update() {
        size = size_of(left) + size_of(right) + 1;
        rank = max(rank_of(left), rank_of(right)) + 1;
        sum = sum_of(left) + sum_of(right) + value;
    }

    std::string to_string() {
        stringstream buffer;
        buffer << this << ": {key = " << this->key << ", rank = " << this->rank
               << ", left = " << this->left << ", right = " << this->right
               << "}";

        return buffer.str();
    }

    std::string to_dot_code() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key << "(" << sum << ", " << mark << ")"
               << "\"]";
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

static Node *tree;

static void _print(Node *h) {
    if (h == nullptr)
        return;

    _print(h->left);
    cout << h->to_string() << endl;
    _print(h->right);
}

static void print(Node *h) {
    cout << "Printing " << h << "..." << endl;
    _print(h);
}

static void _show(Node *h, stringstream &buffer) {
    if (!h)
        return;

    buffer << h->to_dot_code();
    _show(h->left, buffer);
    _show(h->right, buffer);
}

static void show(Node *h) {
    stringstream buffer;

    buffer << "digraph{node[shape=circle]";
    _show(h, buffer);
    buffer << "}";

    fstream file("/tmp/tree.tmp.dot", ios::trunc | ios::out);
    file << buffer.str();
    file.close();
    system("showdot /tmp/tree.tmp.dot");
}

typedef pair<Node *, Node *> NodePair;

Node *query(Node *h, int key);
Node *insert(Node *h, int key, ntype value);
Node *remove(Node *h, int key);
Node *swim(Node *h, int key);
Node *sink(Node *h, int key);
int rank_key(Node *h, int key, int offest = 0);
Node *kth(Node *h, int k);
NodePair split(Node *h, int k);
Node *merge(Node *a, Node *b);

int main() {
#ifndef NPROFILE
    ProfilerStart("/tmp/rank-tree.profile");
#endif  // IFNDEF NPROFILE

    initialize();

    char command;
    int key;
    ntype value;
    while (cin >> command) {
        switch (command) {
            case 'D': {
                cin >> key;
                tree = remove(tree, key);
            } break;
            // case 'Q': {
            //     cin >> key;
            //     cout << query(tree, key)->value << '\n';
            // } break;
            case 'A': {
                cin >> key >> value;

                tree = insert(tree, key, value);
            } break;
            case 'N': {
                cin >> key;
                tree = sink(tree, key);
            } break;
            case 'U': {
                cin >> key;
                tree = swim(tree, key);
            } break;
            case 'R': {
                cin >> key;
                cout << rank_key(tree, key) << '\n';
            } break;
            case 'S': {
                cin >> key;
                NodePair a = split(tree, key);

                show(a.first);
                show(a.second);

                tree = merge(a.first, a.second);
            } break;
            case 'K': {
                cin >> key;
                cout << kth(tree, key)->key << '\n';
            } break;
            case 'C': {
                int x, y;
                ntype v;
                cin >> x >> y >> v;

                NodePair a = split(tree, x - 1);
                NodePair b = split(a.second, y - x + 1);
                b.first->mark += v;

                tree = merge(a.first, merge(b.first, b.second));
            } break;
            case 'Q': {
                int x, y;
                cin >> x >> y;

                NodePair a = split(tree, x - 1);
                NodePair b = split(a.second, y - x + 1);

                // b.first->pushdown();
                cout << b.first->sum << '\n';

                tree = merge(a.first, merge(b.first, b.second));
            } break;
#ifndef NDEBUG
            case 'P': {
                show(tree);
            } break;
#endif     // IFNDEF NDEBUG
        }  // switch to command
    }      // while

#ifndef NDEBUG
    cout << static_cast<double>(
                max(size_of(tree->left), size_of(tree->right))) /
                tree->size << endl;
#endif  // IFNDEF NDEBUG

#ifndef NPROFILE
    ProfilerStop();
#endif  // IFNDEF NPROFILE

    return 0;
}  // function main

int size_of(Node *h) {
    if (h)
        return h->size;
    else
        return 0;
}

int rank_of(Node *h) {
    if (h)
        return h->rank;
    else
        return 0;
}

ntype sum_of(Node *h) {
    if (h)
        return h->sum + h->mark * h->size;
    else
        return 0;
}

static Node *left_rotate(Node *h) {
    assert(h);
    assert(h->mark == 0);
    assert(h->left);
    assert(h->left->mark == 0);

    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    h->update();
    x->update();

    return x;
}

static Node *right_rotate(Node *h) {
    assert(h);
    assert(h->mark == 0);
    assert(h->right);
    assert(h->right->mark == 0);

    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    h->update();
    x->update();

    return x;
}

static Node *balance(Node *h) {
    if (rank_of(h->left) > rank_of(h->right) &&
        rank_of(h->left) - rank_of(h->right) > TOLERANCE) {
        h->pushdown();
        h->left->pushdown();

        if (rank_of(h->left->right) > rank_of(h->left->left)) {
            h->left->right->pushdown();
            h->left = right_rotate(h->left);
        }

        h = left_rotate(h);
    } else if (rank_of(h->left) < rank_of(h->right) &&
               rank_of(h->right) - rank_of(h->left) > TOLERANCE) {
        h->pushdown();
        h->right->pushdown();

        if (rank_of(h->right->left) > rank_of(h->right->right)) {
            h->right->left->pushdown();
            h->right = left_rotate(h->right);
        }

        h = right_rotate(h);
    } else
        h->update();

    return h;
}

Node *query(Node *h, int key) {
    if (h == nullptr)
        return nullptr;

    if (key < h->key)
        return query(h->left, key);
    else if (key > h->key)
        return query(h->right, key);
    else
        return h;
}

Node *insert(Node *h, int key, ntype value) {
    if (!h)
        return new Node(key, value);

    h->pushdown();
    if (key < h->key) {
        h->left = insert(h->left, key, value);

        return balance(h);
    } else if (key > h->key) {
        h->right = insert(h->right, key, value);

        return balance(h);
    } else
        h->value = value;

    return h;
}

static Node *remove(Node *h) {
    h->pushdown();
    if (h->left && h->right) {
        if (rank_of(h->left) > rank_of(h->right)) {
            h->left->pushdown();
            h = left_rotate(h);
            h->right = remove(h->right);
        } else {
            h->right->pushdown();
            h = right_rotate(h);
            h->left = remove(h->left);
        }
    } else {
        if (h->left)
            return h->left;
        else
            return h->right;
    }

    return balance(h);
}

Node *remove(Node *h, int key) {
    if (key < h->key)
        h->left = remove(h->left, key);
    else if (key > h->key)
        h->right = remove(h->right, key);
    else
        return remove(h);

    return balance(h);
}

Node *swim(Node *h, int key) {
    h->pushdown();

    if (key < h->key) {
        h->left = swim(h->left, key);

        h = left_rotate(h);
        // h->right = balance(h->right);
    } else if (key > h->key) {
        h->right = swim(h->right, key);

        h = right_rotate(h);
        // h->left = balance(h->left);
    }

    return h;
}

static Node *_sink(Node *h) {
    if (!h->left && !h->right)
        return h;

    if (rank_of(h->left) > rank_of(h->right)) {
        h->left->pushdown();
        h = left_rotate(h);

        h->right = _sink(h->right);
    } else {
        h->right->pushdown();
        h = right_rotate(h);

        h->left = _sink(h->left);
    }

    return balance(h);
}

static Node *sink(Node *h) {
    h->pushdown();

    return _sink(h);
}

Node *sink(Node *h, int key) {
    if (key < h->key)
        h->left = sink(h->left, key);
    else if (key > h->key)
        h->right = sink(h->right, key);
    else
        return sink(h);

    return balance(h);
}

int rank_key(Node *h, int key, int offest) {
    if (key < h->key)
        return rank_key(h->left, key, offest);
    else if (key > h->key)
        return rank_key(h->right, key, offest + size_of(h->left) + 1);
    else
        return size_of(h->left) + offest + 1;
}

NodePair split(Node *h, int k) {
    if (k < 1)
        return NodePair(nullptr, h);

    k = kth(h, k)->key;
    h = swim(h, k);
    NodePair result = { h, h->right };
    h->pushdown();
    h->right = nullptr;
    h->update();

    return result;
}

Node *merge(Node *a, Node *b) {
    if (!a)
        return sink(b);
    if (!b)
        return sink(a);

    assert(!a->right);

    a->pushdown();
    a->right = b;
    return sink(a);
}

Node *kth(Node *h, int k) {
    if (k <= size_of(h->left))
        return kth(h->left, k);
    else if (k > size_of(h->left) + 1)
        return kth(h->right, k - size_of(h->left) - 1);
    else
        return h;
}
