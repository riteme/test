#include <cstdio>
#include <climits>
#include <cstring>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define QMAX 100000
#define MMAX 300000

template <typename T>
inline void chkmax(T &a, const T &b) {
    if (a < b) a = b;
}

struct Node {
    Node() : maxv(0), lch(nullptr), rch(nullptr) {}
    int maxv;
    Node *lch, *rch;

    void update() {
        maxv = max(lch ? lch->maxv : INT_MAX, rch ? rch->maxv : INT_MAX);
    }
};

Node *modify(Node *x, int p, int v, int xl, int xr) {
    x = x ? new Node(*x) : new Node;
    if (xl == xr) x->maxv = v;
    else {
        int m = (xl + xr) >> 1;
        if (p <= m) x->lch = modify(x->lch, p, v, xl, m);
        else x->rch = modify(x->rch, p, v, m + 1, xr);
        x->update();
    }
    return x;
}

int query(Node *x, int l, int r, int xl, int xr) {
    if (!x) return INT_MAX;
    if (l <= xl && xr <= r) return x->maxv;
    int ret = 0, m = (xl + xr) >> 1;
    if (l <= m) chkmax(ret, query(x->lch, l, r, xl, m));
    if (r > m) chkmax(ret, query(x->rch, l, r, m + 1, xr));
    return ret;
}

static int n, m, q, cnt, ps[2*MMAX + 10];
static struct { int l, r, par; } seg[MMAX + 10];
static vector<int> ins[2*MMAX + 10], del[2*MMAX + 10];
static multiset<int> Q[2*MMAX + 10];
static Node *ver[2*MMAX + 10];

inline int id(int p) {
    return upper_bound(ps + 1, ps + cnt + 1, p) - ps - 1;
}

inline int min(const multiset<int> &qset) {
    return qset.empty() ? INT_MAX : *qset.begin();
}

int main() {
    scanf("%d%d%d", &n, &q, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &seg[i].l, &seg[i].r, &seg[i].par);
        ps[i] = seg[i].l + 1;
    }
    sort(ps + 1, ps + 2*m + 1);
    cnt = unique(ps + 1, ps + 2*m + 1) - ps - 1;
    for (int i = 1; i <= m; i++) {
        ins[1].push_back(i);
        del[id(seg[i].l + 1)].push_back(i);
    }

    Node *cur = nullptr;
    for (int i = 1; i <= cnt; i++) {
        for (int p : del[i]) {
            int x = seg[p].par;
            auto iter = Q[x].find(seg[p].r);
            Q[x].erase(iter);
            cur = modify(cur, x, min(Q[x]), 1, n);
        }
        for (int p : ins[i]) {
            int x = seg[p].par;
            Q[x].insert(seg[p].r);
            cur = modify(cur, x, min(Q[x]), 1, n);
        }
        ver[i] = cur;
    }
    while (q--) {
        int l, r, x, y;
        scanf("%d%d%d%d", &l, &r, &x, &y);
        puts(query(ver[id(x)], l, r, 1, n) <= y ? "yes" : "no");
        fflush(stdout);
    }

    return 0;
}
