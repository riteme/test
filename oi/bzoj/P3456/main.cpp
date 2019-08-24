/**
 * 用总方案数减去不合法方案数，递推式为：
 * f[k] = g[k] - \sum_{i = 0}^{k - 2} {k - 1 \choose i} f(i + 1) * g(k - i - 1)
 * 最后的卷积是这样的：
 * \sum_{j = 0}^{i - 2} A(j) B(i - j - 1)
 * A(k) = f(k + 1) / k!
 * B(k) = g(k + 1) / (k + 1)!
 * 这里需要平移一下才能满足i - 2的下标
 * 但是注意了，不能左移A来实现，因为这样少了东西
 * 可以通过右移B的下标来实现
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 262144
#define MOD 1004535809
#define G 3

typedef long long i64;

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

inline i64 inv(i64 a) {
    return quick_pow(a, MOD - 2);
}

inline int next_pow(int n) {
    int ret = 1;
    while (n > ret) {
        ret <<= 1;
    }

    return ret;
}

void ntt(i64 *X, int n, bool reversed) {
    static i64 tmp[NMAX + 10];
    memcpy(tmp, X, sizeof(i64) * n);
    int rev = 0;
    for (int i = 0; i < n; i++) {
        X[i] = tmp[rev];

        int k = n >> 1;
        while (rev & k) {
            rev ^= k;
            k >>= 1;
        }
        
        rev |= k;
    }

    for (int s = 2; s <= n; s <<= 1) {
        int len = s >> 1;
        i64 wn = reversed ? quick_pow(G, MOD - 1 - (MOD - 1) / s) :
                            quick_pow(G, (MOD - 1) / s);

        for (int i = 0; i < n; i += s) {
            i64 w = 1;
            for (int j = i; j < i + len; j++) {
                i64 tmp = X[j];
                X[j] = (tmp + w * X[j + len] % MOD) % MOD;
                X[j + len] = (tmp - w * X[j + len] % MOD) % MOD;
                w = w * wn % MOD;
            }
        }
    }

    if (reversed) {
        i64 div = inv(n);
        for (int i = 0; i < n; i++) {
            X[i] = X[i] * div % MOD;
        }
    }
}

static int n;
static i64 fac[NMAX + 10];
static i64 f[NMAX + 10], g[NMAX + 10];
static i64 A[NMAX + 10], B[NMAX + 10];

void solve(int l, int r) {
    if (l == r) {
        f[l] = (g[l] - fac[l - 1] * f[l] % MOD) % MOD;
        return;
    }

    int mid = (l + r) / 2;
    solve(l, mid);

    int m = next_pow((r - l + 1) * 2);
    memset(A, 0, sizeof(i64) * m);
    memset(B, 0, sizeof(i64) * m);
    for (int i = l; i <= mid; i++) {
        A[i - l] = f[i] * inv(fac[i - 1]) % MOD;
    }

    for (int i = 0; i <= r - l + 1; i++) {
        B[i] = g[i + 1] * inv(fac[i + 1]) % MOD;
    }

    ntt(A, m, false);
    ntt(B, m, false);

    for (int i = 0; i < m; i++) {
        A[i] = A[i] * B[i] % MOD;
    }

    ntt(A, m, true);

    for (int i = mid + 1; i <= r; i++) {
        f[i] = (f[i] + A[i - l - 1]) % MOD;
    }

    solve(mid + 1, r);
}

int main() {
#ifdef USE_FILE_IO
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
#endif
    scanf("%d", &n);

    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    i64 tpow = 1;
    g[0] = 1;
    for (int i = 1; i <= n; i++) {
        g[i] = g[i - 1] * tpow % MOD;
        tpow = tpow * 2 % MOD;
    }

    solve(1, next_pow(n));
    printf("%lld\n", (f[n] + MOD) % MOD);

    return 0;
}
