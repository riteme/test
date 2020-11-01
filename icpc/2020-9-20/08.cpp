#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 50
#define INF 1e99

int n, x0, K[NMAX + 10];
double L[1000];
double f[NMAX + 10][NMAX + 10][NMAX + 10][2];

template <typename T>
void chkmin(T &a, T b) {
    if (a > b)
        a = b;
}

int pos(int i, int u) {
    return (i & 1 ? 0 : 1) + 2 * (-i / 2 + u - 1);
}

void _main() {
    scanf("%d%d", &n, &x0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", K + i);
    }

    for (int i = 1; i <= n; i++)
    for (int l = 1; l <= i; l++)
    for (int r = l; r <= i; r++)
    for (int b = 0; b < 2; b++) {
        f[i][l][r][b] = 0;
    }
    f[1][1][1][0] = 1;

    for (int i = 2; i <= n; i++)
    for (int c = i; c >= 1; c--)
    for (int l = 1; l + c - 1 <= i; l++)
    for (int b = 0; b < min(2, c); b++) {
        int r = l + c - 1;

        if (c - 1 + K[i] > i) {
            f[i][l][r][b] = INF;
            continue;
        }

        int u = b ? r : l;
        double p = (double) K[i] / max(K[i], i - c + 1);

        double mi = INF;
        if (l > 1)
            chkmin(mi, 2 * abs(u - l + 1) + f[i][l - 1][r][0]);
        if (r < i)
            chkmin(mi, 2 * abs(u - r - 1) + f[i][l][r + 1][1]);
        f[i][l][r][b] += (1 - p) * mi;

        for (int v = 1; v < i; v++) {
            chkmin(mi, L[abs(pos(i, u) - pos(i - 1, v))] + f[i - 1][v][v][0]);
        }
        f[i][l][r][b] += p * mi;
    }

    double ans = INF;
    for (int i = 1; i <= n; i++) {
        int x1 = pos(n, i);
        double d = L[abs(x0 - x1)];
        chkmin(ans, d + f[n][i][i][0]);
    }

    /*
    for (int i = 1; i <= n; i++)
    for (int l = 1; l <= i; l++)
    for (int r = l; r <= i; r++) {
        printf("f[%d][(%d) %d] = %.3lf\n",
            i, l, r, f[i][l][r][0]);

        if (l < r) {
            printf("f[%d][%d (%d)] = %.3lf\n",
                i, l, r, f[i][l][r][1]);
        }
    }
    */

    printf("%.10lf\n", ans);
}

int main() {
    for (int i = 0; i < 1000; i++) {
        L[i] = hypot(i, 1);
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
