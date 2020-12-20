#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 3000;

int n, m;
double a[NMAX + 10], s[NMAX + 10];
double f[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", a + i);
    }
    sort(a + 1, a + n + 1, [](double x, double y) {
        return x > y;
    });

    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i - 1][0] + a[i];
    }

    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
        double d1 = f[i - 1][j];
        double d2 = f[i - 1][j - 1];
        double mi = (d1 + d2 + a[i]) / 2;
        f[i][j] = mi;
        // if (d1 <= mi && mi <= d1 + a[i])
        // else
            // f[i][j] = d1 + a[i];
    }

    printf("%.6lf\n", f[n][m]);
    return 0;
}