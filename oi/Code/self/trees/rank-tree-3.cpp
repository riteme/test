// #define NDEBUG
#define NPROFILE

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <stack>
#include <string>
#include <random>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

#ifndef NPROFILER
#include <gperftools/profiler.h>
#endif  // IFNDEF NPROFILER

using namespace std;

#ifndef NDEBUG
#include <iostream>
using std::cin;
using std::cout;
#else
static ifstream cin("interval.in");
static ofstream cout("interval.out");
#endif  // IFNDEF NDEBUG

inline void initialize() {
#ifndef NDEBUG
    ios::sync_with_stdio(false);
#endif
};

typedef long long ntype;

struct Node;
int size_of(Node *);
int rank_of(Node *);
ntype sum_of(Node *);

#define TOLERANCE 4

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

    std::string to_string() {
        stringstream buffer;
        buffer << this << ": {key = " << this->key << ", rank = " << this->rank
               << ", left = " << this->left << ", right = " << this->right
               << "}";

        return buffer.str();
    }

    std::string to_dot_code() {
        stringstream buffer;

        buffer << key;
        buffer << "[label=\"" << key << "(" << sum << ", " << mark << ")"
               << "\"]";
        buffer << ";";

        if (left != nullptr) {
            buffer << key << ":sw -> " << left->key << ";";
        }

        if (right != nullptr) {
            buffer << key << ":se -> " << right->key << ";";
        }

        return buffer.str();
    }
};  // struct Node

static Node *tree;

static void _print(Node *h) {
    if (h == nullptr)
        return;

    _print(h->left);
    cout << h->to_string() << endl;
    _print(h->right);
}

static void print(Node *h) {
    cout << "Printing " << h << "..." << endl;
    _print(h);
}

static void _show(Node *h, stringstream &buffer) {
    if (!h)
        return;

    buffer << h->to_dot_code();
    _show(h->left, buffer);
    _show(h->right, buffer);
}

static void show(Node *h) {
    stringstream buffer;

    buffer << "digraph{node[shape=circle]";
    _show(h, buffer);
    buffer << "}";

    fstream file("/tmp/tree.tmp.dot", ios::trunc | ios::out);
    file << buffer.str();
    file.close();
    system("showdot /tmp/tree.tmp.dot");
}

typedef pair<Node *, Node *> NodePair;

Node *balance(Node *h);
NodePair split(Node *h, int k);
Node *merge(Node *a, Node *b);
int rank_key(Node *h, int key, int offest = 0);
Node *insert(Node *h, int key, ntype value);
Node *remove(Node *h, int key);

int main() {
#ifndef NPROFILE
    ProfilerStart("/tmp/rank-tree.profile");
#endif  // IFNDEF NPROFILE

    initialize();

    char command;
    while (cin >> command) {
        switch (command) {
            case 'A': {
                int key, value;
                cin >> key >> value;

                tree = insert(tree, key, value);
            } break;
            case 'D': {
                int key;
                cin >> key;

                tree = remove(tree, key);
            } break;
            case 'S': {
                int k;
                cin >> k;

                NodePair a = split(tree, k);
                show(a.first);
                show(a.second);

                tree = merge(a.first, a.second);
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

                // b.first->pushdown();
                cout << b.first->sum << '\n';

                tree = merge(a.first, merge(b.first, b.second));
            } break;
#ifndef NDEBUG
            case 'P': {
                show(tree);
            } break;
#endif     // IFNDEF NDEBUG
        }  // switch to command
    }      // while

#ifndef NDEBUG
    if (tree)
        cout << static_cast<double>(
                    max(size_of(tree->left), size_of(tree->right))) /
                    tree->size << endl;
    else
        cout << "Unvalid." << endl;
#endif  // IFNDEF NDEBUG

#ifndef NPROFILE
    ProfilerStop();
#endif  // IFNDEF NPROFILE

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
    assert(h->mark == 0);
    assert(h->left);
    assert(h->left->mark == 0);

    Node *x = h->left;
    h->left = x->right;
    x->right = h;

    h->update();
    x->update();

    return x;
}

static Node *right_rotate(Node *h) {
    assert(h);
    assert(h->mark == 0);
    assert(h->right);
    assert(h->right->mark == 0);

    Node *x = h->right;
    h->right = x->left;
    x->left = h;

    h->update();
    x->update();

    return x;
}

Node *balance(Node *h) {
    if (rank_of(h->left) > rank_of(h->right) &&
        rank_of(h->left) - rank_of(h->right) > TOLERANCE) {
        assert(h->left);
        h->left->pushdown();

        if (rank_of(h->left->right) > rank_of(h->left->left)) {
            assert(h->left->right);
            h->left->right->pushdown();
            h->left = right_rotate(h->left);
        }

        h = left_rotate(h);
    } else if (rank_of(h->left) < rank_of(h->right) &&
               rank_of(h->right) - rank_of(h->left) > TOLERANCE) {
        assert(h->right);
        h->right->pushdown();

        if (rank_of(h->right->left) > rank_of(h->right->right)) {
            assert(h->right->left);
            h->right->left->pushdown();
            h->right = left_rotate(h->right);
        }

        h = right_rotate(h);
    } else
        h->update();

    return h;
}

NodePair split(Node *h, int k) {
    if (!h)
        return NodePair(nullptr, nullptr);

    h->pushdown();

    NodePair a;
    if (k <= size_of(h->left)) {
        a = split(h->left, k);
        h->left = a.second;
        h->update();
        a.second = h;
    } else {
        a = split(h->right, k - size_of(h->left) - 1);
        h->right = a.first;
        h->update();
        a.first = h;
    }

    return a;
}

Node *merge(Node *a, Node *b) {
    if (!a)
        return b;
    if (!b)
        return a;

    if (a->rank < b->rank) {
        b->pushdown();
        b->left = merge(a, b->left);

        return balance(b);
    } else {
        a->pushdown();
        a->right = merge(a->right, b);

        return balance(a);
    }
}

int rank_key(Node *h, int key, int offest) {
    if (!h)
        return offest + 1;

    if (key < h->key)
        return rank_key(h->left, key, offest);
    else if (key > h->key)
        return rank_key(h->right, key, offest + size_of(h->left) + 1);
    else
        return size_of(h->left) + offest + 1;
}

Node *insert(Node *h, int key, ntype value) {
    if (!h)
        return new Node(key, value);

    int k = rank_key(h, key);

    NodePair a = split(h, k - 1);

    return merge(merge(a.first, new Node(key, value)), a.second);
}

Node *remove(Node *h, int key) {
    int k = rank_key(h, key);

    NodePair a = split(h, k - 1);
    NodePair b = split(a.second, 1);

    // delete b.first;

    return merge(a.first, b.second);
}
