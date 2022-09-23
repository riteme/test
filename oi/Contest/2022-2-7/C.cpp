#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 1000;
constexpr int MMAX = 5000;
constexpr int INF = 0x3f3f3f3f;

int n, m;
int p[MMAX + 10];
int f[NMAX + 10][MMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        p[x]++;
    }
    for (int i = 1; i <= m; i++) {
        p[i] += p[i - 1];
    }

    for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++) {
        f[i][j] = -INF;
    }

    f[n][m] = 0;

    for (int i = n; i >= 1; i--)
    for (int j = m; j >= 0; j--)
    for (int k = 0; k * i <= j; k++) {
        f[i - 1][j - k] = max(f[i - 1][j - k], f[i][j] + p[k]);
    }

    printf("%.12lf\n", static_cast<double>(f[0][0]) / n);

    return 0;
}
