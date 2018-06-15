#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MOD 998244353
#define NMAX 1000
#define KMAX 1000

typedef long long i64;

inline i64 inv(i64 x) {
    return x == 1 ? 1 : -(MOD / x) * inv(MOD % x) % MOD;
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
    else if (a < -MOD)
        a += MOD;
}

static int n;
static i64 p, pp[NMAX + 10], ipp[NMAX + 10];
static i64 f[KMAX + 10][NMAX + 10];

i64 dp(int K) {
    memset(f, 0, sizeof(f));
    f[K + 1][0] = 1;
    for (int k = K; k >= 0; k--) {
        f[k][0] = 1;
        for (int w = 1; w <= (k ? K / k : n); w++) {
            if (w <= K / (k + 1))
                add(f[k][w], f[k + 1][w] * pp[w] % MOD);
            for (int l = 0; l <= min(w, K / (k + 1)); l++)
                add(f[k][w],
                    f[k + 1][l] * f[k][w - l - 1] % MOD *
                    (1 - p) % MOD *
                    pp[l] % MOD
                );
        }
    }

    return f[0][n];
}

static int K;

void initialize() {
    i64 x, y;
    scanf("%d%d%lld%lld", &n, &K, &x, &y);
    p = x * inv(y) % MOD;

    pp[0] = ipp[0] = 1;
    for (int i = 1; i <= n; i++) {
        pp[i] = pp[i - 1] * p % MOD;
        ipp[i] = ipp[i - 1] * (1 - p) % MOD;
    }
}

int main() {
    initialize();

    i64 ans = ((dp(K) - dp(K - 1)) % MOD + MOD) % MOD;
    printf("%lld\n", ans);

    return 0;
}

