#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10000
#define MMAX 1000
#define INFTY 100000000

static int n, m, tc;
static int X[NMAX + 10];
static int Y[NMAX + 10];
static int L[NMAX + 10];
static int R[NMAX + 10];
static int f[NMAX + 10][MMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &tc);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", X + i, Y + i);
    }  // for

    for (int i = 0; i < tc; i++) {
        int p, l, r;
        scanf("%d%d%d", &p, &l, &r);

        L[p] = l;
        R[p] = r;
    }  // for
}

int main() {
    initialize();

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            f[i][j] = INFTY;

    for (int i = 1; i <= m; i++)
        f[0][i] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j == m)
                for (int k = max(1, j - X[i - 1]); k <= m; k++)
                    f[i][j] = min(f[i][j], min(f[i][k], f[i - 1][k]) + 1);
            else if (j > X[i - 1])
                f[i][j] =
                    min(f[i][j],
                        min(f[i - 1][j - X[i - 1]], f[i][j - X[i - 1]]) + 1);
        }  // for

        for (int j = m - Y[i - 1]; j > 0; j--)
            f[i][j] = min(f[i][j], f[i - 1][j + Y[i - 1]]);

        if (L[i] < R[i]) {
            for (int j = 0; j <= L[i]; j++)
                f[i][j] = INFTY;
            for (int j = m; j >= R[i]; j--)
                f[i][j] = INFTY;
        }
    }  // for

    bool ok = true;
    int answer = INFTY;

    for (int j = 1; j <= m; j++)
        answer = min(answer, f[n][j]);

    if (answer == INFTY) {
        ok = false;
        int x;
        for (int i = n; i >= 0; i--) {
            bool flag = false;
            for (int j = 0; j <= m && !flag; j++)
                if (f[i][j] < INFTY)
                    flag = true;

            if (flag) {
                x = i;
                break;
            }
        }  // for

        answer = 0;
        for (int i = 0; i <= x; i++)
            if (L[i] < R[i])
                answer++;
    }

    printf("%d\n%d\n", (ok ? 1 : 0), answer);

    return 0;
}  // function main
