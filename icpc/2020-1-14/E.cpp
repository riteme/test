#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 3000
#define INF 0x3f3f3f3f3f3f3f3f

void chkmin(i64 &a, i64 b) {
    if (a > b) a = b;
}

int n;
int M[NMAX + 10], F[NMAX + 10];
i64 f[2][2 * NMAX + 10][4];

int main() {
    scanf("%d", &n);
    i64 sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", M + i, F + i);
        sum += M[i];
    }

    if (sum == 0)
        return puts("0"), 0;

    memset(f, 0x3f, sizeof(f));
    f[0][NMAX][0] = 0;
    int p = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < NMAX + n; j++)
        for (int s = 0; s < 4; s++)
        if (f[p][j][s] < INF) {
            chkmin(
                f[p^1][j + (M[i] ? 0 : 1)][s | 1],
                f[p][j][s] + F[i] + max(0, M[i] - 1));

            int k = min(M[i], j);
            chkmin(
                f[p^1][j - k][s | 2],
                f[p][j][s] + 2 * M[i] - k);
        }
        memset(f[p], 0x3f, sizeof(f[p]));
        p ^= 1;
    }

    i64 ans = INF;
    for (int j = 0; j <= NMAX; j++)
        chkmin(ans, f[p][j][3] + NMAX - j);
    printf("%lld\n", ans);
    return 0;
}
