#define USE_FILE_IO

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define MOD 998244353

static int n;
static int A[NMAX + 10], B[NMAX + 10];
static i64 fac[NMAX + 10];
static i64 inv[NMAX + 10];

inline i64 qpow(i64 a, i64 b) {
    i64 r = 1;
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", A + i, B + i);
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
#ifdef USE_FILE_IO
    freopen("gf.in", "r", stdin);
    freopen("gf.out", "w", stdout);
#endif
    initialize();

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            ans = fac[A[i] + A[j] + B[i] + B[j]] * inv[A[i] + A[j]] % MOD
                                                 * inv[B[i] + B[j]] % MOD;
            ans %= MOD;
        }
    }

    printf("%lld\n", ans);

    return 0;
}
