#define USE_FILE_IO
// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <fstream>
#include <algorithm>

using namespace std;

#ifndef USE_FILE_IO
#include <iostream>
using std::cin;
using std::cout;
#else
static ifstream cin("interval.in");
static ofstream cout("interval.out");
#endif  // IFNDEF USE_FILE_IO

inline void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
};

typedef long long ntype;

struct Node;
int size_of(Node *);
int rank_of(Node *);
ntype sum_of(Node *);

#define TOLERANCE 1

struct Node {
    Node(int _key = 0, ntype _value = 0, Node *_left = nullptr,
         Node *_right = nullptr)
            : key(_key)
            , value(_value)
            , sum(_value)
            , mark(0)
            , rank(1)
            , size(1)
            , left(_left)
            , right(_right) {}

    int key;
    int value;
    ntype sum;
    ntype mark;
    ntype rank;
    int size;
    Node *left;
    Node *right;

    void pushdown() {
        if (mark != 0) {
            sum += mark * size;
            value += mark;

            if (left)
                left->mark += mark;
            if (right)
                right->mark += mark;

            mark = 0;
        }
    }

    void update() {
        size = size_of(left) + size_of(right) + 1;
        rank = max(rank_of(left), rank_of(right)) + 1;
        sum = sum_of(left) + sum_of(right) + value;
    }
};  // struct Node

static Node *tree;

typedef pair<Node *, Node *> NodePair;

Node *query(Node *h, int key);
Node *insert(Node *h, int key, ntype value);
Node *remove(Node *h, int key);
Node *kth(Node *h, int k);
Node *swim(Node *h, int key);
Node *sink(Node *h);
NodePair split(Node *h, int k);
Node *merge(Node *a, Node *b);

int main() {
    initialize();

    char command;
    int key;
    ntype value;
    while (cin >> command) {
        switch (command) {
            case 'D': {
                cin >> key;
                tree = remove(tree, key);
            } break;
            case 'A': {
                cin >> key >> value;

                tree = insert(tree, key, value);
            } break;
            case 'C': {
                int x, y;
                ntype v;
                cin >> x >> y >> v;

                NodePair a = split(tree, x - 1);
                NodePair b = split(a.second, y - x + 1);
                b.first->mark += v;

                tree = merge(a.first, merge(b.first, b.second));
            } break;
            case 'Q': {
                int x, y;
                cin >> x >> y;

                NodePair a = split(tree, x - 1);
                NodePair b = split(a.second, y - x + 1);

                cout << b.first->sum << '\n';

                tree = merge(a.first, merge(b.first, b.second));
            } break;
        }  // switch to command
    }      // while

    return 0;
}  // function main

int size_of(Node *h) {
    if (h)
        return h->size;
    else
        return 0;
}

int rank_of(Node *h) {
    if (h)
        return h->rank;
    else
        return 0;
}

ntype sum_of(Node *h) {
    if (h)
        return h->sum + h->mark * h->size;
    else
        return 0;
}

static Node *left_rotate(Node *h) {
    assert(h);
    assert(h->left);

    Node *x = h->left;
    h->pushdown();
    x->pushdown();

    h->left = x->right;
    x->right = h;

    h->update();
    x->update();

    return x;
}

static Node *right_rotate(Node *h) {
    assert(h);
    assert(h->right);

    Node *x = h->right;
    h->pushdown();
    x->pushdown();

    h->right = x->left;
    x->left = h;

    h->update();
    x->update();

    return x;
}

static Node *balance(Node *h) {
    if (rank_of(h->left) > rank_of(h->right) &&
        rank_of(h->left) - rank_of(h->right) > TOLERANCE) {
        if (rank_of(h->left->right) > rank_of(h->left->left))
            h->left = right_rotate(h->left);

        h = left_rotate(h);
    } else if (rank_of(h->left) < rank_of(h->right) &&
               rank_of(h->right) - rank_of(h->left) > TOLERANCE) {
        if (rank_of(h->right->left) > rank_of(h->right->right))
            h->right = left_rotate(h->right);

        h = right_rotate(h);
    } else
        h->update();

    return h;
}

Node *query(Node *h, int key) {
    if (h == nullptr)
        return nullptr;

    if (key < h->key)
        return query(h->left, key);
    else if (key > h->key)
        return query(h->right, key);
    else
        return h;
}

Node *insert(Node *h, int key, ntype value) {
    if (!h)
        return new Node(key, value);

    h->pushdown();
    if (key < h->key) {
        h->left = insert(h->left, key, value);

        return balance(h);
    } else if (key > h->key) {
        h->right = insert(h->right, key, value);

        return balance(h);
    } else
        h->value = value;

    return h;
}

static Node *remove(Node *h) {
    if (h->left && h->right) {
        if (rank_of(h->left) > rank_of(h->right)) {
            h = left_rotate(h);
            h->right = remove(h->right);
        } else {
            h = right_rotate(h);
            h->left = remove(h->left);
        }
    } else {
        h->pushdown();

        if (h->left)
            return h->left;
        else
            return h->right;
    }

    return balance(h);
}

Node *remove(Node *h, int key) {
    if (key < h->key)
        h->left = remove(h->left, key);
    else if (key > h->key)
        h->right = remove(h->right, key);
    else
        return remove(h);

    return balance(h);
}

Node *swim(Node *h, int key) {
    h->pushdown();

    if (key < h->key) {
        h->left = swim(h->left, key);

        h = left_rotate(h);
    } else if (key > h->key) {
        h->right = swim(h->right, key);

        h = right_rotate(h);
    }

    return h;
}

Node *sink(Node *h) {
    if (!h->left && !h->right)
        return h;

    if (rank_of(h->left) > rank_of(h->right)) {
        h = left_rotate(h);

        h->right = sink(h->right);
    } else {
        h = right_rotate(h);

        h->left = sink(h->left);
    }

    return balance(h);
}

NodePair split(Node *h, int k) {
    if (k < 1)
        return NodePair(nullptr, h);

    k = kth(h, k)->key;
    h = swim(h, k);
    NodePair result = { h, h->right };
    h->right = nullptr;
    h->update();

    return result;
}

Node *merge(Node *a, Node *b) {
    if (!a)
        return sink(b);
    if (!b)
        return sink(a);

    a->pushdown();
    a->right = b;

    return sink(a);
}

Node *kth(Node *h, int k) {
    while (k != size_of(h->left) + 1) {
        if (k <= size_of(h->left))
            h = h->left;
        else {
            k -= size_of(h->left) + 1;
            h = h->right;
        }
    }  // while

    return h;
}
