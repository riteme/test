#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n;
int x[NMAX + 10], y[NMAX + 10];
int f[NMAX + 10][NMAX + 10];
int g[NMAX + 10][NMAX + 10];

void solve() {
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", x + i, y + i);
        f[i][i] = x[i] + y[i];
        g[i][i] = i;
    }

    for (int l = 2; l <= n; l++)
    for (int i = 1; i + l - 1 <= n; i++) {
        int j = i + l - 1;
        f[i][j] = INT_MAX;
        for (int k = g[i][j - 1]; k <= g[i + 1][j] && k < j; k++) {
            int v = f[i][k] + f[k + 1][j];
            if (v < f[i][j]) {
                f[i][j] = v;
                g[i][j] = k;
            }
        }
        f[i][j] -= x[i] + y[j];
    }

    int ans = f[1][n] - x[1] - y[n];
    printf("%d\n", ans);
}

int main() {
    while (scanf("%d", &n) != EOF)
        solve();
    return 0;
}