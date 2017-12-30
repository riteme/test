#include <cstdio>
#include <string>

#define MOD 65537

static int n, m, f[10000][100];

int main() {
    scanf("%d%d", &n, &m);

    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            f[i][j] = f[i - 1][j - 1];
        }
        for (int j = 0; j < m; j++) {
            f[i][0] += f[i - 1][j];
            f[i][0] %= MOD;
        }
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        ans += f[n][i];
        ans %= MOD;
    }

    printf("%d\n", ans);
    return 0;
}
