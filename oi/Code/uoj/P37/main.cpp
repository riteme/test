#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 15
#define SMAX (1 << NMAX)
#define MOD 1000000007
#define has(s, i) ((s >> i) & 1)

typedef long long i64;

static int n, m;
static int in[NMAX + 10], out[NMAX + 10];
static int cnt[SMAX + 10], edge[SMAX + 10], h[SMAX + 10], w[SMAX + 10];
static i64 tpow[NMAX * NMAX + 10];
static i64 f[SMAX + 10], g[SMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        in[v] |= 1 << u;
        out[u] |= 1 << v;
    }

    tpow[0] = 1;
    for (int i = 1; i <= n * n; i++) {
        tpow[i] = tpow[i - 1] * 2 % MOD;
    }

    cnt[0] = 0;
    for (int s = 1; s < (1 << n); s++) {
        cnt[s] = cnt[s >> 1] + (s & 1);

        for (int i = 0; i < n; i++) {
            if (!has(s, i))
                continue;

            edge[s] += cnt[out[i] & s];
        }
    }

    h[1] = 0;
    for (int s = 2; s < (1 << n); s++) {
        h[s] = h[s >> 1] + 1;
    }
}

#define has(s, i) ((s >> i) & 1)

int main() {
    initialize();

    f[0] = 1;
    g[0] = -1;
    for (int s = 1; s < (1 << n); s++) {
        int p = h[s];
        f[s] = tpow[edge[s]];

        for (int a = (s - 1) & s; a; a = (a - 1) & s) {
            if (!has(a, p))
                continue;

            g[s] = (g[s] - f[a] * g[s ^ a]) % MOD;
        }

        w[s] = 0;
        for (int a = s; a; a = (a - 1) & s) {
            if (a != s) {
                int p = h[s ^ a];
                w[a] = w[a | (1 << p)] - cnt[out[p] & (s ^ a)]
                                       + cnt[in[p] & a];
            }

            f[s] = (f[s] - g[a] * tpow[w[a] + edge[s ^ a]]) % MOD;
        }

        g[s] = (g[s] + f[s]) % MOD;
    }

    i64 ans = f[(1 << n) - 1];
    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);

    return 0;
}
