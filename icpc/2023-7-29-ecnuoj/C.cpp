#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 3000;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n;
i64 a[NMAX + 10];
i64 f[NMAX + 10][NMAX + 10][2];
i64 g[NMAX + 10][2];
int sz[NMAX + 10];

void dp(int i, int x) {
    for (int j = 0; j <= sz[i]; j++) {
        g[j][0] = g[j][1] = -INF;
    }
    for (int j = 0; j <= sz[i]; j++) {
        for (int k = 0; k <= sz[x]; k++) {
            if (j + k > sz[i])
                continue;
            g[j + k][0] =
                max({g[j + k][0], f[i][j][0] + f[x][k][0] + a[x], f[i][j][0] + f[x][k][1]});
            g[j + k][1] =
                max({g[j + k][1], f[i][j][1] + f[x][k][0], f[i][j][1] + f[x][k][1] + a[x]});
        }
    }
    for (int j = 0; j <= sz[i]; j++) {
        f[i][j][0] = g[j][0];
        f[i][j][1] = g[j][1];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }

    for (int i = 1; i <= n; i++) {
        sz[i] = 1;
    }
    for (int i = n; i >= 1; i--) {
        if (2 * i <= n)
            sz[i] += sz[2 * i];
        if (2 * i + 1 <= n)
            sz[i] += sz[2 * i + 1];
    }

    for (int i = n; i >= 1; i--) {
        for (int j = 0; j <= sz[i]; j++) {
            f[i][j][0] = f[i][j][1] = -INF;
        }
        f[i][0][0] = 0;
        f[i][1][1] = 0;

        int x = 2 * i;
        if (x <= n)
            dp(i, x);
        x = 2 * i + 1;
        if (x <= n)
            dp(i, x);
    }

    i64 ans = max(f[1][n / 2][0], f[1][n / 2][1]);
    printf("%lld\n", ans);
    return 0;
}
