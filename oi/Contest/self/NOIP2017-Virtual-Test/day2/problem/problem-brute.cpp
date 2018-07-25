#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10000000
#define MOD 998244353

typedef long long i64;

inline i64 qpow(i64 a, i64 b) {
    i64 r = 1;
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

static int n;
static i64 s, d;
static i64 fac[NMAX + 10];
static i64 inv[NMAX + 10];

inline i64 c(int n, int k) {
    return fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}

int main() {
    scanf("%d%lld%lld", &n, &s, &d);
    s %= MOD;
    d %= MOD;

    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    inv[n] = qpow(fac[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }

    i64 seq = s, ans = 0;
    for (int k = 0; k <= n; k++) {
        ans = (ans + seq * c(n, k)) % MOD;
        seq = (seq + d) % MOD;
    }

    printf("%lld\n", ans);

    return 0;
}
