#include <cstdio>
#include <cstring>
#include <cassert>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 10000
#define INF 0x3f3f3f3f

int n, c0[NMAX + 10];
vector<int> G[NMAX + 10];
int f[NMAX + 10][2][2][2][2];
// f(x, color, req, long, mark)
// req & mark = 0
// req = 0 => long = 0

void chkmin(int &a, int b) {
    if (a > b)
        a = b;
}

void dp(int x, int p) {
    for (int c = 0; c < 2; c++)
    for (int r = 0; r < 2; r++)
    for (int l = 0; l < 2; l++)
    for (int m = 0; m < 2; m++) {
        f[x][c][r][l][m] = INF;
    }
    f[x][c0[x]][0][0][0] = 0;
    f[x][c0[x] ^ 1][1][0][0] = 0;
    //f[x][c0[x] ^ 1][0][0][1] = 1;

    for (int _ = 0; _ < G[x].size(); _++) {
        int v = G[x][_];
        if (v == p)
            continue;

        dp(v, x);
        int t[2][2][2][2];
        memset(t, INF, sizeof(t));

        for (int c = 0; c < 2; c++)
        for (int xr = 0; xr < 2; xr++)
        for (int xl = 0; xl < 2; xl++)
        if (!xl || xr)
        for (int xm = 0; xm < 2; xm++)
        if ((xr & xm) == 0)
        for (int vr = 0; vr < 2; vr++)
        for (int vl = 0; vl < 2; vl++)
        if (!vl || vr)
        for (int vm = 0; vm < 2; vm++)
        if ((vr & vm) == 0) {
            int a = f[x][c][xr][xl][xm] + f[v][c][vr][vl][vm];

            if (xr && vr) {
                if (xl == 0)
                    chkmin(t[c][1][1][0], a);
                chkmin(t[c][0][0][1], a + 1);
            } else if (xr) {
                chkmin(t[c][1][xl][0], a);
                chkmin(t[c][0][0][1], a + 1);
            } else if (vr) {
            } else {
                chkmin(t[c][0][0][xm], a);
            }
        }

        memcpy(&f[x][0][0][0][0], t, sizeof(t));
    }

    for (int c = 0; c < 2; c++)
    /* r = 1 */
    for (int l = 0; l < 2; l++)
    /* m = 0 */ {
        chkmin(f[x][c][0][0][1], f[x][c][1][l][0] + 1);
    }

    int t[2][2][2][2];
    memcpy(t, &f[x][0][0][0][0], sizeof(t));
    for (int c = 0; c < 2; c++)
    for (int r = 0; r < 2; r++)
    for (int l = 0; l < 2; l++)
    for (int m = 0; m < 2; m++) {
        chkmin(t[c ^ 1][r][l][m], f[x][c][r][l][m] + 1);
    }
    memcpy(&f[x][0][0][0][0], t, sizeof(t));
}

void _main() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", c0 + i);
    }

    dp(1, 0);

    int ans = min(
        min(f[1][0][0][0][0], f[1][0][0][0][1]),
        min(f[1][1][0][0][0], f[1][1][0][0][1])
    );
    printf("%d\n", ans);
}

int main() {
    int t = 1;
    while (scanf("%d", &n) != EOF) {
        printf("Case %d: ", t);
        t++;
        _main();
    }
    return 0;
}
