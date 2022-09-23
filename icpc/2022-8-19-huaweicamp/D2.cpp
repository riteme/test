#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 5000;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n, m;
int a[NMAX + 10];
i64 f[NMAX + 10][NMAX + 10][2];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    sort(a + 1, a + n + 1);
    m = a[n];
    memset(f, 0x3f, sizeof(f));
    f[1][1][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 2; k++) {
                if (k)
                    f[i][j + 1][0] = min(f[i][j + 1][0], f[i][j][k]);
                f[i + 1][j][1] = min(f[i + 1][j][1], f[i][j][k] + abs(a[i] - j));
            }
        }
    }
    i64 ans = INF;
    for (int j = 1; j <= m; j++) {
        ans = min(ans, f[n + 1][j][1]);
    }
    printf("%lld\n", ans);
    return 0;
}
