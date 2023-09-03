#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;
constexpr i64 MOD = 998244353;

i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    for ( ; k; k >>= 1) {
        if (k & 1)
            r = r * a % MOD;
        a = a * a % MOD;
    }
    return r;
}

i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

i64 fac[NMAX + 10];
i64 fi[NMAX + 10];

i64 C(int n, int k) {
    if (n < k)
        return 0;
    return fac[n] * fi[k] % MOD * fi[n - k] % MOD;
}

void solve() {
    int n, m, K;
    scanf("%d%d%d", &n, &m, &K);

    i64 ans = 0;
    for (int a = 0; a <= K; a++) {
        ans = (ans + (K - a) * C(n - a - 1, K - a)) % MOD;
    }
    ans = (n + ans * inv(C(n, K)) % MOD * m) % MOD;
    printf("%lld\n", ans);
}

int main() {
    fac[0] = 1;
    for (i64 i = 1; i <= NMAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    fi[NMAX] = inv(fac[NMAX]);
    for (i64 i = NMAX - 1; i >= 0; i--) {
        fi[i] = fi[i + 1] * (i + 1) % MOD;
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
