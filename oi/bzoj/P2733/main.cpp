#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

struct Node {
    Node(int _left, int _right)
        : left(_left), right(_right),
          size(left == right ? 1 : 0),
          leftchild(NULL), rightchild(NULL) {}

    int left;
    int right;
    int size;
    Node *leftchild;
    Node *rightchild;

    void update() {
        if (left < right) {
            size = 0;

            if (leftchild)
                size += leftchild->size;
            if (rightchild)
                size += rightchild->size;
        }
    }
};

static Node *create(int left, int right, int pos) {
    Node *x = new Node(left, right);

    if (left < right) {
        int mid = (left + right) / 2;

        if (pos <= mid)
            x->leftchild = create(left, mid, pos);
        else
            x->rightchild = create(mid + 1, right, pos);

        x->update();
    }

    return x;
}

static Node *merge(Node *x, Node *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    assert(x->left == y->left && x->right == y->right);

    x->leftchild = merge(x->leftchild, y->leftchild);
    x->rightchild = merge(x->rightchild, y->rightchild);
    x->update();

    delete y;
    return x;
}

static Node *query(Node *x, int k) {
    if (!x)
        return NULL;

    if (x->left == x->right) {
        if (k == 1)
            return x;
        return NULL;
    } else {
        int leftsize = x->leftchild ? x->leftchild->size : 0;

        if (leftsize && k <= leftsize)
            return query(x->leftchild, k);
        return query(x->rightchild, k - leftsize);
    }
}

struct UnionFind {
    UnionFind() {
        for (int i = 1; i <= NMAX; i++)
            set[i] = i;
    }

    int set[NMAX + 10];

    int find(int x) {
        return set[x] == x ? x : set[x] = find(set[x]);
    }
};

static int n, m, q;
static int rnk[NMAX + 10];
static int id[NMAX + 10];
static Node *tree[NMAX + 10];
static UnionFind *set;

static void union_point(int u, int v) {
    int iu = set->find(u);
    int iv = set->find(v);

    if (iu != iv) {
        set->set[iu] = iv;
        tree[iv] = merge(tree[iv], tree[iu]);
    }
}

static int kth(int u, int k) {
    u = set->find(u);

    Node *r = query(tree[u], k);
    if (!r)
        return -1;
    else
        return id[r->left];
}

inline char get_valid_char() {
    char c = getchar();

    while (!isalpha(c))
        c = getchar();

    return c;
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", rnk + i);
        id[rnk[i]] = i;
    }

    set = new UnionFind;
    for (int i = 1; i <= n; i++)
        tree[i] = create(1, n, rnk[i]);

    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);

        union_point(u, v);
    }

    scanf("%d", &q);

    while (q--) {
        char command = get_valid_char();

        if (command == 'B') {
            int x, y;
            scanf("%d%d", &x, &y);

            union_point(x, y);
        } else {
            int x, k;
            scanf("%d%d", &x, &k);

            printf("%d\n", kth(x, k));
        }
    }

    return 0;
}

