#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

typedef long long i64;

int n, m, a, b;
i64 mat[NMAX + 10][NMAX + 10];
i64 sum[NMAX + 10][NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &n, &m, &a, &b);
        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lld", &mat[i][j]);

        bool ok = true;
        if (a == 1 && b == 1)
            goto aha;

        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            i64 cnt = sum[i][j];
            if (i >= a) cnt -= sum[i - a][j];
            if (j >= b) cnt -= sum[i][j - b];
            if (i >= a && j >= b) cnt += sum[i - a][j - b];
            if (cnt > mat[i][j]) {
                ok = false;
                goto aha;
            } else {
                mat[i][j] -= cnt;
                sum[i][j] += mat[i][j];
            }
        }
        ok &= mat[n][m] == 0;

        aha: puts(ok ? "^_^" : "QAQ");
    }

    return 0;
}