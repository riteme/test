#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

struct Edge {
    Edge(int _v, i64 _w) : v(_v), w(_w) {}
    int v;
    i64 w;
};

static int n, q, s, t, len;
static vector<Edge *> G[NMAX + 10];
static bool mark[NMAX + 10];
static int top[NMAX + 10], fa[NMAX + 10], dep[NMAX + 10];
static i64 dist[NMAX + 10];

void dfs(int x) {
    mark[x] = true;
    top[x] = 1;
    for (auto e : G[x]) {
        int v = e->v;
        if (mark[v]) continue;
        fa[v] = x;
        dep[v] = dep[x] + 1;
        dist[v] = dist[x] + e->w;
        dfs(v);
        top[x] += top[v];
    }
}

void decompose(int x, int f) {
    int u = 0;
    for (auto e : G[x]) {
        int v = e->v;
        if (v != f && e->w && top[v] > top[u]) u = v;
    }

    if (u) {
        top[u] = top[x];
        decompose(u, x);
    }

    for (auto e : G[x]) {
        int v = e->v;
        if (v == u || v == f || !e->w) continue;
        top[v] = v;
        decompose(v, x);
    }
}

inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

inline i64 d(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[lca(u, v)];
}

void initialize() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(new Edge(v, w));
        G[v].push_back(new Edge(u, w));
    }

    dfs(1);
    for (int u = 1; u <= n; u++) {
        for (auto e : G[u]) {
            if (fa[e->v] != u && fa[u] != e->v){
                s = u;
                t = e->v;
                len = e->w;
                e->w = 0;
            }
        }
    }
    top[1] = 1;
    decompose(1, 0);
}

void finalize() {
    for (int i = 1; i <= n; i++) {
        mark[i] = false;
        G[i].clear();
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        initialize();

        while (q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%lld\n", min(
                d(u, v),
                min(d(u, s) + d(t, v) + len,
                    d(u, t) + d(s, v) + len)
            ));
        }

        finalize();
    }

    return 0;
}
