#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define NMAX 100000

struct Segment {
    Segment(int _left, int _right)
        : left(_left), right(_right), mark(0), value(0), leftchild(NULL), rightchild(NULL) {}

    int left;
    int right;
    int mark;
    int value;
    Segment *leftchild;
    Segment *rightchild;
};

inline int value_of(Segment *x) {
    return x->value + x->mark;
}

inline void update(Segment *x) {
    if (x->left < x->right) {
        x->value = min(value_of(x->leftchild), value_of(x->rightchild));
    }
}

inline void pushdown(Segment *x) {
    if (x->mark) {
        x->value += x->mark;

        if (x->leftchild)
            x->leftchild->mark += x->mark;
        if (x->rightchild)
            x->rightchild->mark += x->mark;

        x->mark = 0;
    }
}

static Segment *build(int left, int right, int *source) {
    Segment *x = new Segment(left, right);

    if (left == right)
        x->value = source[left];
    else {
        int mid = (left + right) / 2;
        x->leftchild = build(left, mid, source);
        x->rightchild = build(mid + 1, right, source);
        x->value = min(x->leftchild->value, x->rightchild->value);
    }

    return x;
}

static void modify(Segment *x, int left, int right, int delta) {
    if (left <= x->left && x->right <= right) {
        x->mark += delta;
        return;
    }

    pushdown(x);

    int mid = (x->left + x->right) / 2;
    if (right <= mid) {
        modify(x->leftchild, left, right, delta);
    } else if (left > mid) {
        modify(x->rightchild, left, right, delta);
    } else {
        modify(x->leftchild, left, right, delta);
        modify(x->rightchild, left, right, delta);
    }

    update(x);
}

static int find(Segment *x) {
    if (x->left == x->right)
        return x->left;

    pushdown(x);
    if (value_of(x->rightchild) <= value_of(x->leftchild))
        return find(x->rightchild);
    else
        return find(x->leftchild);
}

static int n;
static int seq[NMAX + 10];
static int perm[NMAX + 10];
static Segment *tree;

#define INFTY 10000000

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", seq + i);
    }

    tree = build(1, n, seq);

    for (int i = 1; i <= n; i++) {
        int j = find(tree);
        perm[j] = i;
        modify(tree, j, j, INFTY);
        if (j < n)
            modify(tree, j + 1, n, -1);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d\n", perm[i]);
    }
}
