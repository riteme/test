#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define OP_UNION 0
#define OP_QUERY 1

#define NMAX 200000

struct Node {
    Node() : key(0), size(1), weight(0), left(NULL), right(NULL) {}
    Node(int _key = 0, int _size = 1, int _weight = 0, Node *_left = NULL,
         Node *_right = NULL)
            : key(_key)
            , size(_size)
            , weight(_weight)
            , left(_left)
            , right(_right) {}

    int key;
    int size;
    int weight;
    Node *left;
    Node *right;

    void update() {
        size = 1;
        if (left != NULL)
            size += left->size;
        if (right != NULL)
            size += right->size;
    }
};  // struct Node

static int n, m;
static int set[NMAX + 10];
static int size[NMAX + 10];
static Node *tree = NULL;
static int tree_size;

Node *insert(Node *h, int key);
Node *remove(Node *h, int key);
Node *rank_min(Node *h, int k);

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
        size[i] = 1;
    }  // for
}

static int find_set(int u) {
    return set[u] == u ? u : set[u] = find_set(set[u]);
}

static void union_set(int u, int v) {
    u = find_set(u);
    v = find_set(v);

    if (u != v) {
        set[u] = v;
        size[v] += size[u];
    }
}

static void initialize() {
    scanf("%d%d", &n, &m);
    srand(145647U);

    make_set();

    tree_size = n;
    for (int i = 1; i <= n; i++) {
        tree = insert(tree, 1);
    }  // for
}

int main() {
    initialize();

    for (int i = 0; i < m; ++i) {
        int command;
        int a, b;
        scanf("%d", &command);

        switch (command) {
            case OP_UNION: {
                scanf("%d%d", &a, &b);
                if (find_set(a) == find_set(b))
                    continue;

                tree = remove(tree, size[find_set(a)]);
                tree = remove(tree, size[find_set(b)]);

                union_set(a, b);
                tree_size--;

                tree = insert(tree, size[find_set(a)]);
            } break;

            case OP_QUERY: {
                scanf("%d", &a);
                printf("%d\n", rank_min(tree, tree_size - a + 1)->key);
            } break;
        }  // switch to command
    }      // for

    return 0;
}  // function main

static Node *left_rotate(Node *h) {
    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    return x;
}

static Node *right_rotate(Node *h) {
    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    return x;
}

Node *insert(Node *h, int key) {
    if (h == NULL)
        return new Node(key, 1, rand());

    if (key < h->key) {
        h->left = insert(h->left, key);

        if (h->left->weight < h->weight) {
            h = left_rotate(h);
            h->right->update();
        }

        h->update();
    } else {
        h->right = insert(h->right, key);

        if (h->right->weight < h->weight) {
            h = right_rotate(h);
            h->left->update();
        }

        h->update();
    }

    return h;
}

static Node *remove(Node *h) {
    if (h->left != NULL and h->right != NULL) {
        if (h->left->weight < h->right->weight) {
            h = left_rotate(h);

            h->right = remove(h->right);
        } else {
            h = right_rotate(h);

            h->left = remove(h->left);
        }
    } else {
        Node *next;

        if (h->left != NULL)
            next = h->left;
        else
            next = h->right;

        delete h;
        return next;
    }

    h->update();
    return h;
}

Node *remove(Node *h, int key) {
    if (key < h->key) {
        h->left = remove(h->left, key);
    } else if (key > h->key) {
        h->right = remove(h->right, key);
    } else {
        return remove(h);
    }

    h->update();
    return h;
}

Node *rank_min(Node *h, int k) {
recursive:
    int lsize;
    if (h->left == NULL)
        lsize = 0;
    else
        lsize = h->left->size;

    if (lsize == k - 1)
        return h;
    else if (lsize < k - 1) {
        // return rank_min(h->right, k - lsize - 1);
        h = h->right;
        k = k - lsize - 1;
        goto recursive;
    } else {
        // return rank_min(h->left, k);
        h = h->left;
        goto recursive;
    }
}
