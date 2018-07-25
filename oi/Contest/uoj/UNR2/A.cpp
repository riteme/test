#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 400
#define MOD 998244353

typedef long long i64;

static int n, k;
static i64 w[NMAX + 10][NMAX + 10];
static i64 f[NMAX + 10][NMAX + 10];
static i64 g[NMAX + 10][NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", w[i] + 1);

        for (int j = 2; j <= n; j++) {
            w[i][j] = w[i][j - 1] * w[i][1] % MOD;
        }
    }
}

#define rep(x, l, r) for (int x = l; x <= r; x++)
#define add(a, b) a += b % MOD; if (a >= MOD) a -= MOD;

int main() {
    initialize();

    rep(x, 0, n) {
        g[0][x] = 1;
    }

    rep(i, 1, k - 1) rep(x, 1, n) {
        g[i][x] = g[i - 1][x] * x % MOD;
    }

    rep(i, k, n) rep(x, 1, n) {
        rep(j, 1, i) {
            int minl = max(1, j - k + 1), maxl = min(j, i - k + 1);
            int t = maxl - minl + 1;
            // printf("j = %d, t = %d\n", j, t);
            add(f[i][x], g[j - 1][x - 1] * g[i - j][x] % MOD * w[x][t]);
        }

        g[i][x] = (g[i][x - 1] + f[i][x]) % MOD;
    }

    printf("%lld\n", g[n][n]);

    return 0;
}
