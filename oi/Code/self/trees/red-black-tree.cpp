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

    void print_node() {
        cout << this << ": { key = " << key << ", value = " << value
             << ", color = " << (color == RED ? "RED" : "BLACK")
             << ", parent = " << parent << ", left = " << left
             << ", right = " << right << " }" << endl;
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
    if (node == nullptr)
        return;

    print_tree(node->left);
    node->print_node();
    print_tree(node->right);
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

inline Node *real_remove(Node *node) {
    // if (node->left != nullptr and node->right != nullptr) {
    //     Node *parent = node;
    //     Node *prev = get_pervious(node->left, &parent);

    //     swap(prev->key, node->key);
    //     swap(prev->value, node->value);

    //     Node *update = real_remove(prev);
    //     if (parent == node) {
    //         node->left = update;
    //     } else {
    //         parent->right = update;
    //     }

    //     return node;
    // } else {
    //     Node *next = nullptr;

    //     if (node->left != nullptr) {
    //         next = node->left;
    //     }

    //     if (node->right != nullptr) {
    //         next = node->right;
    //     }

    //     delete node;
    //     return next;
    // }
}

Node *remove(Node *node, int key) {
    if (node->key == key) {
        return real_remove(node);
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

Node *max_node(Node *node) {
    if (node == nullptr)
        return nullptr;

    if (node->right != nullptr)
        return max_node(node->right);

    return node;
}
