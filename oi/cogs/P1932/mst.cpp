/**
 * 子集容斥DP
 * 还是考虑如何贡献答案的。
 * 对于一张图，如果< x的边不连通，但是<= x连通那么说明最大边为x
 * 因此我们考虑枚举前j条边答案，如果前j条边**恰好**连通，那么
 * 答案的贡献就是最大边，也就是j / (m + 1)
 * 考虑计算方案，设f[S][j]是点集S上选取j条边**不连通**的方案数
 * g[S][j]是连通的方案数，那么这两个函数之间可以互相DP
 * 也是钦定一个点，枚举一个连通块，然后转移
 * 注意到f[S][j] + g[S][j] = c[e[S]][j]，这样只用计算f就可以算出g
 * 最后计算答案时注意：不能用j * g[S][j]来贡献答案
 * 因为贡献答案的不一定是一棵树，这样就会出现不正确的贡献
 * 所以用f[S][j]直接贡献，原因是小于某一权重的方案会多次贡献
 * 但是每次只会贡献1，而到了x时就停止贡献了
 * 因此是对的。
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10
#define MMAX (NMAX * (NMAX - 1) / 2)
#define SMAX (1 << NMAX)

typedef long long i64;

static int n, m;
static int E[MMAX + 10];
static int e[SMAX + 10];
static i64 c[MMAX + 10][MMAX + 10];
static i64 f[SMAX + 10][MMAX + 10];
static i64 g[SMAX + 10][MMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        E[i] |= 1 << (u - 1);
        E[i] |= 1 << (v - 1);
    }

    c[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }

    for (int s = 0; s <= (1 << n); s++) {
        for (int i = 1; i <= m; i++) {
            if ((s & E[i]) == E[i])
                e[s]++;
        }
    }
}

int main() {
    // freopen("zjoi15_mst.in", "r", stdin);
    // freopen("zjoi15_mst.out", "w", stdout);
    initialize();

    for (int s = 1; s <= (1 << n); s++) {
        int u;
        for (u = 0; !((s >> u) & 1); u++);

        for (int j = 0; j <= m; j++) {
            int q = (s ^ (1 << u));
            for (int a = q; a; a = (a - 1) & q) {
                int b = s ^ a;
                for (int k = 0; k <= j; k++) {
                    f[s][j] += g[b][k] * c[e[a]][j - k];
                }
            }

            g[s][j] = c[e[s]][j] - f[s][j];
        }
    }

    int all = (1 << n) - 1;
    double answer = 0.0;
    for (int j = 0; j <= m; j++) {
        answer += f[all][j] / (double) c[m][j];
    }
    answer /= m + 1;
    printf("%lf\n", answer);

    return 0;
}
