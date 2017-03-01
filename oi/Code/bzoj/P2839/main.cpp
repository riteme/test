#include <cstdio>

#define NMAX 1000000
#define MOD 1000000007

typedef long long i64;

static i64 f[NMAX + 10];
static i64 fac[NMAX + 10];
static i64 inv[NMAX + 10];

inline i64 quick_pow(i64 a, i64 b) {
    i64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

inline i64 c(i64 n, i64 m) {
    return fac[n] * (inv[m] * inv[n - m] % MOD) % MOD;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    f[n] = 1;
    for (int i = n - 1; i >= k; i--) {
        i64 last = f[i + 1] + 1;
        f[i] = (last * last - 1) % MOD;
    }

    fac[0] = 1;
    for (i64 i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv[0] = 1;
    inv[n] = quick_pow(fac[n], MOD - 2);
    for (i64 i = n - 1; i >= 1; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }

    i64 answer = 0;
    for (int i = k; i <= n; i++) {
        i64 s = c(n, i) * c(i, k) % MOD;
        answer += (((i - k) & 1) ? -1 : 1) * f[i] * s % MOD;
        answer %= MOD;
    }

    if (answer < 0)
        answer += MOD;

    printf("%lld\n", answer);

    return 0;
}
