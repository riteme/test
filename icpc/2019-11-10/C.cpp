#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef unsigned long long u64;

struct Edge {
    int v;
    u64 w;
};

static int n;
static vector<Edge> G[NMAX + 10];
static u64 f[NMAX + 10][2], g[NMAX + 10][2];

void dfs(int x, int k, int fa) {
    f[x][1] = g[x][1] = 0;
    f[x][0] = g[x][0] = 1;
    for (auto &e : G[x]) if (e.v != fa) {
        int v = e.v;
        dfs(v, k, x);
        int b = (e.w >> k) & 1;
        g[x][b] += f[x][0] * f[v][0] + f[x][1] * f[v][1];
        g[x][b ^ 1] += f[x][0] * f[v][1] + f[x][1] * f[v][0];
        g[x][0] += g[v][0];
        g[x][1] += g[v][1];
        f[x][b] += f[v][0];
        f[x][b ^ 1] += f[v][1];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        u64 w;
        scanf("%d%d%llu", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    u64 ans = 0;
    for (int k = 0; k < 32; k++) {
        dfs(1, k, 0);
        //fprintf(stderr, "g[%d] = %llu\n", k, g[1][1]);
        ans += (1ULL << k) * g[1][1];
    }
    printf("%llu\n", ans);
    return 0;
}
