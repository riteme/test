#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 250000

struct Edge {
    int u, v, i;

    int either(int x) {
        return u == x ? v : u;
    }
};

static int n, m, K;
static int ans[MMAX + 10];
static vector<Edge *> G[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 1; i <= m; i++) {
        Edge *e = new Edge;
        scanf("%d%d", &e->u, &e->v);
        e->i = i;
        G[e->u].push_back(e);
        G[e->v].push_back(e);
    }
}

static bool dfn[NMAX + 10];

void dfs(int u) {
    static int cur, cnt;
    dfn[u] = ++cur;

    for (size_t i = 0; i < G[u].size(); i++) {
        Edge *e = G[u][i];
        int v = e->either(u);
        if (!ans[e->i])
            ans[e->i] = ++cnt;

        if (!dfn[v])
            dfs(v);
    }
}

int main() {
    initialize();
    dfs(1);
    for (int i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
