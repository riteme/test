// #define USE_FILE_IO
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

struct Node;
int size_of(Node *);
int rank_of(Node *);

#define TOLERANCE 1

struct Node {
    Node(int _key = 0, int _value = 0, Node *_left = nullptr,
         Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , rank(1)
            , size(1)
            , left(_left)
            , right(_right) {}

    int key;
    int value;
    int rank;
    int size;
    Node *left;
    Node *right;

    void update() {
        size = size_of(left) + size_of(right) + 1;
        rank = max(rank_of(left), rank_of(right)) + 1;
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
        buffer << "[label=\"" << key << "(" << rank << ")"
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
Node *insert(Node *h, int key, int value);
Node *remove(Node *h, int key);
Node *swim(Node *h, int key);
Node *sink(Node *h, int key);
int rank_key(Node *h, int key, int offest = 0);
Node *kth(Node *h, int k);
NodePair split(Node *h, int key);
Node *merge(Node *a, Node *b);

int main() {
    initialize();

    char command;
    int key, value;

    while (cin >> command) {
        switch (command) {
            case 'D': {
                cin >> key;
                // tree = remove(tree, key);
            } break;
            case 'Q': {
                cin >> key;
                cout << query(tree, key)->value << '\n';
            } break;
            case 'A': {
                cin >> key >> value;

                auto ptr = query(tree, key);
                if (ptr)
                    ptr->value = value;
                else
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
                key = kth(tree, key)->key;
                NodePair a = split(tree, key);

                show(a.first);
                show(a.second);

                tree = merge(a.first, a.second);
            } break;
            case 'K': {
                cin >> key;
                cout << kth(tree, key)->key << '\n';
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

static Node *left_rotate(Node *h) {
    assert(h);
    assert(h->left);

    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    h->update();
    x->update();

    return x;
}

static Node *right_rotate(Node *h) {
    assert(h);
    assert(h->right);

    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    h->update();
    x->update();

    return x;
}

static Node *balance(Node *h) {
    if (rank_of(h->left) > rank_of(h->right)) {
        if (rank_of(h->left) - rank_of(h->right) > TOLERANCE) {
            if (rank_of(h->left->right) > rank_of(h->left->left))
                h->left = right_rotate(h->left);

            h = left_rotate(h);
        }
    } else {
        if (rank_of(h->right) - rank_of(h->left) > TOLERANCE) {
            if (rank_of(h->right->left) > rank_of(h->right->right))
                h->right = left_rotate(h->right);

            h = right_rotate(h);
        }
    }

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

Node *insert(Node *h, int key, int value) {
    if (!h)
        return new Node(key, value);

    if (key < h->key) {
        h->left = insert(h->left, key, value);

        h = balance(h);
    } else if (key > h->key) {
        h->right = insert(h->right, key, value);

        h = balance(h);
    } else
        h->value = value;

    return h;
}

Node *remove(Node *h, int key) {
    h = reinterpret_cast<Node *>(key);
    return h;
}

Node *swim(Node *h, int key) {
    if (key < h->key) {
        h->left = swim(h->left, key);

        h = left_rotate(h);
        h->right = balance(h->right);
    } else if (key > h->key) {
        h->right = swim(h->right, key);

        h = right_rotate(h);
        h->left = balance(h->left);
    }

    return h;
}

static Node *sink(Node *h) {
    if (!h->left && !h->right)
        return h;

    if (rank_of(h->left) > rank_of(h->right)) {
        h = left_rotate(h);

        h->right = sink(h->right);
    } else {
        h = right_rotate(h);

        h->left = sink(h->left);
    }

    h->update();
    h = balance(h);
    return h;
}

Node *sink(Node *h, int key) {
    if (key < h->key) {
        h->left = sink(h->left, key);

        return balance(h);
    } else if (key > h->key) {
        h->right = sink(h->right, key);

        return balance(h);
    }

    return sink(h);
}

int rank_key(Node *h, int key, int offest) {
    if (key < h->key)
        return rank_key(h->left, key, offest);
    else if (key > h->key)
        return rank_key(h->right, key, offest + size_of(h->left) + 1);
    else
        return size_of(h->left) + offest + 1;
}

NodePair split(Node *h, int key) {
    h = swim(h, key);

    NodePair result = { h, h->right };
    h->right = nullptr;
    h->update();

    return result;
}

Node *merge(Node *a, Node *b) {
    assert(!a->right);

    a->right = b;
    return sink(a, a->key);
}

Node *kth(Node *h, int k) {
    if (k <= size_of(h->left))
        return kth(h->left, k);
    else if (k > size_of(h->left) + 1)
        return kth(h->right, k - size_of(h->left) - 1);
    else
        return h;
}
