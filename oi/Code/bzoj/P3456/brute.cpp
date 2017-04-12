#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 130000
#define MOD 1004535809

typedef long long i64;

i64 quick_pow(i64 a, i64 b) {
    i64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

static int n;
static i64 fact[NMAX + 10];
static i64 inv[NMAX + 10];
static i64 tpow[NMAX + 10];
static i64 f[NMAX + 10];
static i64 g[NMAX + 10];

inline i64 c(int n, int m) {
    return fact[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
#ifdef USE_FILE_IO
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
#endif
    scanf("%d", &n);

    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv[n] = quick_pow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }

    tpow[0] = 1;
    for (int i = 1; i <= n; i++) {
        tpow[i] = tpow[i - 1] * 2 % MOD;
    }

    g[0] = 1;
    for (int i = 1; i <= n; i++) {
        g[i] = g[i - 1] * tpow[i - 1] % MOD;
    }

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = g[i];

        for (int j = 0; j < i - 1; j++) {
            f[i] -= c(i - 1, j) * f[j + 1] % MOD *
                    g[i - j - 1] % MOD;
            f[i] %= MOD;
        }
    }

    printf("%lld\n", (f[n] + MOD) % MOD);

    return 0;
}
