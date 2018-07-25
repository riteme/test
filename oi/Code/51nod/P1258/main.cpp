/**
 * 拉格朗日插值法
 * 注意取模！
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define KMAX (50000 + 10)
#define MOD 1000000007

typedef long long i64;

static int pcnt;
static int primes[KMAX + 10];
static int mindiv[KMAX + 10];
static bool marked[KMAX + 10];
static i64 fac[KMAX + 10];
static i64 inv[KMAX + 10];

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

void initialize() {
    for (int i = 2; i <= KMAX; i++) {
        if (!marked[i]) {
            primes[++pcnt] = i;
            mindiv[i] = i;
        }

        for (int j = 1; j <= pcnt && i * primes[j] <= KMAX; j++) {
            int p = primes[j];
            marked[i * p] = true;
            mindiv[i * p] = p;  // 求最小质因子这里曾经写错了，但是x^k是完全积性函数就没有出错......

            if (i % p == 0)
                break;
        }
    }

    fac[0] = 1;
    for (int i = 1; i <= KMAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    inv[KMAX] = quick_pow(fac[KMAX], MOD - 2);
    for (int i = KMAX - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

static i64 f[KMAX + 10];

void sample(int k) {
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= k + 1; i++) {
        if (!marked[i])
            f[i] = quick_pow(i, k);
        else
            f[i] = f[mindiv[i]] * f[i / mindiv[i]] % MOD;
    }

    for (int i = 1; i <= k + 1; i++) {
        f[i] = (f[i] + f[i - 1]) % MOD;
    }
}

static i64 pre[KMAX + 10];
static i64 suf[KMAX + 10];

i64 solve(i64 n, int k) {
    sample(k);

    n %= MOD;
    pre[0] = suf[k + 1] = 1;
    for (int i = 1; i <= k + 1; i++) {
        pre[i] = pre[i - 1] * (n - i + 1) % MOD;
    }
    for (int i = k; i >= 0; i--) {
        suf[i] = suf[i + 1] * (n - i - 1) % MOD;
    }

    i64 ret = 0;
    for (int i = 0; i <= k + 1; i++) {
        i64 coeff = pre[i] * suf[i] % MOD *
                    inv[i] % MOD * inv[k - i + 1] % MOD;
        ret += (((k - i) & 1) ? 1 : -1) *
               f[i] * coeff % MOD;
        ret %= MOD;
    }

    if (ret < 0)
        ret += MOD;

    return ret;
}

int main() {
    initialize();

    int t;
    scanf("%d", &t);
    while (t--) {
        i64 n;
        int k;
        scanf("%lld%d", &n, &k);
        printf("%lld\n", solve(n, k));
    }

    return 0;
}
