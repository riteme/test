#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 5000;
constexpr i64 MOD = 998244353;

int n, K;
i64 a[NMAX + 10];
i64 g[NMAX + 10];
i64 fac[NMAX + 10];
i64 fi[NMAX + 10];

i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    while (k) {
        if (k & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        k >>= 1;
    }
    return r;
}

i64 c(i64 n, i64 m) {
    if (n < m)
        return 0;
    return fac[n] * fi[m] % MOD * fi[n - m] % MOD;
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }
    sort(a + 1, a + n + 1);

    fac[0] = 1;
    for (i64 i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    fi[n] = qpow(fac[n], MOD - 2);
    for (i64 i = n - 1; i >= 0; i--) {
        fi[i] = fi[i + 1] * (i + 1) % MOD;
    }

    g[1] = 0;
    for (int i = 2; i <= n; i++) {
        g[i] = 0;
        for (int k = 1; k <= K; k++) {
            g[i] = (g[i] + c(n - k, i - 1)) % MOD;
        }
        g[i] = g[i] * fac[i] % MOD * fac[n - i] % MOD * (i - 1) % MOD;
    }

    i64 ans = 0;
    for (int i = 2; i <= n; i++) {
        ans = (ans + a[i] * (g[i] - g[i - 1])) % MOD;
    }

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);

    return 0;
}
