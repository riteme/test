#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n;
static int deg[NMAX + 10], dist[NMAX + 10], fa[NMAX + 10];
static bool marked[NMAX + 10];
static vector<int> G[NMAX + 10];

void dfs(int x, int f) {
    for (int v : G[x]) {
        if (v == f) continue;
        dist[v] = dist[x] + 1;
        fa[v] = x;
        dfs(v, x);
    }
}

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        deg[u]++;
        deg[v]++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
}

int main() {
    initialize();

    dfs(1, 0);
    int u = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 2 && dist[i] > dist[u])
            u = i;
    }

    if (u) {
        memset(dist, 0, sizeof(dist));
        dfs(u, 0);
        int v = u;
        for (int i = 1; i <= n; i++) {
            if (deg[i] > 2 && dist[i] > dist[v])
                v = i;
        }
        while (v != u) {
            marked[v] = true;
            v = fa[v];
        }
        marked[u] = true;
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            if (deg[i] > 2 && !marked[i])
                ok = false;
        }
        puts(ok ? "YES" : "NO");
    } else puts("YES");

    return 0;
}
