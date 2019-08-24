/**
 * 利用容斥的思想来做到很优的复杂度的例子
 * 首先任意连边的方案可以暴力枚举求出来
 * 对于一个点集S，令f[S]为在S上的答案
 * g[S]表示任意连边的方案，g[S]可以O(n^2)求出
 * 对于f[S]，使用容斥的方法。即使用g[S]减去不合法的
 * 考虑不合法的方案，其中至少有一个连通块（大小可以为1）
 * 那么基本的想法就是枚举这个连通块，那么剩下的部分就是由g计算
 * 但是这样有个问题，如果一张图有c个连通块，那么它就会被计算c次
 * 因此只考虑与某个点u相连的联通块，这样这就不会算重了
 * 关于枚举子集：对于每个集合枚举自己的子集的复杂度是3^n的
 * 因为复杂度为：
 * \sum_{k = 0}^n {n \choose k} 2^k
 * 利用二项式定理可以得到上式等于(1 + 2)^n，即3^n
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 16
#define MOD 1000000007

typedef long long i64;

static int n;
static i64 G[NMAX + 10][NMAX + 10];
static i64 f[1 << NMAX];
static i64 g[1 << NMAX];

void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lld", &G[i][j]);
        }
    }
}

int main() {
    initialize();

    for (int s = 1; s < (1 << n); s++) {
        g[s] = 1;
        for (int u = 0; u < n; u++) {
            if (!((s >> u) & 1))
                continue;

            for (int v = u + 1; v < n; v++) {
                if ((s >> v) & 1)
                    g[s] = g[s] * (G[u][v] + 1) % MOD;
            }
        }

        f[s] = g[s];
        int q = 0;
        for (int u = 0; u < n; u++) {
            if ((s >> u) & 1) {
                q = s ^ (1 << u);
                break;
            }
        }

        for (int p = q; p; p = (p - 1) & q) {
            f[s] = (f[s] - g[p] * f[s ^ p] % MOD) % MOD;
        }
    }

    i64 answer = f[(1 << n) - 1];
    if (answer < 0)
        answer += MOD;
    printf("%lld\n", answer);

    return 0;
}
