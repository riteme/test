#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MOD 1000000007

typedef long long i64;

inline i64 qpow(i64 a, int b) {
    i64 r = 1;
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

static int n, m;
static i64 fac[NMAX + 10], inv[NMAX + 10];

inline i64 c(int n, int m) {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
    scanf("%d%d", &n, &m);

    if (n < m) {
        puts("0");
        return 0;
    }

    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    inv[n] = qpow(fac[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }

    i64 ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = (ans + (i & 1 ? -1 : 1) *
               c(m, i) * qpow(m - i, n)) % MOD;
    }

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);

    return 0;
}
