#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define CMAX 1000000000

static struct UnionFind {
    UnionFind() {
        memset(fa, 0, sizeof(fa));
        cur = 0;
        for (int i = 1; i <= NMAX; i++) size[i] = 1;
    }

    int fa[NMAX + 10], cur;
    int size[NMAX + 10];
    struct {
        int pos, sz;
    } stk[NMAX + 10];

    int find(int x) {
        while (fa[x]) x = fa[x];
        return x;
    }

    int link(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return 0;
        if (size[u] < size[v]) swap(u, v);
        stk[cur++] = {v, size[v]};
        size[u] += size[v];
        fa[v] = u;
        return 1;
    }

    void back() {
        auto v = stk[--cur];
        size[fa[v.pos]] -= v.sz;
        fa[v.pos] = 0;
    }
} uf;

struct Edge { int u, v; };

struct Node {
    Node(int _l, int _r) : l(_l), r(_r), lch(NULL), rch(NULL) {}

    int l, r;
    Node *lch, *rch;
    vector<Edge> e;
};

static int n, q, ans;

void cover(Node *x, const Edge &e, int l, int r) {
    if (l <= x->l && x->r <= r) x->e.push_back(e);
    else {
        int m = (x->l + x->r) >> 1;
        if (l <= m) {
            if (!x->lch) x->lch = new Node(x->l, m);
            cover(x->lch, e, l, r);
        }
        if (r > m) {
            if (!x->rch) x->rch = new Node(m + 1, x->r);
            cover(x->rch, e, l, r);
        }
    }
}

void solve(Node *x) {
    int cnt = 0;
    for (auto &e : x->e) cnt += uf.link(e.u, e.v);
    if (x->l == x->r) ans += uf.find(1) == uf.find(n);
    else {
        int m = (x->l + x->r) >> 1;
        if (x->lch) solve(x->lch);
        else if (uf.find(1) == uf.find(n)) ans += m - x->l + 1;
        if (x->rch) solve(x->rch);
        else if (uf.find(1) == uf.find(n)) ans += x->r - m;
    }
    for (int i = 0; i < cnt; i++) uf.back();
}

int main() {
    scanf("%d%d", &n, &q);
    Node *tr = new Node(1, CMAX);
    for (int i = 0; i < q; i++) {
        int u, v, l, r;
        scanf("%d%d%d%d", &u, &v, &l, &r);
        cover(tr, {u, v}, l, r);
    }
    solve(tr);
    printf("%d\n", ans);

    return 0;
}
