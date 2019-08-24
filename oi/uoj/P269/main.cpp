/**
 * 在标算的推导基础上，我们最后只用求得差分表第一斜列
 * 根据第一斜列b_0, b_1, ..., b_m可以计算整个多项式：
 * f(n) = \sum_{k = 0}^m b_k \binom{n}{k}
 * f(0)...f(m)已经全部知道，直接使用二项式反演：
 * b_n = \sum_{k = 0}^m (-1)^{m - k} \binom{n}{k} f(k)
 * 拆开组合数后直接FFT即可
 */

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 65536
#define MOD 998244353
#define G 3

typedef long long i64;

inline i64 qpow(i64 a, int b) {
    i64 r = 1;
    
    for (; b; b >>= 1, a = a * a % MOD) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

inline int nxtp(int n) {
    int r = 1;
    while (r < n) {
        r <<= 1;
    }

    return r;
}

void dft(i64 X[], int n, bool inverse) {
    static i64 tmp[NMAX + 10];
    int rev = 0;
    for (int i = 0; i < n; i++) {
        tmp[i] = X[rev];
        int k = n >> 1;
        while (rev & k) {
            rev ^= k;
            k >>= 1;
        }

        rev |= k;
    }
    memcpy(X, tmp, sizeof(i64) * n);

    for (int s = 2; s <= n; s <<= 1) {
        int l = s >> 1;
        i64 wn = qpow(G, inverse ? MOD - 1 - (MOD - 1) / s : (MOD - 1) / s);

        for (int i = 0; i < n; i += s) {
            i64 w = 1;
            for (int j = i; j < i + l; j++) {
                i64 t = X[j + l];
                X[j + l] = (X[j] - w * t) % MOD;
                X[j] = (X[j] + w * t) % MOD;
                w = w * wn % MOD;
            }
        }
    }

    if (inverse) {
        i64 d = qpow(n, MOD - 2);
        for (int i = 0; i < n; i++) {
            X[i] = X[i] * d % MOD;
        }
    }
}

static int n, m, x, size;
static i64 a[NMAX + 10], b[NMAX + 10];
static i64 fac[NMAX + 10], inv[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &x);

    fac[0] = 1;
    for (int i = 1; i <= m; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    inv[m] = qpow(fac[m], MOD - 2);
    for (int i = m - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
    
    for (int i = 0; i <= m; i++) {
        scanf("%lld", a + i);
        a[i] = a[i] * inv[i] % MOD;
        b[i] = i & 1 ? -inv[i] : inv[i];
    }

    size = nxtp((m + 1) * 2);
    dft(a, size, false);
    dft(b, size, false);

    for (int i = 0; i < size; i++) {
        a[i] = a[i] * b[i] % MOD;
    }

    dft(a, size, true);

    inv[1] = 1;
    for (int i = 2; i <= m + 1; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    i64 ans = 0;
    i64 kf = 1, nd = 1, xp = 1;
    for (int i = 0; i <= m; i++) {
        a[i] = a[i] * fac[i] % MOD;
        ans = (ans + a[i] * kf % MOD * nd % MOD * xp) % MOD;
        kf = kf * inv[i + 1] % MOD;
        nd = nd * (n - i) % MOD;
        xp = xp * x % MOD;
    }

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);

    return 0;
}
