#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define MOD 998244353
#define NMAX 5000

static i64 fac[NMAX + 10], fi[NMAX + 10], pw[NMAX + 10];

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

inline i64 c(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * fi[m] % MOD * fi[n - m] % MOD;
}

inline i64 f(int n, int K, int p) {
    if (n == 0) return 1;
    i64 ret = 0;
    for (int k = 0; k <= p; k++)
        ret = (ret + c(p, k) * pw[k] % MOD * c(n + K - 2 * p - 1, n - k)) % MOD;
    return ret;
}

int main() {
    pw[0] = fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        pw[i] = (pw[i - 1] << 1) % MOD;
    }
    fi[NMAX] = inv(fac[NMAX]);
    for (int i = NMAX - 1; i >= 0; i--) fi[i] = fi[i + 1] * (i + 1) % MOD;

    int n, K;
    scanf("%d%d", &K, &n);
    for (int t = 2; t <= 2 * K; t++)
        printf("%lld\n", t & 1 ? f(n, K, t / 2 - max(0, t - K - 1)) :
                         (f(n, K - 1, t / 2 - 1 - max(0, t - K - 1)) +
                         f(n - 1, K - 1, t / 2 - 1 - max(0, t - K - 1))) % MOD);

    return 0;
}
