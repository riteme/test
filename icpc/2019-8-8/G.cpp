#include <cstdio>
#include <cstring>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define KMAX 1000000
#define _KMAX (2 * KMAX)

inline void chkmax(int &a, int b) { if (a < b) a = b; }

static struct Fenwick {
    int tm[_KMAX + 10], mx[_KMAX + 10], cur;
    void clear() { cur++; }

    void modify(int x, int v) {
        x += KMAX;
        for ( ; x <= _KMAX; x += x & -x) {
            if (tm[x] != cur) {
                tm[x] = cur;
                mx[x] = 0;
            }
            if (v > mx[x]) mx[x] = v;
        }
    }

    int query(int x) {
        x += KMAX;
        int r = 0;
        for ( ; x; x -= x & -x) {
            if (tm[x] != cur) {
                tm[x] = cur;
                mx[x] = 0;
            }
            chkmax(r, mx[x]);
        }
        return r;
    }
} bit[2];

static int n, m, w[NMAX + 10], size[NMAX + 10];
static vector<int> G[NMAX + 10];
struct Query { int k, ans; } op[NMAX + 10];
static vector<Query*> Q[NMAX + 10];

void dfs(int x, int fa) {
    size[x] = 1;
    for (int v : G[x]) if (v != fa) {
        dfs(v, x);
        size[x] += size[v];
    }
}

template <typename THook>
void scan_node(int x, int fa, const THook &hook) {
    hook(x);
    for (int v : G[x]) if (v != fa) scan_node(v, x, hook);
}

template <typename THook>
void scan_op(int x, int fa, const THook &hook) {
    for (auto e : Q[x]) hook(*e);
    for (int v : G[x]) if (v != fa) scan_op(v, x, hook);
}

set<int> *solve(int x, int fa) {
    int u = 0;
    for (int v : G[x]) if (v != fa && size[v] > size[u]) u = v;
    bit[0].modify(x - w[x], x);
    bit[1].clear();
    for (auto it = G[x].begin(); it != G[x].end(); it++) {
        int v = *it;
        if (v == fa || v == u) continue;
        scan_op(v, x, [](Query &q) {
            chkmax(q.ans, bit[0].query(q.k));
            chkmax(q.ans, bit[1].query(q.k));
        });
        scan_node(v, x, [x](int p) {
            bit[1].modify(p - w[x], p);
        });
    }
    for (auto it = G[x].rbegin(); it != G[x].rend(); it++) {
        int v = *it;
        if (v == fa || v == u) continue;
        scan_op(v, x, [](Query &q) {
            chkmax(q.ans, bit[0].query(q.k));
        });
        scan_node(v, x, [x](int p) {
            bit[0].modify(p - w[x], p);
        });
    }
    for (auto q : Q[x]) chkmax(q->ans, bit[0].query(q->k));
    set<int> *S;
    if (u) S = solve(u, x);
    else S = new set<int>;
    S->insert(x);
    auto update = [x, S](Query &q) {
        auto it = S->upper_bound(q.k + w[x]);
        if (it == S->end()) chkmax(q.ans, *S->rbegin());
        else if (it != S->begin()) chkmax(q.ans, *prev(it));
    };
    for (int v : G[x]) if (v != fa && v != u) scan_op(v, x, update);
    for (int v : G[x]) if (v != fa && v != u) {
        bit[0].clear();
        auto S0 = solve(v, x);
        auto it = S->begin();
        for (auto p : *S0) it = S->insert(it, p);
    }
    for (auto q : Q[x]) update(*q);
    return S;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", w + i);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= m; i++) {
        int x, k;
        scanf("%d%d", &x, &k);
        op[i] = {k, 0};
        Q[x].push_back(op + i);
    }
    dfs(1, 0);
    solve(1, 0);
    for (int i = 1; i <= m; i++) printf("%d\n", op[i].ans);
    return 0;
}
