/**
 * 由于k是质数，所以利用Lucas定理，这个题就变为了一道数位DP
 * 需要统计C(i, j)为0的个数，可以变为某一位为0的个数
 * 但是这样计算需要设立至少3个状态，
 * 因为要满足i <= n, j <= m和i >= j，由于允许i < j此时出现组合数为0的情况
 * 所以i >= j的状态不得不记，转移起来不方便
 * 考虑容斥，用总方案减去不合法的方案数
 * 不合法的方案数就是没有一位是0的方案数
 * 相当于每一位都要i >= j。这样就可以少记一维状态啦~~~
 * 注意一些细节，就是要记得清空数组，否则会卡成暴力分......
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define PMAX 100
#define MOD 1000000007
#define INV2 500000004

typedef long long i64;

static int T, p;
static int len;
static int dn[PMAX + 10];
static int dm[PMAX + 10];
static i64 f[PMAX + 10][2][2]; 

inline i64 S(i64 n, i64 m) {
    i64 minv = min(n, m);
    return minv * (minv + 1) / 2 + max(0LL, n - m) * m;
}

int main() {
    scanf("%d%d", &T, &p);

    while (T--) {
        i64 n, m;
        scanf("%lld%lld", &n, &m);

        if (m > n)
            m = n;

        i64 minv = m % MOD;
        i64 answer = ((minv + 1) * (minv + 2) % MOD * INV2 % MOD +
                      (n - m) % MOD * ((m + 1) % MOD) % MOD) % MOD;

        memset(dn, 0, sizeof(dn));
        memset(dm, 0, sizeof(dm));
        int pos = 0;
        while (n) {
            dn[++pos] = n % p;
            n /= p;
        }
        len = pos;
        pos = 0;
        while (m) {
            dm[++pos] = m % p;
            m /= p;
        }

        f[0][0][0] = f[0][1][0] = f[0][0][1] = f[0][1][1] = 1;
        for (int i = 1; i <= len; i++) {
            f[i][0][0] = (
                p * (p + 1) / 2 * f[i - 1][0][0]
            ) % MOD;
            f[i][0][1] = (
                S(p, dm[i]) * f[i - 1][0][0] % MOD +
                (p - dm[i]) * f[i - 1][0][1] % MOD
            ) % MOD;
            f[i][1][0] = (
                S(dn[i], p) * f[i - 1][0][0] % MOD +
                (dn[i] + 1) * f[i - 1][1][0] % MOD
            ) % MOD;
            f[i][1][1] = (
                S(dn[i], dm[i]) * f[i - 1][0][0] % MOD +
                max(0, dn[i] - dm[i]) * f[i - 1][0][1] % MOD +
                min(dn[i] + 1, dm[i]) * f[i - 1][1][0] % MOD +
                (dn[i] >= dm[i] ? f[i - 1][1][1] : 0)
            ) % MOD;
        }

        printf("%lld\n", (answer - f[len][1][1] + MOD) % MOD);
    }

    return 0;
}
