#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000
#define INF 1000000000

struct Node {
    Node(int _l, int _r)
        : l(_l), r(_r), maxv(0), minv(INF),
          lch(NULL), rch(NULL) {}

    int l, r, maxv, minv;
    Node *lch, *rch;

    void update() {
        maxv = max(lch->maxv, rch->maxv);
        minv = min(lch->minv, rch->minv);
    }
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

void modify(Node *x, int p, int v) {
    if (x->l == x->r) x->minv = x->maxv = v;
    else {
        int m = (x->l + x->r) >> 1;
        if (p <= m) modify(x->lch, p, v);
        else modify(x->rch, p, v);
        x->update();
    }
}

int query_max(Node *x, int l, int r) {
    if (l <= x->l && x->r <= r) return x->maxv;
    else {
        int ret = 0, m = (x->l + x->r) >> 1;
        if (l <= m) ret = max(query_max(x->lch, l, r), ret);
        if (r > m) ret = max(query_max(x->rch, l, r), ret);
        return ret;
    }
}

int query_min(Node *x, int l, int r) {
    if (l <= x->l && x->r <= r) return x->minv;
    else {
        int ret = INF, m = (x->l + x->r) >> 1;
        if (l <= m) ret = min(query_min(x->lch, l, r), ret);
        if (r > m) ret = min(query_min(x->rch, l, r), ret);
        return ret;
    }
}

static int perm[NMAX + 10], f[NMAX + 10][2];

int main() {
    int n;
    scanf("%d", &n);
    Node *seg = build(1, n), *sl = build(1, n), *sr = build(1, n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", perm + i);
        f[i][0] = perm[i] == i;
        f[i][1] = perm[i] != i;
        if (perm[i] == i) modify(seg, i, i);
        else if (i < perm[i]) modify(sr, i, perm[i]);
        else modify(sl, i, perm[i]);
        if (i > 1) {
            f[i][0] += perm[i - 1] != i - 1 ? f[i - 1][1] : 0;
            f[i][1] += perm[i - 1] == i - 1 ? f[i - 1][0] : 0;
        }
    }
    bool ok = true;
    for (int i = 1; i <= n && ok; i++) {
        ok &= (i & 1) == (perm[i] & 1);
        ok &= perm[i] == i || perm[i] - f[perm[i]][1] < i;
        if (perm[i] > i) {
            ok &= query_max(seg, i, perm[i]) < perm[i];
            ok &= query_min(sr, i, perm[i]) >= perm[i];
        } else if (perm[i] < i) {
            ok &= query_min(seg, perm[i], i) > perm[i];
            ok &= query_max(sl, perm[i], i) <= perm[i];
        }
    }
    puts(ok ? "Yes" : "No");
    return 0;
}
