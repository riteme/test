/**
 * 基本思路：
 *
 * 先考虑没有前置0的限制，那么将会是一个三维DP：
 * f[d][n][k]
 * 考虑的是将出现次数为k的数字都挖掉
 *
 * 然后考虑f[10][n][k]与最终答案的关系，通过一个巧妙的映射来证明
 * answer = 9 * f[10][n][k] / 10
 *
 * 具体看solution.pdf
 */

#pragma GCC optimize(3)

#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define KEMAX 10000
#define DMAX 10
#define MOD 1000000007
#define INV10 700000005

typedef long long int64;

static int64 C[NMAX + 10][NMAX + 10];
static int64 fac[KEMAX + 10][DMAX + 1];
static int64 facinv[KEMAX + 10][DMAX + 1];
static int64 f[DMAX + 1][NMAX + 10][NMAX + 10];

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

inline int64 inv(int64 x) {
    return quick_pow(x, MOD - 2);
}

static void initialize_combine() {
    for (int i = 0; i <= NMAX; i++)
        C[i][0] = C[i][i] = 1;
        
    for (int i = 1; i <= NMAX; i++)
        for (int j = 1; j < i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
}

inline int64 c(int n, int m) {
    if (m > n)
        return 0;
    return C[n][m];
}

static void initialize_factorial() {
    for (int i = 0; i <= DMAX; i++)
        fac[0][i] = facinv[0][i] = 1;

    for (int i = 1; i <= KEMAX; i++) {
        fac[i][0] = facinv[i][0] = 1;
        fac[i][1] = fac[i - 1][1] * i % MOD;

        for (int j = 1; j <= DMAX; j++) {
            facinv[i][j] = inv(fac[i][j]);

            if (j < DMAX)
                fac[i][j + 1] = fac[i][j] * fac[i][1] % MOD;
        }
    }
}

static void initialize_dp() {
    for (int d = 1; d <= DMAX; d++)
        for (int n = 1; n <= NMAX; n++)
            for (int k = 1; k <= NMAX; k++)
                f[d][n][k] = -1;
}

static int64 dp(int d, int n, int k) {
    if (n <= 0)
        return 1;
    if (d == 0 || k == 0)
        return 0;
    if (f[d][n][k] >= 0)
        return f[d][n][k];

    int64 &answer = f[d][n][k];
    answer = 0;

    for (int e = 0; e <= d; e++) {
        answer += ((c(d, e) * c(n, k * e) % MOD) * 
                   (fac[k * e][1] * facinv[k][e] % MOD) % MOD) *
                  dp(d - e, n - k * e, k - 1) % MOD;
        answer %= MOD;
    }

    return answer;
}

int main() {
    initialize_combine();
    initialize_factorial();
    initialize_dp();

    int t;
    scanf("%d", &t);

    while (t--) {
        int n, k;
        scanf("%d%d", &n, &k);

        if (k > n)
            printf("%lld\n", 9 * quick_pow(10, n -  1) % MOD);
        else
            printf("%lld\n", (dp(10, n, k) * 9 % MOD) * INV10 % MOD);
    }

    return 0;
}
