#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

// #define USE_FILE_IO

#ifndef USE_FILE_IO
#include <iostream>
using std::cin;
using std::cout;
#else
#include <fstream>
static ifstream cin("tree.in");
static ofstream cout("tree.out");
#endif  // IFNDEF USE_FILE_IO

void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
};

struct Node {
    Node() = default;
    Node(int _key = 0, int _value = 0, Node *_left = nullptr,
         Node *_right = nullptr)
            : key(_key), value(_value), left(_left), right(_right) {}

    int key = 0;
    int value = 0;
    Node *left = nullptr;
    Node *right = nullptr;
};  // struct Node

static Node *tree = nullptr;

Node *insert(Node *node, int key, int value);
Node *remove(Node *node, int key);
int query(Node *node, int key);
void cw_rotate(Node *node);
void ccw_rotate(Node *node);

int main() {
    initialize();

    char command;
    int key, value;
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
                cout << query(tree, key) << "\n";

                break;
        }  // switch to command
    }      // while

    return 0;
}  // function main

Node *insert(Node *node, int key, int value) {
    if (node == nullptr) {
        node = new Node(key, value);
    } else {
        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;
        }
    }

    return node;
}

// TODO(riteme): Improve this
Node *remove(Node *node, int key) {
    if (node->key == key) {
        Node *origin = node;
        Node *parent = node;

        while (node->left != nullptr and node->right != nullptr) {
            cw_rotate(node);
            parent = node;
            node = node->right;
        }  // while

        Node *next = nullptr;
        if (node->left != nullptr)
            next = node->left;
        if (node->right != nullptr)
            next = node->right;

        delete node;

        if (parent == node) {
            return next;
        } else {
            parent->right = next;
            return origin;
        }
    } else {
        if (key < node->key) {
            node->left = remove(node->left, key);
        } else {
            node->right = remove(node->right, key);
        }
    }

    return node;
}

int query(Node *node, int key) {
    if (node == nullptr) {
        return -1;
    }

    if (key < node->key) {
        return query(node->left, key);
    } else if (key > node->key) {
        return query(node->right, key);
    } else {
        return node->value;
    }
}

void cw_rotate(Node *node) {
    if (node->left == nullptr)
        return;

    swap(node->left->left, node->left->right);
    swap(node->left->right, node->right);
    swap(node->key, node->left->key);
    swap(node->value, node->left->value);
    swap(node->left, node->right);
}

void ccw_rotate(Node *node) {
    if (node->right == nullptr)
        return;

    swap(node->right->left, node->right->right);
    swap(node->right->right, node->left);
    swap(node->key, node->right->key);
    swap(node->value, node->right->value);
    swap(node->left, node->right);
}
