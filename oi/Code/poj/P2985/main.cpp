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
    Node() : key(0), value(0), weight(0), left(NULL), right(NULL) {}
    Node(int _key = 0, int _value = 0, int _weight = 0, Node *_left = NULL,
         Node *_right = NULL)
            : key(_key)
            , value(_value)
            , weight(_weight)
            , left(_left)
            , right(_right) {}

    int key;
    int value;
    int weight;
    Node *left;
    Node *right;
};  // struct Node

static int n, m;
static int size;
static int set[NMAX + 10];
static Node *tree = NULL;

Node *insert(Node *h, int key, int value);
Node *remove(Node *h, int key);
Node *query(Node *h, int key);
Node *rank_min(Node *h, int k);

inline void make_set() {
    size = n;
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

static int find_set(int u) {
    return set[u] == u ? u : set[u] = find_set(set[u]);
}

static void union_set(int u, int v) {
    set[find_set(u)] = find_set(v);
    size--;
}

static void initialize() {
    scanf("%d%d", &n, &m);
    srand(145647U);

    make_set();

    for (int i = 1; i <= n; i++) {
        tree = insert(tree, i, 1);
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
                a = find_set(a);
                b = find_set(b);

                int new_size = query(tree, a)->value + query(tree, b)->value;
                tree = remove(tree, a);
                tree = remove(tree, b);
                tree = insert(tree, b, new_size);

                set[a] = b;
                size--;
            } break;

            case OP_QUERY: {
                scanf("%d", &a);
                printf("%d\n", rank_min(tree, size - a + 1)->value);
            } break;
        }  // switch to command
    }      // for

    return 0;
}  // function main

Node *insert(Node *h, int key, int value) {
    if (h == NULL) {
        h = new Node(key, value, rand());
    } else {
        if (key < h->key) {
            h->left = insert(h->left, key, value);
        } else if (key > h->key) {
            h->right = insert(h->right, key, value);
        }
    }

    return h;
}

Node *remove(Node *h, int key);

Node *query(Node *h, int key);

Node *rank_min(Node *h, int k);
