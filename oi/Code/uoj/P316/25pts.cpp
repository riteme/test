#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define MOD 998244353
#define NMAX 10
#define KMAX 1000
#define SMAX (1 << (NMAX))

inline i64 inv(i64 x) {
    return x == 1 ? 1 : -(MOD / x) * inv(MOD % x) % MOD;
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
    else if (a < -MOD)
        a += MOD;
}

static int n, all, cnt[SMAX + 10];
static i64 p, pp[NMAX + 10], ipp[NMAX + 10];
static bool ok[KMAX + 10][SMAX + 10];
static i64 f[KMAX + 10][SMAX + 10];

inline bool test(int s, int w) {
    for (int c = 0; s; s >>= 1) {
        if (s & 1)
            c++;
        else
            c = 0;
        if (c > w)
            return false;
    }

    return true;
}

i64 dp(int K) {
    memset(ok, 0, sizeof(ok));
    memset(f, 0, sizeof(f));

    ok[0][all] = ok[K + 1][0] = true;
    for (int i = 1; i <= K; i++) {
        int w = K / i;
        for (int s = 0; s <= all; s++) {
            ok[i][s] = test(s, w);
        }
    }

    f[0][all] = 1;
    for (int i = 0; i <= K; i++) {
        for (int s = 1; s <= all; s++) {
            if (!ok[i][s])
                continue;

            if (ok[i + 1][s])
                add(f[i + 1][s], f[i][s] * pp[cnt[s]] % MOD);

            for (int m = s; m; m = (m - 1) & s) {
                int t = s ^ m;
                if (!ok[i + 1][t])
                    continue;

                add(f[i + 1][t], f[i][s] * pp[cnt[t]] % MOD * ipp[cnt[m]] % MOD);
            }
        }
    }

    i64 ret = 0;
    for (int i = 1; i <= K + 1; i++) {
        add(ret, f[i][0]);
    }

    return ret;
}

int main() {
    int K;
    i64 _x, _y;
    scanf("%d%d%lld%lld", &n, &K, &_x, &_y);
    p = _x * inv(_y) % MOD;

    all = (1 << n) - 1;
    for (int s = 1; s <= all; s++) {
        cnt[s] = cnt[s >> 1] + (s & 1);
    }

    pp[0] = ipp[0] = 1;
    for (int i = 1; i <= n; i++) {
        pp[i] = pp[i - 1] * p % MOD;
        ipp[i] = ipp[i - 1] * (1 - p) % MOD;
    }

    i64 ans = ((dp(K) - dp(K - 1)) % MOD + MOD) % MOD;
    printf("%lld\n", ans);

    return 0;
}
