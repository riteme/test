#define USE_FILE_IO
// #define NDEBUG

#include <cassert>
#include <cstring>
#include <climits>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
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

struct Node {
    Node() = default;
    Node(int _key = 0, int _value = 0, Node *_left = nullptr,
         Node *_right = nullptr, Node *_parent = nullptr)
            : key(_key)
            , value(_value)
            , left(_left)
            , right(_right)
            , parent(_parent) {}

    int key = 0;
    int value = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    std::string print_node() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key << "\"]";
        buffer << ";";

        if (left != nullptr) {
            buffer << key << ":sw -> " << left->key << "[style=bold];";
        }

        if (right != nullptr) {
            buffer << key << ":se -> " << right->key << "[style=bold];";
        }

        if (parent != nullptr) {
            buffer << key << " -> " << parent->key << ";";
        }

        return buffer.str();
    }
};  // struct Node

static Node *tree = nullptr;

Node *insert(Node *h, int key, int value);
Node *remove(Node *h, int key);
int query(Node *&h, int key);

Node *splay(Node *x);
Node *right_rotate(Node *h);
Node *left_rotate(Node *h);

void print_tree(Node *node);
void print_tree(Node *node, std::string &data);

int main() {
    initialize();

    char command;
    int key = INT_MAX, value = INT_MAX;
    while (cin >> command) {
        switch (command) {
            case 'A':
                // puts("A");
                cin >> key >> value;
                tree = insert(tree, key, value);

                break;
            case 'D':
                // puts("D");
                cin >> key;
                // tree = remove(tree, key);

                break;
            case 'Q':
                // puts("Q");
                cin >> key;
                cout << query(tree, key) << "\n";

                break;
        }  // switch to command

#ifndef NDEBUG
        // if (command == 'A') {
        //     cout << "A " << key << " " << value << endl;
        // }
        // if (command == 'D') {
        //     cout << "D " << key << endl;
        // }

        if (command == 'P') {
            print_tree(tree);
        }
#endif  // IFNDEF NDEBUG
    }   // while

    return 0;
}  // function main

void print_tree(Node *node) {
    std::string data;
    data = "digraph{\nnode [shape=circle];";

    print_tree(node, data);

    data += "}";
    ofstream file("/tmp/tree.tmp.dot");
    file << data;
    file.close();
    system("showdot /tmp/tree.tmp.dot");
}

void print_tree(Node *node, std::string &data) {
    if (node == nullptr)
        return;

    data += node->print_node();
    print_tree(node->left, data);
    print_tree(node->right, data);
}

Node *left_rotate(Node *h) {
    assert(h != nullptr);
    assert(h->left != nullptr);

    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    if (h->left)
        h->left->parent = h;

    x->parent = h->parent;
    h->parent = x;

    if (x->parent) {
        if (x->parent->left == h)
            x->parent->left = x;
        else
            x->parent->right = x;
    }

    return x;
}

Node *right_rotate(Node *h) {
    assert(h != nullptr);
    assert(h->right != nullptr);

    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    if (h->right)
        h->right->parent = h;

    x->parent = h->parent;
    h->parent = x;

    if (x->parent) {
        if (x->parent->left == h)
            x->parent->left = x;
        else
            x->parent->right = x;
    }

    return x;
}

Node *splay(Node *x) {
    while (x->parent) {
        if (!x->parent->parent) {
            if (x == x->parent->left)
                left_rotate(x->parent);
            else
                right_rotate(x->parent);
        } else {
            if (x == x->parent->left) {
                if (x->parent == x->parent->parent->left) {
                    left_rotate(x->parent->parent);
                    left_rotate(x->parent);
                } else {
                    left_rotate(x->parent);
                    right_rotate(x->parent);
                }
            } else {
                if (x->parent == x->parent->parent->left) {
                    right_rotate(x->parent);
                    left_rotate(x->parent);
                } else {
                    right_rotate(x->parent->parent);
                    right_rotate(x->parent);
                }
            }
        }
    }  // while

    return x;
}

Node *insert(Node *h, int key, int value) {
    if (!h)
        return new Node(key, value);

    while (true) {
        if (key < h->key) {
            if (h->left == nullptr) {
                h->left = new Node(key, value);
                h->left->parent = h;

                return splay(h->left);
            } else
                h = h->left;
        } else if (key > h->key) {
            if (h->right == nullptr) {
                h->right = new Node(key, value);
                h->right->parent = h;

                return splay(h->right);
            } else
                h = h->right;
        } else {
            h->value = value;

            return splay(h);
        }
    }  // while
}

static Node *remove(Node *h) {
    if (h->left != nullptr and h->right != nullptr) {
        h = left_rotate(h);

        h->left = remove(h->left);
    } else {
        Node *next = nullptr;

        if (h->left != nullptr) {
            next = h->left;
        } else {
            next = h->right;
        }

        delete h;
        return next;
    }

    return h;
}

Node *remove(Node *h, int key) {
    assert(h != nullptr);

    if (key < h->key) {
        h->left = remove(h->left, key);

        if (h->left != nullptr)
            h = right_rotate(h);
    } else if (key > h->key) {
        h->right = remove(h->right, key);

        if (h->right != nullptr)
            h = left_rotate(h);
    } else {
        return remove(h);
    }

    return h;
}

static Node *_query(Node *h, int key) {
    if (h == nullptr)
        return nullptr;

    if (key < h->key)
        return _query(h->left, key);
    else if (key > h->key)
        return _query(h->right, key);
    else
        return h;
}

int query(Node *&h, int key) {
    Node *result = _query(h, key);

    if (result == nullptr)
        return -1;
    else {
        h = splay(result);
        return h->value;
    }
}