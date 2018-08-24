#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 400
#define MOD 998244353
#define BASE 1000000

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

inline i64 qpow(i64 x, i64 n) {
    i64 r = 1;
    for (; n; n >>= 1, x = x * x % MOD)
        if (n & 1) r = r * x % MOD;
    return r;
}

static int n;
static i64 P, fac[NMAX + 10], fi[NMAX + 10];
static i64 f[NMAX + 10][NMAX + 10];

int main() {
    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++)
        fac[i] = fac[i - 1] * i % MOD;
    fi[NMAX] = inv(fac[NMAX]);
    for (int i = NMAX - 1; i >= 0; i--)
        fi[i] = fi[i + 1] * (i + 1) % MOD;
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lld", &n, &P);
        P = P * inv(BASE) % MOD;
        memset(f, 0, sizeof(f));
        f[1][1] = 1;
        for (int i = 2; i <= n; i++) for (int j = 1; j <= i; j++) for (int k = 1; k <= i - j; k++) {
            
        }
    }

    return 0;
 }
