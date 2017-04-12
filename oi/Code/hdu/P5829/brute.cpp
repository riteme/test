#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 998244353

typedef long long i64;

static int t, n;
static i64 fac[NMAX + 10];
static i64 inv[NMAX + 10];
static i64 tpow[NMAX + 10];
static i64 seq[NMAX + 10];
static i64 f[NMAX + 10];

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

void preprocess() {
    tpow[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        tpow[i] = (tpow[i - 1] << 1) % MOD;
    }

    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    
    inv[NMAX] = quick_pow(fac[NMAX], MOD - 2);
    for (int i = NMAX - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

inline i64 c(int n, int m) {
    if (n < m)
        return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

bool cmp(const i64 &a, const i64 &b) {
    return seq[a] > seq[b];
}

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
    }

    sort(seq + 1, seq + n + 1, cmp);
}

int main() {
    preprocess();
    scanf("%d", &t);

    while (t--) {
        initialize();

        f[n] = 0;
        for (int i = 1; i <= n; i++) {
            f[n] += seq[i];
            f[n] %= MOD;
        }
        f[n] = f[n] * tpow[n - 1] % MOD;

        for (int k = n - 1; k >= 1; k--) {
            f[k] = f[k + 1];
            for (int j = k + 1; j <= n; j++) {
                f[k] -= seq[j] * c(j - 1, k) % MOD * tpow[n - j] % MOD;
                f[k] %= MOD;
            }

            if (f[k] < 0)
                f[k] += MOD;
        }

        for (int i = 1; i <= n; i++) {
            printf("%lld ", f[i]);
        }
        printf("\n");
    }

    return 0;
}
