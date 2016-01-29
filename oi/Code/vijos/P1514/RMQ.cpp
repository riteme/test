#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define NMAX 200000

struct Node {
    Node()
            : left(0)
            , right(0)
            , value(INT_MIN)
            , leftchild(NULL)
            , rightchild(NULL) {}

    int left;
    int right;
    int value;
    int mark;
    Node *leftchild;
    Node *rightchild;
};  // struct Node

static int n;
static int m;
static int memory_usage;
static Node memory[3 * NMAX];
static Node *tree;

inline void free_memory() {
    memory_usage = -1;
}

inline Node *alloc() {
    memory_usage++;
    return memory + memory_usage;
}

Node *build_tree(int left, int right) {
    Node *node = alloc();

    node->left = left;
    node->right = right;
    node->value = 0;

    if (left < right) {
        int mid = (left + right) >> 1;
        node->leftchild = build_tree(left, mid);
        node->rightchild = build_tree(mid + 1, right);
    } else {
        node->leftchild = NULL;
        node->rightchild = NULL;
    }

    return node;
}

void insert(Node *x, int left, int right, int value) {
    // Out of control
    if (right < x->left or left > x->right) {
        return;
    }

    // Completely included
    if (left <= x->left and right >= x->right) {
        x->value += value;
        x->mark += value;
    } else {
        // Spread marks
        if (x->mark != 0) {
            x->leftchild->mark += x->mark;
            x->rightchild->mark += x->mark;
            x->leftchild->value += x->mark;
            x->rightchild->value += x->mark;

            x->mark = 0;
        }

        int mid = (x->left + x->right) >> 1;

        if (right <= mid) {
            insert(x->leftchild, left, right, value);
        } else if (left > mid) {
            insert(x->rightchild, left, right, value);
        } else {
            insert(x->leftchild, left, right, value);
            insert(x->rightchild, left, right, value);
        }

        x->value = max(x->leftchild->value, x->rightchild->value);
    }
}

int query(Node *x, int left, int right) {
    // Out of control
    if (right < x->left or left > x->right) {
        return INT_MIN;
    }

    // Completely included
    if (left <= x->left and right >= x->right) {
        return x->value;
    } else {
        // Spread marks
        if (x->mark != 0) {
            x->leftchild->mark += x->mark;
            x->rightchild->mark += x->mark;
            x->leftchild->value += x->mark;
            x->rightchild->value += x->mark;

            x->mark = 0;
        }

        int mid = (x->left + x->right) >> 1;
        int leftresult = INT_MIN;
        int rightresult = INT_MIN;

        if (right <= mid) {
            leftresult = query(x->leftchild, left, right);
        } else if (left > mid) {
            rightresult = query(x->rightchild, left, right);
        } else {
            leftresult = query(x->leftchild, left, right);
            rightresult = query(x->rightchild, left, right);
        }

        return max(leftresult, rightresult);
    }
}

void initialize() {
    scanf("%d", &n);

    free_memory();
    tree = build_tree(1, n);

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);

        insert(tree, i, i, x);
    }  // for
}

int main() {
    initialize();

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", query(tree, a, b));
    }  // for

    return 0;
}  // function main
