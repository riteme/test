#include <cstdio>
#include <string>

#define MOD 65537

static int n, m, f[10000];

int main() {
    scanf("%d%d", &n, &m);

    f[0] = 1;
    for (int i = 1; i < m; i++) {
        f[i] = f[i - 1] * 2 % MOD;
    }

    for (int i = m; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i] = (f[i] + f[i - j]) % MOD;
        }
    }

    printf("%d\n", f[n]);

    return 0;
}
