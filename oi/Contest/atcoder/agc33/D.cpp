#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 185

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define rrep(i, r, l) for (int i = (r); i >= (l); i--)

static int n, m;
static char mat[NMAX + 10][NMAX + 10];
static int row[NMAX + 10][NMAX + 10][NMAX + 10];
static int col[NMAX + 10][NMAX + 10][NMAX + 10];

inline void chkmin(int &a, int b) {
    if (a > b) a = b;
}

static int dp[NMAX + 10][NMAX + 10];
int solve(int lx, int rx, int ly, int ry, int d = 0) {
    rep(i, 1, d) fputc(' ', stderr);
    fprintf(stderr, "[%d, %d]x[%d, %d]\n", lx, rx, ly, ry);

    if (lx == rx) return row[lx][ly][ry];
    if (ly == ry) return col[ly][lx][rx];
    int ret = 0x3f3f3f3f, p = -1, lv, rv;

    memset(dp, 0x3f, sizeof(dp));
    rep(i, ly, ry) dp[i][i] = col[i][lx][rx];
    rep(l, ly, ry) rep(r, l + 1, ry) rep(k, l, r - 1) {
        if (!dp[l][k] && !dp[k + 1][r] && mat[lx][l] == mat[lx][r]) {
            dp[l][r] = 0;
            p = k;
        } else
            chkmin(dp[l][r], max(dp[l][k], dp[k + 1][r]) + 1);
    }
    rep(i, ly, ry - 1) if (max(dp[ly][i], dp[i + 1][ry]) + 1 == dp[ly][ry]) p = i;
    lv = solve(lx, rx, ly, p, d + 1);
    rv = solve(lx, rx, p + 1, ry, d + 1);
    if (!lv && !rv && mat[lx][ly] == mat[lx][ry]) ret = 0;
    else chkmin(ret, max(lv, rv) + 1);

    memset(dp, 0x3f, sizeof(dp));
    p = -1;
    rep(i, lx, rx) dp[i][i] = row[i][ly][ry];
    rep(l, lx, rx) rep(r, l + 1, rx) rep(k, l, r - 1) {
        if (!dp[l][k] && !dp[k + 1][r] && mat[l][ly] == mat[r][ly]) {
            dp[l][r] = 0;
            p = k;
        } else
            chkmin(dp[l][r], max(dp[l][k], dp[k + 1][r]) + 1);
    }
    rep(i, lx, rx - 1) if (max(dp[lx][i], dp[i + 1][rx]) + 1 == dp[lx][rx]) p = i;
    lv = solve(lx, p, ly, ry, d + 1);
    rv = solve(p + 1, rx, ly, ry, d + 1);
    if (!lv && !rv && mat[lx][ly] == mat[rx][ly]) ret = 0;
    else chkmin(ret, max(lv, rv) + 1);

    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) scanf("%s", mat[i] + 1);
    memset(row, 0x3f, sizeof(row));
    memset(col, 0x3f, sizeof(col));
    rep(i, 1, n) rep(j, 1, m)
        row[i][j][j] = col[j][i][i] = 0;
    rep(i, 1, n) rep(l, 1, m) {
        rep(r, l + 1, m) rep(k, l, r - 1) {
            if (!row[i][l][k] && !row[i][k + 1][r] && mat[i][l] == mat[i][r])
                row[i][l][r] = 0;
            else
                chkmin(row[i][l][r], max(row[i][l][k], row[i][k + 1][r]) + 1);
        }
    }
    rep(i, 1, m) rep(l, 1, n) {
        rep(r, l + 1, n) rep(k, l, r - 1) {
            if (!col[i][l][k] && !col[i][k + 1][r] && mat[l][i] == mat[r][i])
                col[i][l][r] = 0;
            else
                chkmin(col[i][l][r], max(col[i][l][k], col[i][k + 1][r]) + 1);
        }
    }
    printf("%d\n", solve(1, n, 1, m));
    return 0;
}
