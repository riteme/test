#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 50

typedef long long int64;

static int n, m;
static int64 w[NMAX + 10][NMAX + 10];
static int64 pre[NMAX + 10][NMAX + 10];
static int64 f[NMAX + 10][NMAX + 10][NMAX * NMAX + 100];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n - i + 1; j++)
            scanf("%lld", &w[i][j]);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n - i + 1; j++)
            pre[i][j] += pre[i - 1][j] + w[i][j];
}

int main() {
    freopen("tec.in", "r", stdin);
    freopen("tec.out", "w", stdout);
    initialize();

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j <= n - i + 1; j++) {
            for (int k = 1; k <= m; k++) {
                if (k < j)
                    continue;

                if (j > 0)
                    f[j][i][k] = max(f[j][i][k],
                        f[j - 1][i][k - 1] + w[j][i]
                    );

                if (i > 1 && k >= j) {
                    f[j][i][k] = max(f[j][i][k],
                        f[j][i - 1][k - j] + pre[j][i]
                    );
                    f[j][i][k] = max(f[j][i][k],
                        f[j + 1][i - 1][k - j] + pre[j][i]
                    );
                }
            }
        }
    }

    printf("%lld\n", f[0][n + 1][m]);

    return 0;
}
