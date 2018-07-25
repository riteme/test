#define USE_FILE_IO

#include <cstdio>

typedef long long i64;

#define MOD 998244353

inline i64 qpow(i64 a, i64 b) {
    i64 r = 1;
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

int main() {
#ifdef USE_FILE_IO
    freopen("problem.in", "r", stdin);
    freopen("problem.out", "w", stdout);
#endif

    i64 n, s, d;
    scanf("%lld%lld%lld", &n, &s, &d);

    i64 p = qpow(2, n - 1);
    n %= MOD;
    s %= MOD;
    d %= MOD;
    printf("%lld\n", (2 * s + n * d % MOD) * p % MOD);

    return 0;
}
