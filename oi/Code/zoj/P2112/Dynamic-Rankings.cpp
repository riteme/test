// #include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define QMAX 10000
// #define NMAX 30
// #define QMAX 30

static int n, q;
static int cnt;
static int num[NMAX + 10];
static int sorted[NMAX + QMAX + 10];

static void hashing() {
    sort(sorted + 1, sorted + cnt + 1);
    cnt = unique(sorted + 1, sorted + cnt + 1) - sorted - 1;
}

inline int id(int x) {
    return lower_bound(sorted + 1, sorted + cnt + 1, x) - sorted;
}

struct Node {
    int sum;
    Node *leftchild, *rightchild;
};  // struct Node

#define MEMORYSIZE 8000000
static unsigned _memcnt;
static Node _memory[MEMORYSIZE];

inline void refresh() {
    _memcnt = 0;
}

inline Node *allocate() {
    return &_memory[_memcnt++];
}

static Node *build(int left, int right) {
    Node *x = allocate();

    if (left == right) {
        x->sum = 0;
        x->leftchild = x->rightchild = NULL;
    } else {
        int mid = (left + right) >> 1;
        x->sum = 0;
        x->leftchild = build(left, mid);
        x->rightchild = build(mid + 1, right);
    }

    return x;
}

static Node *persistent_modify(Node *x, int left, int right, int u, int delta) {
    // Copying
    Node *y = allocate();
    *y = *x;
    x = y;

    if (left != right) {
        int mid = (left + right) >> 1;

        if (u <= mid) {
            x->leftchild = persistent_modify(x->leftchild, left, mid, u, delta);
        } else {
            x->rightchild =
                persistent_modify(x->rightchild, mid + 1, right, u, delta);
        }
    }

    x->sum += delta;
    return x;
}

static Node *version[NMAX + 10];
static Node *mark[NMAX + 10];

inline void fenwick_modify(int x, int u, int v) {
    for (int i = x; i <= n; i += i & (-i)) {
        mark[i] = persistent_modify(mark[i], 1, cnt, u, v);
    }  // for
}

static int cnt1;
static Node *a1[NMAX + 10];
static int cnt2;
static Node *a2[NMAX + 10];

static int query(Node *x, Node *y, int left, int right, int k) {
    cnt1 = cnt2 = 0;
    for (int i = left - 1; i; i -= i & (-i))
        a1[++cnt1] = mark[i];
    for (int i = right; i; i -= i & (-i))
        a2[++cnt2] = mark[i];

    int l = 1, r = cnt;
    while (l < r) {
        int mid = (l + r) >> 1;
        int leftsum = x->leftchild->sum - y->leftchild->sum;

        for (int i = 1; i <= cnt2; i++)
            leftsum += a2[i]->leftchild->sum;
        for (int i = 1; i <= cnt1; i++)
            leftsum -= a1[i]->leftchild->sum;

        if (k <= leftsum) {
            for (int i = 1; i <= cnt1; i++)
                a1[i] = a1[i]->leftchild;
            for (int i = 1; i <= cnt2; i++)
                a2[i] = a2[i]->leftchild;

            r = mid;
            x = x->leftchild;
            y = y->leftchild;
        } else {
            for (int i = 1; i <= cnt1; i++)
                a1[i] = a1[i]->rightchild;
            for (int i = 1; i <= cnt2; i++)
                a2[i] = a2[i]->rightchild;

            l = mid + 1;
            x = x->rightchild;
            y = y->rightchild;
            k -= leftsum;
        }
    }  // while

    return l;
}

enum CommandType { COMM_ADD = 1, COMM_QUERY = 2 };  // enum CommandType

struct Command {
    CommandType type;
    int i, j, k;
};  // struct Command

static Command ops[QMAX + 10];

static void cleanup() {
    refresh();
}

static void initialize() {
    cleanup();
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        scanf("%d", num + i);
        sorted[i] = num[i];
    }  // for
    cnt = n;

    char buffer[10];
    for (int i = 1; i <= q; i++) {
        scanf("%s", buffer);

        if (buffer[0] == 'Q') {
            ops[i].type = COMM_QUERY;
            scanf("%d%d%d", &ops[i].i, &ops[i].j, &ops[i].k);
        } else {
            ops[i].type = COMM_ADD;
            scanf("%d%d", &ops[i].i, &ops[i].j);
            sorted[++cnt] = ops[i].j;
        }
    }  // for

    hashing();

    version[0] = build(1, cnt);
    for (int i = 1; i <= n; i++) {
        version[i] = persistent_modify(version[i - 1], 1, cnt, id(num[i]), 1);
    }  // for

    for (int i = 1; i <= n; i++) {
        mark[i] = version[0];
    }  // for
}

int main() {
    freopen("dynrank.in", "r", stdin);
    freopen("dynrank.out", "w", stdout);
    int t;
    scanf("%d", &t);

    for (int m = 0; m < t; m++) {
        initialize();

        for (int i = 1; i <= q; i++) {
            Command &c = ops[i];

            if (c.type == COMM_ADD) {
                fenwick_modify(c.i, id(num[c.i]), -1);
                fenwick_modify(c.i, id(c.j), 1);
                num[c.i] = c.j;
            } else {
                printf("%d\n",
                       sorted[query(
                           version[c.j], version[c.i - 1], c.i, c.j, c.k)]);
            }
        }  // for
    }      // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
