#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 998244353

typedef long long i64;

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

static i64 fac[NMAX + 10], fi[NMAX + 10];

inline i64 C(int n, int m) {
    if (n < m || m < 0) return 0;
    return fac[n] * fi[m] % MOD * fi[n - m] % MOD;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) fac[i] = fac[i - 1] * i % MOD;
    fi[NMAX] = inv(fac[NMAX]);
    for (int i = NMAX - 1; i >= 0; i--) fi[i] = fi[i + 1] * (i + 1) % MOD;
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M;
        scanf("%d%d", &N, &M);
        i64 ans = 0;
        for (int k = 1; k * M <= N; k++) for (int n = 0; n + k * M <= N; n++)
            ans = (ans + C(n + 2 * k - 1, n) - C(n + k - 1, n - k)) % MOD;
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
