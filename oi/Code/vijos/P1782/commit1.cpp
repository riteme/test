// 借教室

#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MMAX 1000000
#define MEMORY_SIZE 2097151

// #define FMT "%lld"
// typedef long long ntype;
#define FMT "%d"
typedef int ntype;

struct Reservation {
    Reservation() : start(0), end(0), need(0) {}
    Reservation(ntype s, ntype t, ntype d) : start(s), end(t), need(d) {}

    ntype start;
    ntype end;
    ntype need;
};  // struct Reservation

struct Node {
    Node() : l(0), r(0), left(NULL), right(NULL), sum(0) {}
    Node(ntype _l, ntype _r) : l(_l), r(_r), left(NULL), right(NULL), sum(0) {}
    ntype l;
    ntype r;
    Node *left;
    Node *right;
    ntype sum;
};

static ntype n, m;
static ntype r[NMAX + 10];
static Reservation q[MMAX + 10];
static unsigned memcnt;
static Node memory[MEMORY_SIZE];
static Node *tree;
static bool flag;
static ntype id;

Node *build_tree(ntype lb, ntype rb);
void insert(ntype s, ntype t, ntype value, Node *x);
ntype query(ntype d, Node *x);

inline Node *allocate() { return &memory[memcnt++]; }

inline ntype read() {
    ntype x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}

void initialize();
void quit();

int main() {
    initialize();

    for (int i = 1; i <= m; i++) {
        insert(q[i].start, q[i].end, -q[i].need, tree);
    }  // for

    ntype j = m + 1;
    for (ntype i = 1; i <= n; i++) {
        while (query(i, tree) < 0) {
            j--;
            insert(q[j].start, q[j].end, q[j].need, tree);
        }  // while
    }      // for

    if (j != m + 1) {
        flag = true;
        id = j;
    }

    quit();
    return 0;
}  // function main

void initialize() {
    n = read();
    m = read();

    for (int i = 1; i <= n; i++) r[i] = read();
    for (int i = 1; i <= m; i++)
        q[i].need = read(), q[i].start = read(), q[i].end = read();

    flag = false;
    id = 0;
    memcnt = 0;

    tree = build_tree(1, n);
}

void quit() {
    if (!flag)
        puts("0");
    else {
        puts("-1");
        printf(FMT, id);
    }
}

Node *build_tree(ntype lb, ntype rb) {
    // Node *x = new Node(lb, rb);
    Node *x = allocate();
    x->l = lb;
    x->r = rb;

    if (lb != rb) {
        ntype mid = (lb + rb) / 2;
        x->left = build_tree(lb, mid);
        x->right = build_tree(mid + 1, rb);
        x->sum = 0;
    } else {
        x->left = NULL;
        x->right = NULL;
        x->sum = r[lb];
    }

    return x;
}

void insert(ntype s, ntype t, ntype value, Node *x) {
    if (s <= x->l and x->r <= t)
        x->sum += value;
    else {
        ntype mid = (x->l + x->r) / 2;

        if (t <= mid)
            insert(s, t, value, x->left);
        else if (s > mid)
            insert(s, t, value, x->right);
        else {
            insert(s, t, value, x->left);
            insert(s, t, value, x->right);
        }
    }
}

ntype query(ntype d, Node *x) {
recursive:
    if (d == x->l and d == x->r) return x->sum;

    ntype mid = (x->l + x->r) / 2;

    if (x->sum != 0) {
        x->left->sum += x->sum;
        x->right->sum += x->sum;
        x->sum = 0;
    }

    if (d <= mid) {
        // return query(d, x->left);
        x = x->left;
        goto recursive;
    } else {
        // return query(d, x->right);
        x = x->right;
        goto recursive;
    }
}
