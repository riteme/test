#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 50
#define INVMAX 10000
#define MOD 998244353

template <typename T>
inline T c2(T x) {
    return x * (x + 1) >> 1;
}

static int n, sz[NMAX + 10], cnt[NMAX + 10];
static vector<int> G[NMAX + 10];
static i64 f[NMAX + 10][2][NMAX + 10][NMAX * NMAX][2];
static i64 inv[INVMAX];

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) for (int c = 0; c < 2; c++) for (int j = 0; j <= n; j++)
    for (int k = 0; k <= c2(n); k++) for (int d = 0; d < 2; d++)
        f[i][c][j][k][d] = -1;
}

void finalize() {
    for (int i = 1; i <= n; i++)
        G[i].clear();
}

#define add(x, y) x = ((x < 0 ? 0 : x) + y) % MOD

// inline void add(i64 &dest, i64 src) {
//     if (dest < 0) dest = 0;
//     dest += src;
//     if (dest >= MOD) dest -= MOD;
// }

inline bool ok(int i, int c, int j, int k, int d) {
    return j >= 0 && k >= 0 && f[i][c][j][k][d] >= 0;
}

void dfs(int x, int u) {
    sz[x] = 1;
    for (int v : G[x]) {
        if (v == u) continue;
        dfs(v, x);
        sz[x] += sz[v];
    }
}

void dp(int x, int u) {
    f[x][cnt[x]][1][1][0] = f[x][cnt[x]][0][0][1] = 1;
    for (int v : G[x]) {
        if (v == u) continue;
        dp(v, x);
    }

    if (!u) return;

    cnt[u] ^= 1;
    for (int j = 0; j <= sz[u]; j++)
    for (int k = 0; k <= c2(sz[u]); k++)
    for (int d = 0; d < 2; d++)
        f[u][cnt[u]][j][k][d] = -1;

    int c = cnt[u] ^ 1;
    for (int j = 0; j <= sz[x]; j++)
    for (int k = 0; k <= c2(sz[x]); k++)
    for (int d = 0; d < 2; d++) {
        if (!ok(x, cnt[x], j, k, d)) continue;
        for (int J = max(1, j); J <= sz[u]; J++)
        for (int K = max(1, k); K <= c2(sz[u]); K++)
        for (int D = 0; D < 2; D++) {
            int pj = J - j, pk = K - k - j * (J - j);
            if (pj >= 1 && ok(u, c, pj, pk, D ^ d)) {
                // printf("A: (%d, %d, %d, %d) * (%d, %d, %d, %d) -> (%d, %d, %d, %d) +%lld\n",
                //         x, j, k, d, u, pj, pk, D ^ d, u, J, K, D, f[x][cnt[x]][j][k][d] * f[u][c][pj][pk][D ^ d]);
                add(f[u][c ^ 1][J][K][D], f[x][cnt[x]][j][k][d] * f[u][c][pj][pk][D ^ d]);
            }
        }

        for (int K = 0; K <= c2(sz[u]); K++)
        for (int D = 0; D < 2; D++) {
            if (ok(u, c, 0, K - k, D ^ d)) {
                // printf("B: (%d, %d, %d, %d) * (%d, %d, %d, %d) -> (%d, %d, %d, %d) +%lld\n",
                //         x, j, k, d, u, 0, K - k, D ^ d, u, 0, K, D, f[x][cnt[x]][j][k][d] * f[u][c][0][K - k][D ^ d]);
                add(f[u][c ^ 1][0][K][D], f[x][cnt[x]][j][k][d] * f[u][c][0][K - k][D ^ d]);
            }
        }
    }
}

int main() {
    inv[1] = 1;
    for (int i = 2; i < INVMAX; i++)
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;

    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        initialize();
        dfs(1, 0);
        dp(1, 0);

        i64 ans = 0, A = c2(n);
        for (int j = 0; j <= n; j++)
        for (int k = 0; k <= A; k++)
        for (int d = 0; d < 2; d++) {
            if (!ok(1, cnt[1], j, k, d)) continue;
            // printf("f(%d, %d, %d, %d) = %lld\n", 1, j, k, d, f[1][cnt[1]][j][k][d]);
            ans = (ans + f[1][cnt[1]][j][k][d] * inv[A - k] * (d ? 1 : -1)) % MOD;
        }

        ans = ans * A % MOD;
        if (ans < 0) ans += MOD;
        printf("Case #%d: %lld\n", t, ans);

        finalize();
    }

    return 0;
}
