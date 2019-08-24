#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

#define TREE_SIZE 1024

struct Node {
    Node() : key('?'), left(NULL), right(NULL) {}

    char key;
    Node *left;
    Node *right;
};  // struct Node

static string preorder, inorder;
static Node tree[TREE_SIZE + 5];
static int cnt;
static int pos;

inline void reserve_node() { pos = -1; }

inline Node *allocate_node() {
    pos++;
    tree[pos] = Node();

    return &tree[pos];
}

Node *generate_binary_tree(int left, int right);
void print_postorder(Node *node);

int main() {
    ios::sync_with_stdio(false);

    while (cin >> preorder >> inorder) {
        cnt = 0;

        reserve_node();
        generate_binary_tree(0, preorder.size());
        print_postorder(tree);

        cout << '\n';
    }  // while

    return 0;
}  // function main

Node *generate_binary_tree(int left, int right) {
    if (right <= left) return NULL;

    Node *node = allocate_node();
    node->key = preorder[cnt++];

    if (right - left != 1) {
        int mid = left;
        while (mid < right and node->key != inorder[mid]) mid++;

        if (mid - left > 0) node->left = generate_binary_tree(left, mid);

        if (right - mid > 0) node->right = generate_binary_tree(mid + 1, right);
    }

    return node;
}

void print_postorder(Node *node) {
    // Left, Right, Root
    if (node->left != NULL) print_postorder(node->left);
    if (node->right != NULL) print_postorder(node->right);

    cout << node->key;
}
