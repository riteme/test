/**
 * 考虑扫描线，设f[i][j][k]表示当前扫描线在i，扫描线以左有j个跳蚤
 * 穿过扫描线的有k个跳蚤，
 * 考虑枚举到下一个扫描线
 * 我们首先要确定有多少个跳蚤在i处结束，有多少个跳蚤在i + 1处开始
 * 分别枚举a, b表示上面两个东西，注意要满足k <= T的限制
 * 选出a和b的方案数可以用组合数算出
 * 直接DP是40^5的
 * 40^4的DP？
 */

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define MOD 1011110011

typedef long long i64;

static int n, K, T;
static i64 C[100][100];
static i64 f[100][100][100];

void initialize() {
    scanf("%d%d%d", &n, &K, &T);

    C[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        C[i][0] = C[i][i] = 1;
        
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int main() {
    initialize();

    f[0][0][0] = 1;
    for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= K; j++) {
    for (int k = 0; k <= T; k++) {
        if (j + k > K || k > T)
            continue;

        int r = K - j - k;
        for (int a = 0; a <= k; a++) {
        for (int b = 0; b <= min(r, T - k + a); b++) {
            add(f[i + 1][j + a][k - a + b], f[i][j][k] * C[k][a] % MOD * C[r][b]);
        }}
    }}}

    printf("%lld\n", f[n + 1][K][0]);

    return 0;
}
