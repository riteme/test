#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 30

typedef long long i64;

#define rep(i, l, r) for(int i = (l); i <= (r); i++)

static int n, m;
static i64 MOD, pw[NMAX * NMAX + 10], g[2*NMAX + 1];
static i64 c[NMAX + 10][NMAX + 10];
static i64 f[2*NMAX + 1][NMAX + 1][NMAX + 1][NMAX + 1];

inline void add(i64 &a, i64 b) {
    a = (a + b) % MOD;
}

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

int main(int /*argc*/, char * /*argv*/[]) {
    int T = 1;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%lld", &n, &m, &MOD);
        //n = atoi(argv[1]);
        //m = atoi(argv[2]);
        //MOD = 998244353;

        pw[0] = 1;
        rep(i, 1, n*m) pw[i] = (pw[i - 1] << 1) % MOD;
        rep(i, 0, max(n, m)) c[i][0] = 1;
        rep(i, 1, max(n, m)) rep(j, 1, i)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;

        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        f[1][n - 1][m][1] = 1;
        int mx = max(n, m);
        rep(i, 1, n + m - 1) rep(j, 0, mx) rep(k, 0, mx) {
            rep(a, 1, mx - j) if (f[i][j][k][a]) {
                add(g[i], f[i][j][k][a] * pw[(j + a) * k] % MOD * a);
                i64 t = 1;
                rep(b, 1, k) {
                    t = t * (pw[a] - 1) % MOD;
                    add(f[i + 1][k - b][j][b],
                        c[k][b] * t % MOD * f[i][j][k][a]);
                }
            }
        }
        rep(j, 0, mx) rep(k, 0, mx) rep(a, 0, mx - j)
            add(g[n + m], f[n + m][j][k][a] * pw[(j + a) * k] % MOD * a);

        i64 num = 0, dem = pw[n * m] * m % MOD;
        rep(i, 1, min(n, m)) {
            add(num, g[2*i] * (2*i - 1));
            //fprintf(stderr, "%2d: %lld\n", 2*i - 1, g[2*i]);
        }

        //printf("%lld/%lld\n", num, dem);
        i64 ans = num * inv(dem) % MOD;
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
