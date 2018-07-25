#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100

static int n, m;
static int W[NMAX + 10][NMAX + 10];
static i64 C[NMAX + 10][NMAX + 10];
static double f[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    memset(W, 0x3f, sizeof(W));
    for (int i = 1; i <= n; i++) {
        W[i][i] = 0;
        C[i][i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        i64 w;
        scanf("%d%d%lld", &u, &v, &w);
        W[u][v] = W[v][u] = w;
        C[u][v] = C[v][u] = 1;
    }
}

int main() {
    freopen("network1.in", "r", stdin);
    freopen("network1.out", "w", stdout);
    initialize();

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (k == i || k == j)
                    continue;

                if (W[i][k] + W[k][j] < W[i][j]) {
                    W[i][j] = W[i][k] + W[k][j];
                    C[i][j] = C[i][k] * C[k][j];
                } else if (W[i][k] + W[k][j] == W[i][j]) {
                    C[i][j] += C[i][k] * C[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (k == i || k == j)
                    continue;

                if (W[i][k] + W[k][j] == W[i][j])
                    f[k] += (double) C[i][k] * C[k][j] / C[i][j];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%.3lf\n", f[i]);
    }

    return 0;
}

