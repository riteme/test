#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 5000
#define MOD 1000000007

typedef long long i64;
typedef i64 dp[NMAX + 10][NMAX + 10];

int n, m;
dp f, g, gk;

void add(i64 &a, i64 b) {
    a = (a + b) % MOD;
}

int main() {
    scanf("%d%d", &n, &m);

    for (int j = 1; j <= n; j++) {
        f[0][j] = 1;
        g[j][j] = 1;
        gk[j][j] = j;
    }
    for (int i = 0; i <= m; i++) {
        f[i][1] = 1;
        g[i + 1][1] = 1;
        gk[i + 1][1] = 1;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 2; j <= n; j++) {
            add(g[i][j], g[i][j - 1]);
            add(gk[i][j], gk[i][j - 1]);
        }
        for (int j = 2; j <= n; j++) {
            int R = min(i, j);
            f[i][j] = ((j + 1) * g[i][R] - gk[i][R]) % MOD;
            if (i + j <= m) {
                add(g[i + j][j], f[i][j]);
                add(gk[i + j][j], f[i][j] * j);
            }
        }
    }
    printf("%lld\n", f[m - n][n]);
    return 0;
}