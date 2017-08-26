#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define CMAX 3001
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
static int X[NMAX + 10], Y[NMAX + 10];
static i64 fac[NMAX + 10], inv[NMAX + 10];
static unsigned int f[CMAX * 2 + 10][CMAX * 2 + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d%d", X + i, Y + i);
        f[CMAX - X[i]][CMAX - Y[i]]++;
    }

    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    inv[NMAX] = qpow(fac[NMAX], MOD - 2);
    for (int i = NMAX - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

int main() {
    initialize();

    for (int i = 1; i <= CMAX * 2; i++) {
        for (int j = 1; j <= CMAX * 2; j++) {
            f[i][j] = (f[i][j] + f[i - 1][j] + f[i][j - 1]) % MOD;
        }
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + f[X[i] + CMAX][Y[i] + CMAX]) % MOD;
    }

    for (int i = 0; i < n; i++) {
        ans -= fac[2 * (X[i] + Y[i])] * inv[2 * X[i]] % MOD
                                      * inv[2 * Y[i]] % MOD;
        ans %= MOD;
    }

    ans = ans * qpow(2, MOD - 2) % MOD;

    if (ans < 0)
        ans += MOD;

    printf("%lld\n", ans);

    return 0;
}
