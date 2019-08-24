#include <cstring>
#include <climits>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// #define USE_FILE_IO

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

#define BLACK false
#define RED true

struct Node {
    Node() = default;
    Node(int _key = 0, int _value = 0, bool _color = BLACK,
         Node *_parent = nullptr, Node *_left = nullptr, Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , color(_color)
            , parent(_parent)
            , left(_left)
            , right(_right) {}

    int key = 0;
    int value = 0;
    bool color = BLACK;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;

    auto is_red() const -> bool {
        return color;
    }

    std::string print_node() {
        stringstream buffer;

        buffer << key;
        if (color == RED) {
            buffer << "[color=red]";
        }
        buffer << ";";

        if (left != nullptr) {
            buffer << key << "->" << left->key << ";";
        }

        if (right != nullptr) {
            buffer << key << "->" << right->key << ";";
        }

        return buffer.str();
    }
};  // struct Node

static Node *tree = nullptr;

Node *insert(Node *node, int key, int value);
Node *remove(Node *node, int key);
int query(Node *node, int key);
void cw_rotate(Node *node);
void ccw_rotate(Node *node);
Node *max_node(Node *node);
void print_tree(Node *node);
void print_tree(Node *node, std::string &data);

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

        if (tree != nullptr)
            tree->color = BLACK;

        print_tree(tree);
    }  // while

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

Node *insert(Node *node, int key, int value) {
    if (node == nullptr) {
        node = new Node(key, value, RED);
    } else {
        if (key < node->key) {
            node->left = insert(node->left, key, value);
            node->left->parent = node;
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
            node->right->parent = node;
        } else {
            node->value = value;
        }
    }

    if ((node->right != nullptr and node->right->is_red()) and
        (node->left == nullptr ? true : not node->left->is_red())) {
        ccw_rotate(node);
    }

    if (node->left != nullptr and node->left->left != nullptr and
        node->left->is_red() and node->left->left->is_red()) {
        cw_rotate(node);
        node->left->parent = node;
        node->right->parent = node;
    };

    if (node->left != nullptr and node->right != nullptr and
        node->left->is_red() and node->right->is_red()) {
        node->left->color = BLACK;
        node->right->color = BLACK;
        node->color = RED;
        node->left->parent = node;
    }

    return node;
}

static Node *real_remove(Node *node) {}

Node *remove(Node *node, int key) {
    if (node == nullptr)
        return nullptr;
    else {
        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            return real_remove(node);
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
    swap(node->right->left, node->left);
    swap(node->key, node->right->key);
    swap(node->value, node->right->value);
    swap(node->left, node->right);
}

Node *max_node(Node *node) {
    if (node == nullptr)
        return nullptr;

    if (node->right != nullptr)
        return max_node(node->right);

    return node;
}
