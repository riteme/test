/**
 * HNOI2004 宠物收留所
 * operation nearest
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

typedef long long ntype;

struct Node {
    Node() : key(0), weight(0), left(NULL), right(NULL) {}
    Node(ntype _key = 0, ntype _weight = 0, Node *_left = NULL,
         Node *_right = NULL)
            : key(_key), weight(_weight), left(_left), right(_right) {}

    ntype key;
    ntype weight;
    Node *left;
    Node *right;
};  // struct Node

struct MyRandom {
    MyRandom(const unsigned seed) {
        srand(seed);
    }

    ntype operator()() {
        return rand();
    }
};  // struct MyRandom

#define MOD 1000000

#define MODE_UNKNOWN -1
#define MOD_PETS 0
#define MOD_CUSTOMERS 1

static ntype n;
static ntype mode = MODE_UNKNOWN;
static Node *tree = NULL;
static MyRandom randint(233);

typedef pair<Node *, Node *> NodePair;

Node *insert(Node *h, ntype key);
Node *remove(Node *h, ntype key);
NodePair nearest(Node *h, ntype target);

Node *right_rotate(Node *h);
Node *left_rotate(Node *h);

template <typename T>
inline T abs(const T &value) {
    return value < 0 ? -value : value;
}

static void initialize() {
    scanf("%lld", &n);
}

int main() {
    initialize();

    ntype result = 0;
    for (ntype i = 0; i < n; i++) {
        ntype m, key;
        scanf("%lld%lld", &m, &key);

        if (mode == MODE_UNKNOWN) {
            mode = m;
            tree = insert(tree, key);
        } else {
            if (mode == m) {
                tree = insert(tree, key);
            } else {
                NodePair near = nearest(tree, key);
                Node *a = near.first, *b = near.second;
                Node *target;

                if (a == NULL)
                    target = b;
                else if (b == NULL)
                    target = a;
                else {
                    ntype offest_a = abs(key - a->key);
                    ntype offest_b = abs(b->key - key);

                    if (offest_a <= offest_b)
                        target = a;
                    else
                        target = b;
                }

                result += abs(key - target->key);
                result %= MOD;

                tree = remove(tree, target->key);

                if (tree == NULL) {
                    mode = MODE_UNKNOWN;
                }
            }
        }
    }  // for

    printf("%lld", result);

    return 0;
}  // function main

Node *insert(Node *h, ntype key) {
    if (h == NULL)
        return new Node(key, randint());

    if (key < h->key) {
        h->left = insert(h->left, key);

        if (h->left->weight < h->weight) {
            h = right_rotate(h);
        }
    } else if (key > h->key) {
        h->right = insert(h->right, key);

        if (h->right->weight < h->weight) {
            h = left_rotate(h);
        }
    }

    return h;
}

static Node *remove(Node *h) {
    if (h->left != NULL and h->right != NULL) {
        if (h->left->weight >= h->right->weight) {
            h = right_rotate(h);

            h->right = remove(h->right);
        } else {
            h = left_rotate(h);

            h->left = remove(h->left);
        }
    } else {
        Node *next = NULL;

        if (h->left != NULL) {
            next = h->left;
        } else {
            next = h->right;
        }

        delete h;
        return next;
    }

    return h;
}

Node *remove(Node *h, ntype key) {
    if (key < h->key) {
        h->left = remove(h->left, key);
    } else if (key > h->key) {
        h->right = remove(h->right, key);
    } else {
        return remove(h);
    }

    return h;
}

NodePair nearest(Node *h, ntype target) {
    Node *current = h;
    Node *left = NULL;
    Node *right = NULL;

    while (current != NULL and target != current->key) {
        if (target < current->key) {
            right = current;
            current = current->left;
        } else if (target > current->key) {
            left = current;
            current = current->right;
        }
    }

    if (current != NULL and target == current->key) {
        left = right = current;
    }

    return NodePair(left, right);
}

Node *right_rotate(Node *h) {
    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    return x;
}

Node *left_rotate(Node *h) {
    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    return x;
}
