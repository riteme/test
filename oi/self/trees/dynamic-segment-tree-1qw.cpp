// #define USE_FILE_IO
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
    int value = 0;

    Segment *leftchild = NULL;
    Segment *rightchild = NULL;
};  // struct Segment

static void insert(Segment *h, int key, int value) {
    assert(h != NULL);

    if (h->left == h->right) {
        h->value = value;
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

    return h;
}

static int query(Segment *h, int key) {
    if (!h) {
        return -1;
    }

    if (h->left == h->right) {
        return h->value;
    }

    int mid = (h->left + h->right) / 2;
    if (key <= mid) {
        return query(h->leftchild, key);
    } else {
        return query(h->rightchild, key);
    }
}

int main() {
    initialize();

    char command[10];
    Segment *tree = NULL;
    while (scanf("%s", command) != EOF) {
        if (!tree) {
            tree = new Segment;
            tree->left = 1;
            tree->right = 100000000;
        }

        switch (command[0]) {
            case 'A': {
                int key, value;
                scanf("%d%d", &key, &value);

                insert(tree, key, value);
            } break;
            case 'D': {
                int key;
                scanf("%d", &key);

                tree = remove(tree, key);
            } break;
            case 'Q': {
                int key;
                scanf("%d", &key);

                printf("%d\n", query(tree, key));
            } break;
        }  // switch to command
    }      // while

    return 0;
}  // function main
