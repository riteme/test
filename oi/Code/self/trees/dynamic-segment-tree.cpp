// #define USE_FILE_IO
// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef USE_FILE_IO
#include <iostream>
using std::cin;
using std::cout;
#else
#include <fstream>
static ifstream cin("interval.in");
static ofstream cout("interval.out");
#endif  // IFNDEF USE_FILE_IO

inline void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
}

typedef long long ntype;

struct Segment {
    int left = 0;
    int right = 0;
    ntype size = 0;
    ntype sum = 0;
    ntype mark = 0;

    Segment *parent = NULL;
    Segment *leftchild = NULL;
    Segment *rightchild = NULL;
};  // struct Segment

static void pushdown(Segment *x) {
    if (x->mark != 0) {
        x->sum += x->mark * x->size;

        if (x->leftchild) {
            x->leftchild->mark += x->mark;
        }

        if (x->rightchild) {
            x->rightchild->mark += x->mark;
        }

        x->mark = 0;
    }
}

static void update(Segment *x) {
    assert(x->mark == 0);
    assert(x->left != x->right);

    x->sum = 0;
    x->size = 0;

    if (x->leftchild) {
        x->sum += x->leftchild->sum + x->leftchild->size * x->leftchild->mark;
        x->size += x->leftchild->size;
    }

    if (x->rightchild) {
        x->sum +=
            x->rightchild->sum + x->rightchild->size * x->rightchild->mark;
        x->size += x->rightchild->size;
    }
}

static void insert(Segment *h, int key, ntype value) {
    assert(h != NULL);

    if (h->left == h->right) {
        h->sum = value;
        h->size = 1;
        return;
    }

    pushdown(h);

    int mid = (h->left + h->right) / 2;
    if (key <= mid) {
        if (!h->leftchild) {
            h->leftchild = new Segment;
            h->leftchild->parent = h;
            h->leftchild->left = h->left;
            h->leftchild->right = mid;
        }

        insert(h->leftchild, key, value);
    } else {
        if (!h->rightchild) {
            h->rightchild = new Segment;
            h->rightchild->parent = h;
            h->rightchild->left = mid + 1;
            h->rightchild->right = h->right;
        }

        insert(h->rightchild, key, value);
    }

    h->sum += value;
    h->size++;
}

static Segment *remove(Segment *h, int key) {
    if (h->left == h->right) {
        // delete h;
        return NULL;
    }

    pushdown(h);
    int mid = (h->left + h->right) / 2;
    if (key <= mid) {
        h->leftchild = remove(h->leftchild, key);
    } else {
        h->rightchild = remove(h->rightchild, key);
    }

    if (h->parent != NULL && h->leftchild == NULL && h->rightchild == NULL) {
        // delete h;
        return NULL;
    }

    update(h);
    return h;
}

inline int size_of(Segment *x) {
    if (x) {
        return x->size;
    } else {
        return 0;
    }
}

static int kth(Segment *h, int k) {
    if (h->left == h->right) {
        return h->left;
    }

    if (k <= size_of(h->leftchild)) {
        return kth(h->leftchild, k);
    } else {
        return kth(h->rightchild, k - size_of(h->leftchild));
    }
}

static void modify(Segment *h, int left, int right, int value) {
    if (!h) {
        return;
    }

    if (left <= h->left && h->right <= right) {
        h->mark += value;
        return;
    }

    pushdown(h);
    int mid = (h->left + h->right) / 2;
    if (right <= mid) {
        modify(h->leftchild, left, right, value);
    } else if (left > mid) {
        modify(h->rightchild, left, right, value);
    } else {
        modify(h->leftchild, left, right, value);
        modify(h->rightchild, left, right, value);
    }

    update(h);
}

static ntype query(Segment *h, int left, int right) {
    if (!h) {
        return 0;
    }

    if (left <= h->left && h->right <= right) {
        return h->sum + h->mark * h->size;
    }

    pushdown(h);
    int mid = (h->left + h->right) / 2;
    if (right <= mid) {
        return query(h->leftchild, left, right);
    } else if (left > mid) {
        return query(h->rightchild, left, right);
    } else {
        return query(h->leftchild, left, right) +
               query(h->rightchild, left, right);
    }
}

int main() {
    initialize();

    char command;
    Segment *tree = new Segment;
    tree->left = 1;
    tree->right = 5000000;
    while (cin >> command) {
        switch (command) {
            case 'A': {
                int key, value;
                cin >> key >> value;

                insert(tree, key, value);
            } break;
            case 'D': {
                int key;
                cin >> key;

                remove(tree, key);
            } break;
            case 'K': {
                int k;
                cin >> k;

                cout << kth(tree, k) << '\n';
            } break;
            case 'C': {
                int x, y;
                ntype v;
                cin >> x >> y >> v;

                int left = kth(tree, x);
                int right = kth(tree, y);
                modify(tree, left, right, v);
            } break;
            case 'Q': {
                int x, y;
                cin >> x >> y;

                int left = kth(tree, x);
                int right = kth(tree, y);
                cout << query(tree, left, right) << '\n';
            } break;
        }  // switch to command
    }      // while

    return 0;
}  // function main
