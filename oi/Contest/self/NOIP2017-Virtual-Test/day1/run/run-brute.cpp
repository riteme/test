#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};

static int n, m;
static vector<Edge *> G[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }
}

static int ans = INT_MAX;
static bool marked[NMAX + 10];

void dfs(int u, int s, int len) {
    if (s >= ans)
        return;
    if (u == 1 && len == n) {
        ans = s;
        return;
    }
    if (marked[u])
        return;
    marked[u] = true;

    for (auto e : G[u]) {
        int v = e->either(u);
        dfs(v, s + e->w, len + 1);
    }

    marked[u] = false;
}

int main() {
    initialize();
    dfs(1, 0, 0);
    printf("%d\n", ans);

    return 0;
}
