#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 5000

static int m, A, B, C;
static struct Point {
    int x, y, z;
} p[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &A, &B, &C);
    m = 0;
    for (int x = 0; x < A; x++)
    for (int y = 0; y < B; y++)
    for (int z = 0; z < C; z++) {
        int v;
        scanf("%d", &v);
        if (v) p[m++] = {x, y, z};
    }
}

static int n, G[NMAX + 10][NMAX + 10];
static bool vis[NMAX + 10];
static int mc[NMAX + 10];

void link(int u, int v) {
    G[u][++G[u][0]] = v;
    G[v][++G[v][0]] = u;
}

int dfs(int x) {
    vis[x] = true;
    for (int i = 1; i <= G[x][0]; i++) {
        int v = G[x][i];
        if (v == mc[x])
            continue;
        if (!mc[v] || (!vis[mc[v]] && dfs(mc[v]))) {
            mc[x] = v;
            mc[v] = x;
            return 1;
        }
    }
    return 0;
}

int eval(int n0) {
    memset(mc + 1, 0, sizeof(int) * n);

    int ret = 0;
    for (int i = 1; i <= n0; i++) if (!mc[i]) {
        memset(vis + 1, 0, n);
        ret += dfs(i);
    }

    return ret;
}

void solve() {
    initialize();

    int ans = INT_MAX;

#define ALGO(A, B, C, x, y, z) \
    n = B + C; \
    for (int S = 0; S < (1 << A); S++) { \
        int cnt = S ? __builtin_popcount(S) : 0; \
        for (int i = 1; i <= n; i++) \
            G[i][0] = 0; \
        for (int i = 0; i < m; i++) if (!((S >> p[i].x) & 1)) \
            link(p[i].y + 1, B + p[i].z + 1); \
        cnt += eval(B); \
        ans = min(ans, cnt); \
    }

    if (A <= B && A <= C) {
        ALGO(A, B, C, x, y, z);
    } else if (B <= A && B <= C) {
        ALGO(B, A, C, y, x, z);
    } else {
        ALGO(C, A, B, z, x, y);
    }

    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
