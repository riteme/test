// FAKE
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200

static int n;
static int a[NMAX + 10];
static i64 f[NMAX + 10][NMAX + 10][NMAX + 10];

int main() {
    int _;
    while (scanf("%d", &_) != EOF)
        a[++n] = _;
    //scanf("%d", &n);
    //for (int i = 1; i <= n; i++)
    //    scanf("%d", a + i);
    printf("n = %d\n", n);
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++)
        if (a[j] == a[i])
            f[i][j + 1][i + 1] = 1;
        for (int j = 1; j < i; j++)
        for (int k = i; k <= n; k++)
        if (f[i][j][k]) {
            for (int p = j; p < i; p++)
            if (a[p] == a[k])
                f[i][p + 1][k + 1] += f[i][j][k];
            f[i][j][k + 1] += f[i][j][k];
        }
        for (int j = 1; j < i; j++)
            f[i][i][n + 1] += f[i][j][n + 1];
        for (int k = i; k <= n; k++)
            f[i][i][n + 1] += f[i][i][k];
        //printf("f[%d][%d][%d] = %lld\n", i, i, n + 1, f[i][i][n + 1]);
        ans += f[i][i][n + 1];
    }
    printf("%lld\n", ans);
    return 0;
}
