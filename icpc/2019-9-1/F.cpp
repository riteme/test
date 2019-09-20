#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

struct Node {
    Node(int _l, int _r) : l(_l), r(_r), mx(0), lch(NULL), rch(NULL) {}
    int l, r, mx;
    Node *lch, *rch;
};

Node *build(int l, int r) {
    Node *x = new Node(l, r);
    if (l < r) {
        int m = (l + r) >> 1;
        x->lch = build(l, m);
        x->rch = build(m + 1, r);
    }
    return x;
}

void clear(Node *x) {
    x->mx = 0;
    if (x->l < x->r) {
        clear(x->lch);
        clear(x->rch);
    }
}

void modify(Node *x, int p, int v) {
    if (x->l == x->r) x->mx = v;
    else {
        int m = (x->l + x->r) >> 1;
        if (p <= m) modify(x->lch, p, v);
        else modify(x->rch, p, v);
        x->mx = max(x->mx, v);
    }
}

int query(Node *x, int l, int r) {
    if (l <= x->l && x->r <= r) return x->mx;
    int m = (x->l + x->r) >> 1, ret = 0;
    if (l <= m) ret = max(ret, query(x->lch, l, r));
    if (r > m) ret = max(ret, query(x->rch, l, r));
    return ret;
}

static int n, K;
static int a[NMAX + 10], p[NMAX + 10], dp[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    Node *tr = build(1, NMAX);
    while (T--) {
        clear(tr);
        scanf("%d%d", &n, &K);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            p[a[i]] = i;
        }
        for (int v = 1; v <= n; v++) {
            int u = query(tr, p[v] - K, p[v] + K);
            dp[v] = dp[u] + 1;
            modify(tr, p[v], v);
            printf(v < n ? "%d " : "%d\n", dp[v]);
        }
    }
    return 0;
}
