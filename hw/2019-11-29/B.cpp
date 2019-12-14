#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

struct Edge {
    int u, v, cnt = 0;

    int nxt(int x) const {
        return u == x ? v : u;
    }
};

static int n, q;
static Edge e[NMAX + 10];
static vector<Edge*> G[NMAX + 10];
static int fa[NMAX + 10], top[NMAX + 10], dep[NMAX + 10];

void dfs(int x, int f) {
    top[x] = 1;
    for (auto e : G[x]) {
        int v = e->nxt(x);
        if (v == f) continue;
        fa[v] = x;
        dep[v] = dep[x] + 1;
        dfs(v, x);
        top[x] += top[v];
    }
}

void decompose(int x, int f) {
    int u = 0;
    for (auto e : G[x]) {
        int v = e->nxt(x);
        if (v != f && top[v] > top[u]) u = v;
    }
    if (u) {
        top[u] = top[x];
        decompose(u, x);
    }
    for (auto e : G[x]) {
        int v = e->nxt(x);
        if (v == f || v == u) continue;
        top[v] = v;
        decompose(v, x);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

static int w[NMAX + 10];

void dp(int x, int f) {
    for (auto e : G[x]) {
        int v = e->nxt(x);
        if (v == f) continue;
        dp(v, x);
        e->cnt = w[v];
        w[x] += w[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &e[i].u, &e[i].v);
        G[e[i].u].push_back(e + i);
        G[e[i].v].push_back(e + i);
    }
    dfs(1, 0);
    top[1] = 1;
    decompose(1, 0);
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        int p = lca(u, v);
        w[p] -= 2;
        w[u]++;
        w[v]++;
    }
    dp(1, 0);
    for (int i = 1; i < n; i++)
        printf("%d ", e[i].cnt);
    puts("");
    return 0;
}
