/**
 * 关键的一点：
 * 至少一个点在边界上的方案数等于(n + 1) x (m + 1)随意放的方案数
 * 减去(n - 1) x (m - 1)随意放的方案数
 * 这样可以简化问题
 * 考虑水平和竖直的直线，可以直接组合数计算
 * 每一条正数斜率都会和一条负数斜率对应
 * 剩下的就是枚举两个端点，注意到方案数只与坐标差相关、
 * 所以只用枚举坐标差。
 * 线段上整点数量跟gcd相关，最后的和式就是一个带gcd的二阶级数
 * 运用莫比乌斯函数相关套路即可解决
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000001
#define MOD 1000000007

typedef long long i64;

static i64 mu[NMAX + 10];
static i64 fac[NMAX + 10];
static i64 inv[NMAX + 10];
static i64 S[NMAX + 10];

inline i64 quick_pow(i64 a, i64 b) {
    i64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a  % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

inline i64 c(i64 n, i64 m) {
    assert(0 <= n);
    if (n < m)
        return 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

void initialize() {
    mu[1] = -1;
    for (int i = 1; i <= NMAX; i++) {
        mu[i] *= -1;
        for (int j = i + i; j <= NMAX; j += i) {
            mu[j] += mu[i];
        }
    }

    fac[0] = 1;
    for (i64 i = 1; i <= NMAX; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }

    inv[NMAX] = quick_pow(fac[NMAX], MOD - 2);
    for (i64 i = NMAX - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }

    for (i64 i = 1; i <= NMAX; i++) {
        S[i] = (S[i - 1] + i) % MOD;
    }
}

static i64 f[NMAX + 10];

i64 solve(i64 n, i64 m, i64 k) {
    memset(f, 0, sizeof(f));

    i64 bound = max(n, m) - 1;
    for (i64 s = 1; s <= bound; s++) {
        for (i64 d = 1; d * s <= bound; d++) {
            f[d * s] += c(s - 1, k - 2) * mu[d];
            f[d * s] %= MOD;
        }
    }

    i64 ret = 0;
    for (i64 T = 1; T <= bound; T++) {
        i64 a = (n - 1) / T;
        i64 b = (m - 1) / T;
        i64 coeff = (
              n * m % MOD * a % MOD * b % MOD
            - T * m % MOD * b % MOD * S[a] % MOD
            - T * n % MOD * a % MOD * S[b] % MOD
            + T * T % MOD * S[a] % MOD * S[b] % MOD
        ) % MOD;
        ret += coeff * f[T];
        ret %= MOD;
    }

    return (
        ret * 2 % MOD +
        c(n, k) * m % MOD +
        c(m, k) * n % MOD
    ) % MOD;
}

int main() {
    initialize();

    i64 n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    printf(
        "%lld\n",
        (solve(n + 1, m + 1, k) - solve(n - 1, m - 1, k) + MOD) % MOD
    );

    return 0;
}

