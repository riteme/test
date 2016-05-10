#define USE_FILE_IO
#define NDEBUG

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
static ifstream cin("tree.in");
static ofstream cout("tree.out");
#endif  // IFNDEF USE_FILE_IO

inline void initialize() {
#ifndef USE_FILE_IO
    ios::sync_with_stdio(false);
#endif
}

struct Segment {
    int left = 0;
    int right = 0;
    int size = 0;
    int value = 0;

    Segment *leftchild = NULL;
    Segment *rightchild = NULL;
};  // struct Segment

static void update(Segment *x) {
    assert(x->left != x->right);

    x->size = 0;

    if (x->leftchild) {
        x->size += x->leftchild->size;
    }

    if (x->rightchild) {
        x->size += x->rightchild->size;
    }
}

static void insert(Segment *h, int key, int value) {
    assert(h != NULL);

    if (h->left == h->right) {
        h->value = value;
        h->size = 1;
        return;
    }

    int mid = (h->left + h->right) / 2;
    if (key <= mid) {
        if (!h->leftchild) {
            h->leftchild = new Segment;
            h->leftchild->left = h->left;
            h->leftchild->right = mid;
        }

        insert(h->leftchild, key, value);
    } else {
        if (!h->rightchild) {
            h->rightchild = new Segment;
            h->rightchild->left = mid + 1;
            h->rightchild->right = h->right;
        }

        insert(h->rightchild, key, value);
    }

    h->size++;
}

static Segment *remove(Segment *h, int key) {
    if (h->left == h->right) {
        // delete h;
        return NULL;
    }

    int mid = (h->left + h->right) / 2;
    if (key <= mid) {
        h->leftchild = remove(h->leftchild, key);
    } else {
        h->rightchild = remove(h->rightchild, key);
    }

    if (h->leftchild == NULL && h->rightchild == NULL) {
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

static Segment *kth(Segment *h, int k) {
    if (h->left == h->right) {
        return h;
    }

    if (k <= size_of(h->leftchild)) {
        return kth(h->leftchild, k);
    } else {
        return kth(h->rightchild, k - size_of(h->leftchild));
    }
}

static int query(Segment *h, int key) {
    int left = 1;
    int right = h->size;

    while (right - left > 1) {
        int mid = (left + right) / 2;
        Segment *x = kth(h, mid);

        if (x->left == key) {
            return x->value;
        }

        if (x->left < key) {
            left = mid;
        } else {
            right = mid;
        }
    }  // while

    Segment *x = kth(h, left);
    if (x->left == key) {
        return x->value;
    } else {
        if (left != right) {
            x = kth(h, right);
            if (x->left == key) {
                return x->value;
            }
        }
        return -1;
    }
}

int main() {
    initialize();

    char command;

    Segment *tree = NULL;
    while (cin >> command) {
        if (!tree) {
            tree = new Segment;
            tree->left = 1;
            tree->right = 100000000;
        }

        switch (command) {
            case 'A': {
                int key, value;
                cin >> key >> value;

                insert(tree, key, value);
            } break;
            case 'D': {
                int key;
                cin >> key;

                tree = remove(tree, key);
            } break;
            case 'K': {
                int k;
                cin >> k;

                cout << kth(tree, k) << '\n';
            } break;
            case 'Q': {
                int key;
                cin >> key;

                cout << query(tree, key) << '\n';
            } break;
        }  // switch to command
    }      // while

    return 0;
}  // function main
