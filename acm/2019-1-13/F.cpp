#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, q, perm[NMAX + 10], map[NMAX + 10], cur;
static int fa[NMAX + 10], dep[NMAX + 10], top[NMAX + 10], in[NMAX + 10], out[NMAX + 10];
static vector<int> T[NMAX + 10];

void dfs(int x) {
    top[x] = 1;
    in[x] = ++cur;
    for (int v : T[x]) {
        dfs(v);
        top[x] += top[v];
    }
    out[x] = cur;
}

void decompose(int x) {
    int u = 0;
    for (int v : T[x]) if (top[v] > top[u]) u = v;
    if (u) {
        top[u] = top[x];
        decompose(u);
    }
    for (int v : T[x]) {
        if (v == u) continue;
        top[v] = v;
        decompose(v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

bool insub(int p, int u) {
    return in[p] <= in[u] && in[u] <= out[p];
}

bool onpath(int u, int v, int p1, int p2) {
    if ((insub(p1, u) || insub(p1, v)) && (insub(p2, u) || insub(p2, v))) {
        int q = lca(u, v);
        return insub(q, p1) && insub(q, p2);
    }
    return false;
}

struct Path {
    Path() : l(0), r(0), u(0), v(0) {}
    Path(int p) : l(p), r(p), u(map[p]), v(map[p]) {}
    Path(int _l, int _r, int _u, int _v) : l(_l), r(_r), u(_u), v(_v) {}

    int l, r, u, v;

    int len() const {
        return r - l + 1;
    }
};

Path *connect(Path *a, Path *b) {
    if (!a) return b;
    if (!b) return a;
    int l = min(a->l, b->l), r = max(a->r, b->r);
    if (onpath(a->u, a->v, b->u, b->v)) return new Path(l, r, a->u, a->v);
    if (onpath(a->u, b->u, b->v, a->v)) return new Path(l, r, a->u, b->u);
    if (onpath(a->u, b->v, b->u, a->v)) return new Path(l, r, a->u, b->v);
    if (onpath(a->v, b->u, b->v, a->u)) return new Path(l, r, a->v, b->u);
    if (onpath(a->v, b->v, b->u, a->u)) return new Path(l, r, a->v, b->v);
    if (onpath(b->u, b->v, a->u, a->v)) return new Path(l, r, b->u, b->v);
    return nullptr;
}

Path *try_connect(Path *a, Path *b) {
    Path *ret = connect(a, b);
    return ret ? ret : a;
}

struct Node {
    Node() : valid(false), p(nullptr), lch(nullptr), rch(nullptr) {}

    bool valid;
    Path *p;
    Node *lch, *rch;
};

Node *build(int l, int r) {
    Node *x = new Node;
    if (l < r) {
        int m = (l + r) >> 1;
        x->lch = build(l, m);
        x->rch = build(m + 1, r);
    } else {
        x->valid = true;
        x->p = new Path(l);
    }
    return x;
}

void clear(Node *x, int p, int xl, int xr) {
    if (xl < xr) {
        delete x->p;
        x->p = nullptr;
        x->valid = false;
        int m = (xl + xr) >> 1;
        if (p <= m) clear(x->lch, p, xl, m);
        else clear(x->rch, p, m + 1, xr);
    } else x->p->u = x->p->v = map[xl];
}

void eval(Node *x) {
    if (x->valid) return;
    if (!x->lch->valid) eval(x->lch);
    if (!x->rch->valid) eval(x->rch);
    if (x->lch->p && x->rch->p) x->p = connect(x->lch->p, x->rch->p);
    x->valid = true;
}

int query(Node *x) {
    Path *cur = nullptr;
    while (x->lch) {
        Path *tmp = connect(cur, x->lch->p);
        if (tmp && cur != tmp) cur = tmp, x = x->rch;
        else x = x->lch;
    }
    cur = try_connect(cur, x->p);
    return cur->len();
}

static Node *seg;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", perm + i);
        map[perm[i]] = i;
    }
    for (int i = 2; i <= n; i++) {
        scanf("%d", fa + i);
        dep[i] = dep[fa[i]] + 1;
        T[fa[i]].push_back(i);
    }
    dfs(1);
    top[1] = 1;
    decompose(1);
    seg = build(0, n - 1);
    eval(seg);

    scanf("%d", &q);
    while (q--) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int i, j;
            scanf("%d%d", &i, &j);
            int ti = perm[i], tj = perm[j];
            swap(perm[i], perm[j]);
            swap(map[ti], map[tj]);
            clear(seg, ti, 0, n - 1);
            clear(seg, tj, 0, n - 1);
            eval(seg);
        } else printf("%d\n", query(seg));
    }

    return 0;
}
