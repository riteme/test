#define USE_FILE_IO
#define NDEBUG

#define ALPHA 0.805

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
         Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , size(1)
            , left(_left)
            , right(_right)
            , deleted(false) {}

    int key = 0;
    int value = 0;
    int size = 1;
    Node *left = nullptr;
    Node *right = nullptr;
    bool deleted = false;

    void update() {
        size = (deleted ? 0 : 1) + (left ? left->size : 0) +
               (right ? right->size : 0);
    }

    std::string print_node() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key
               << "\" color=" << (deleted ? "red" : "black") << "]";
        buffer << ";";

        if (left != nullptr) {
            buffer << key << ":sw -> " << left->key << "[style=bold];";
        }

        if (right != nullptr) {
            buffer << key << ":se -> " << right->key << "[style=bold];";
        }

        return buffer.str();
    }
};  // struct Node

static int size = 0;
static int deleted_count = 0;
static Node *tree = nullptr;

#define MEMORY_SIZE 10000000
static size_t current;
static Node *memory[MEMORY_SIZE];

inline void refresh() {
    current = 0;
}

inline void push(Node *node) {
    memory[++current] = node;
}

Node *rebalance(Node *h);
Node *insert(Node *h, int key, int value);
Node *remove(Node *h, int key);
Node *query(Node *h, int key);

void print_tree(Node *node);
void print_tree(Node *node, std::string &data);

int main() {
    initialize();

    char command;
    int key = INT_MAX, value = INT_MAX;
    while (cin >> command) {
        switch (command) {
            case 'A':
                cin >> key >> value;
                tree = insert(tree, key, value);

                break;
            case 'D':
                cin >> key;
                tree = remove(tree, key);

                break;
            case 'Q':
                cin >> key;

                {
                    auto ptr = query(tree, key);
                    if (ptr)
                        cout << ptr->value << "\n";
                    else
                        cout << "-1\n";
                }

                break;

            case 'B': tree = rebalance(tree); break;
        }  // switch to command

#ifndef NDEBUG
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

static void travel(Node *h) {
    if (!h)
        return;

    travel(h->left);
    if (!h->deleted)
        push(h);
    travel(h->right);

    if (h->deleted)
        delete h;
}

static Node *rebalance(int left, int right) {
    if (right < left)
        return nullptr;

    int mid = (left + right) >> 1;
    Node *node = memory[mid];
    node->left = rebalance(left, mid - 1);
    node->right = rebalance(mid + 1, right);
    node->update();

    return node;
}

Node *rebalance(Node *h) {
    refresh();
    travel(h);

    return rebalance(1, current);
}

static Node *insert(Node *h, int key, int value, bool &balanced) {
    if (!h) {
        size++;

        return new Node(key, value);
    }

    if (key == h->key) {
        h->value = value;

        if (h->deleted)
            h->deleted = false;
    } else if (key < h->key)
        h->left = insert(h->left, key, value);
    else
        h->right = insert(h->right, key, value);

    h->update();

    if (!balanced && ((h->left && h->left->size > ALPHA * h->size) ||
                      ((h->right && h->right->size > ALPHA * h->size)))) {
        balanced = true;

        return rebalance(h);
    } else
        return h;
}

Node *insert(Node *h, int key, int value) {
    bool balanced = false;

    return insert(h, key, value, balanced);
}

static Node *_remove(Node *h, int key) {
    if (!h)
        return nullptr;

    if (!h->deleted && key == h->key) {
        h->deleted = true;
        deleted_count++;
    } else if (key < h->key)
        h->left = _remove(h->left, key);
    else
        h->right = _remove(h->right, key);

    return h;
}

Node *remove(Node *h, int key) {
    h = _remove(h, key);

    if (deleted_count > size / 2) {
        size -= deleted_count;
        deleted_count = 0;

        return rebalance(h);
    } else
        return h;
}

Node *query(Node *h, int key) {
    if (!h)
        return nullptr;

    if (!h->deleted && key == h->key)
        return h;
    else if (key < h->key)
        return query(h->left, key);
    else
        return query(h->right, key);
}
