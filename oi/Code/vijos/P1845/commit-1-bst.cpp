#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define SEED (233)

static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;  // struct MyRandom

struct Node {
    Node(int _key, int _value)
            : key(_key)
            , value(_value)
            , maxvalue(_value)
            , weight(randint())
            , left(NULL)
            , right(NULL) {}

    int key;
    int value;
    int maxvalue;
    int weight;
    Node *left;
    Node *right;
};  // struct Node

inline void update(Node *x) {
    x->maxvalue = max(x->value,
                      max(x->left ? x->left->maxvalue : -1,
                          x->right ? x->right->maxvalue : -1));
}

inline Node *left_rotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;

    update(x);
    update(y);
    return y;
}

inline Node *right_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    update(x);
    update(y);
    return y;
}

static Node *insert(Node *x, int key, int value) {
    if (!x)
        return new Node(key, value);

    if (key < x->key) {
        x->left = insert(x->left, key, value);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else if (key > x->key) {
        x->right = insert(x->right, key, value);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    } else
        x->value = max(x->value, value);

    update(x);
    return x;
}

typedef pair<Node *, Node *> NodePair;

template <typename TCompare>
static NodePair split(Node *x, int key, const TCompare &cmp) {
    if (!x)
        return NodePair(NULL, NULL);

    NodePair result;
    if (cmp(key, x->key)) {
        result = split(x->left, key, cmp);
        x->left = result.second;
        result.second = x;
    } else {
        result = split(x->right, key, cmp);
        x->right = result.first;
        result.first = x;
    }

    update(x);
    return result;
}

static Node *quick_merge(Node *x, Node *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->weight < y->weight) {
        x->right = quick_merge(x->right, y);
        update(x);
        return x;
    } else {
        y->left = quick_merge(x, y->left);
        update(y);
        return y;
    }
}

static int n;
static int seq[NMAX + 10];
static int f1[NMAX + 10];
static int f2[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }  // for
}

int main() {
    initialize();

    Node *f1odd = NULL, *f1even = NULL, *f2odd = NULL, *f2even = NULL;
    for (int i = 1; i <= n; i++) {
        f1[i] = 1;
        f2[i] = 1;

        // for (int j = 1; j < i; j++) {
        //     if (((f1[j] & 1) && seq[i] < seq[j]) ||
        //         (!(f1[j] & 1) && seq[i] > seq[j]))
        //         f1[i] = max(f1[i], f1[j] + 1);
        //     if (((f2[j] & 1) && seq[i] > seq[j]) ||
        //         (!(f2[j] & 1) && seq[i] < seq[j]))
        //         f2[i] = max(f2[i], f2[j] + 1);
        // }  // for

        NodePair result;

        result = split(f1odd, seq[i],
                       [](const int a, const int b) { return a < b; });
        if (result.second)
            f1[i] = max(f1[i], result.second->maxvalue + 1);
        f1odd = quick_merge(result.first, result.second);

        result = split(f1even, seq[i],
                       [](const int a, const int b) { return a <= b; });
        if (result.first)
            f1[i] = max(f1[i], result.first->maxvalue + 1);
        f1even = quick_merge(result.first, result.second);

        result = split(f2odd, seq[i],
                       [](const int a, const int b) { return a <= b; });
        if (result.first)
            f2[i] = max(f2[i], result.first->maxvalue + 1);
        f2odd = quick_merge(result.first, result.second);

        result = split(f2even, seq[i],
                       [](const int a, const int b) { return a < b; });
        if (result.second)
            f2[i] = max(f2[i], result.second->maxvalue + 1);
        f2even = quick_merge(result.first, result.second);

        if (f1[i] & 1)
            f1odd = insert(f1odd, seq[i], f1[i]);
        else
            f1even = insert(f1even, seq[i], f1[i]);

        if (f2[i] & 1)
            f2odd = insert(f2odd, seq[i], f2[i]);
        else
            f2even = insert(f2even, seq[i], f2[i]);
    }  // for

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, max(f1[i], f2[i]));
    }  // for

    printf("%d\n", answer);

    return 0;
}  // function main
