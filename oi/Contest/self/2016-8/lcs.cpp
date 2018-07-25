#define NDEBUG
#pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

#define NMAX 80000
// #define NMAX 100

struct Node {
    Node(int _left, int _right)
            : left(_left)
            , right(_right)
            , maxcount(0)
            , leftchild(NULL)
            , rightchild(NULL) {}

    int left, right;
    int maxcount;
    Node *leftchild, *rightchild;
};  // struct Node

static Node *build(int left, int right) {
    if (left == right)
        return new Node(left, left);
    else {
        int mid = (left + right) / 2;
        Node *x = new Node(left, right);
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);

        return x;
    }
}

static void modify(Node *x, int u, int v) {
    if (x->left == x->right)
        x->maxcount = v;
    else {
        int mid = (x->left + x->right) / 2;

        if (u <= mid)
            modify(x->leftchild, u, v);
        else
            modify(x->rightchild, u, v);

        x->maxcount = max(x->leftchild->maxcount, x->rightchild->maxcount);
    }
}

static int query(Node *x, int r) {
    if (x->right <= r)
        return x->maxcount;
    else {
        int mid = (x->left + x->right) / 2;

        if (r <= mid)
            return query(x->leftchild, r);
        else
            return max(query(x->leftchild, r), query(x->rightchild, r));
    }
}

static void clear(Node *x) {
    if (!x)
        return;

    x->maxcount = 0;

    clear(x->leftchild);
    clear(x->rightchild);
}

static int n;
static int p, q;
static int seq1[NMAX + 10];
static int seq2[NMAX + 10];
static int map1[NMAX + 10];
static int map2[NMAX + 10];
static Node *tree;

static void initialize() {
    scanf("%d%d%d", &n, &p, &q);

    memset(map1, 0, sizeof(map1));
    memset(map2, 0, sizeof(map2));

    for (int i = 1; i <= p; i++) {
        scanf("%d", seq1 + i);
        map1[seq1[i]] = i;
    }

    for (int i = 1; i <= q; i++) {
        scanf("%d", seq2 + i);
        map2[seq2[i]] = i;
    }

    clear(tree);
}

int main() {
    // freopen("lcs.in", "r", stdin);
    // freopen("lcs.out", "w", stodut);

    int t;
    scanf("%d", &t);
    tree = build(1, NMAX);

    while (t--) {
        initialize();

        for (int i = 1; i <= p; i++) {
            int pos = map2[seq1[i]];

            if (pos == 0)
                continue;

            int maxlength = query(tree, pos);
            modify(tree, pos, maxlength + 1);
        }  // for

        printf("%d\n", query(tree, NMAX));
    }  // while

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
