#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 40000

struct Edge {
    int v, w, nxt;
};

static int n, q;
static Edge e[2 * NMAX + 10];
static int G[NMAX + 10];

int dfs(int x, int t, int dist, int fa) {
    if (x == t) return dist;
    for (int i = G[x]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        int ret = dfs(v, t, dist + e[i].w, x);
        if (ret) return ret;
    }
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        memset(G + 1, 0, sizeof(int) * n);
        for (int i = 1; i < n; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[2 * i].nxt = G[u];
            e[2 * i].v = v;
            e[2 * i].w = w;
            G[u] = 2 * i;
            e[2 * i - 1].nxt = G[v];
            e[2 * i - 1].v = u;
            e[2 * i - 1].w = w;
            G[v] = 2 * i - 1;
        }

        while (q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", dfs(u, v, 0, 0));
        }
    }
    return 0;
}
