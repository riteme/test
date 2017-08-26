#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define MOD 998244353
#define TMAX 64
#define OFF 32

typedef long long i64;

static int T, N, K;
static bool m[65][65];
static i64 f[65][65][31][31];
static i64 g[2][65][65][65][65];
static i64 c[65][65][31], h[65][65][31];

#define rep(var, l, r) for (int var = l; var <= r; var++)

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int main() {
    scanf("%d%d%d", &T, &N, &K);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        m[x + OFF][y + OFF] = true;
    }

    int cur = 1, last = 0, l = OFF - T - 1, r = OFF + T + 1;
    f[OFF][OFF][0][1] = 1;
    rep(x, l, r) rep(y, l, r) {
        if (m[x][y])
            continue;

        h[x][y][0] = 1;
        g[0][x][y][x][y] = 1;
    }

    rep(i, 1, T) {
        memset(g[cur], 0, sizeof(g[cur]));

        rep(x0, l, r) rep(y0, l, r) rep(x1, l, r) rep(y1, l, r) {
            if (m[x0][y0] || m[x1][y1])
                continue;

            i64 &r = g[cur][x0][y0][x1][y1];
            add(r, g[last][x0][y0][x1 - 1][y1]);
            add(r, g[last][x0][y0][x1 + 1][y1]);
            add(r, g[last][x0][y0][x1][y1 - 1]);
            add(r, g[last][x0][y0][x1][y1 + 1]);
        }

        rep(x, l, r) rep(y, l, r) {
            if (i != 1)
                c[x][y][i] = g[cur][x][y][x][y];
            if (x != OFF || y != OFF)
                f[x][y][i][1] = g[cur][OFF][OFF][x][y];

            g[cur][x][y][x][y] = 0;
            rep(x0, l, r) rep(y0, l, r) {
                add(h[x][y][i], g[cur][x][y][x0][y0]);
            }
        }

        swap(cur, last);
    }

    rep(i, 0, T) {
        printf("%d:\n", i);
        rep(x, l, r) {
            rep(y, l, r) {
                printf("%lld ", h[x][y][i]);
            }
            printf("\n");
        }
    }

    i64 ans = 0;
    rep (x, l + 1, r - 1) rep(y, l + 1, r - 1) {
        rep(i, 0, T) rep(k, 1, T) {
            rep(j, 1, i) {
                add(f[x][y][i][k], f[x][y][i - j][k - 1] * c[x][y][j] % MOD);
            }

            if (k >= K)
                add(ans, f[x][y][i][k] * h[x][y][T - i] % MOD);
        }
    }

    printf("%lld\n", ans);

    return 0;
}
