#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Node {
    Node(int _key) : key(_key), left(NULL), right(NULL) {}

    int key;
    Node *left;
    Node *right;
};  // struct Node

static Node *insert(Node *x, int key) {
    if (!x) {
        return new Node(key);
    }

    if (key < x->key) {
        x->left = insert(x->left, key);
    } else {
        x->right = insert(x->right, key);
    }

    return x;
}

static Node *query(Node *x, int key) {
    if (!x) {
        return NULL;
    }

    if (key < x->key) {
        return query(x->left, key);
    } else if (key > x->key) {
        return query(x->right, key);
    } else {
        return x;
    }
}

static int stat(Node *x, int key, int k) {
    if (!x) {
        return -1;
    }

    if (k == 1) {
        return x->key;
    }

    if (key < x->key) {
        return stat(x->left, key, k - 1);
    } else {
        return stat(x->right, key, k - 1);
    }
}

static int n;

int main() {
    freopen("bst.in", "r", stdin);
    freopen("bst.out", "w", stdout);
    scanf("%d", &n);

    Node *tree = NULL;
    for (int i = 0; i < n; i++) {
        int u, k;
        scanf("%d%d", &u, &k);

        tree = insert(tree, u);
        printf("%d\n", stat(tree, u, k));
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
