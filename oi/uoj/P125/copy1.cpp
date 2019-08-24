// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 150
#define MMAX 500
#define INFTY 0xbfbfbfbf

#define chkmax(dest, src) if (src > dest) dest = src;
#define val(i, l, r) (pre[i][r] - pre[i][l - 1])
#define rep \
    for (int j = 1; j <= n; j++) \
        for (int k = j; k <= n; k++)

static int n, m;
static int mat[MMAX + 1][NMAX + 1];
static int pre[MMAX + 1][NMAX + 1];
static int f[2][11][NMAX + 1][NMAX + 1];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &mat[j][i]);
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] = pre[i][j - 1] + mat[i][j];
        }
    }

    memset(f, 0xbf, sizeof(f));
}

int main() {
    initialize();
    int last = 0, cur = 1;

    int answer = INFTY;
    for (int i = 1; i <= m; i++) {
        memset(f[cur], 0xbf, sizeof(f[cur]));

        // 0 N
        rep {
            f[cur][0][j][k] = max(0, f[last][0][j][k]) + val(i, j, k);
        }

        // 1 N
        rep {
            int &r = f[cur][1][j][k];

            for (int d = k + 1; d <= n; d++) {
                chkmax(r, f[last][0][j][d]);
            }

            for (int u = 1; u <= j; u++) {
                for (int d = max(u, j - 1); d <= k; d++) {
                    chkmax(r, f[last][1][u][d]);
                }
            }

            r += val(i, j, k);
        }

        // 2 N
        rep {
            int &r = f[cur][2][j][k];

            for (int u = j + 1; u <= k; u++) {
                chkmax(r, f[last][1][u][k]);
            }

            chkmax(r, f[last][2][j][k]);
            r += val(i, j, k);
        }

        // 3 N O
        for (int i = 1; i <= m; i++) {
            int &r = f[cur][3][1][1];

            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    chkmax(r, f[last][2][j][k]);
                }
            }

            chkmax(r, f[last][3][1][1]);
        }

        // 4 O
        rep {
            if (k - j < 2)
                continue;

            f[cur][4][j][k] = f[last][3][1][1] + val(i, j, k);
        }

        // 5 O
        rep {
            if (k - j < 2)
                continue;

            int &r = f[cur][5][j][k];

            chkmax(r, f[last][4][j][k]);
            chkmax(r, f[last][5][j][k]);

            r += mat[i][j] + mat[i][k];
        }

        // 6 O
        rep {
            if (k - j < 2)
                continue;

            f[cur][6][j][k] = f[last][5][j][k] + val(i, j, k);
        }

        // 7 O I
        for (int i = 1; i <= m; i++) {
            int &r = f[cur][7][1][1];

            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    chkmax(r, f[last][6][j][k]);
                }
            }

            chkmax(r, f[last][7][1][1]);
        }

        // 8 I
        rep {
            if (k - j < 2)
                continue;

            int &r = f[cur][8][j][k];

            chkmax(r, f[last][7][1][1]);
            chkmax(r, f[last][8][j][k]);

            r += mat[i][j] + mat[i][k];
        }

        // 9 I
        rep {
            if (k - j < 2)
                continue;

            int &r = f[cur][9][j][k];

            chkmax(r, f[last][8][j][k]);
            chkmax(r, f[last][9][j][k]);

            r += val(i, j, k);
        }

        // 10 I
        rep {
            if (k - j < 2)
                continue;

            int &r = f[cur][10][j][k];

            chkmax(r, f[last][9][j][k]);
            chkmax(r, f[last][10][j][k]);

            r += mat[i][j] + mat[i][k];
            chkmax(answer, r);
        }

        swap(last, cur);
    }

    printf("%d\n", answer);

    return 0;
}
