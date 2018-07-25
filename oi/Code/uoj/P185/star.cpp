/**
 * 不会子集DP.....容斥还是挺容易懂的
 * 利用容斥可以放宽对于子树的要求。假设现在只允许在S中选择点来对应
 * 并且允许多个点选择一个点，只要保证最后出来的图是连通的
 * 这样的方案数可以使用一个树型DP来解决
 * 设f[i][j]表示i号点对应到S中j号点上的方案数
 * 转移的时候枚举每个儿子会对应什么点上面，这个点随意选取
 * 只要保证原图中有这个点到这个儿子的边即可
 * 这要每个子树，用每个儿子的方案数之和相乘，就是自己的答案
 * 最后进行容斥，全集为正贡献，之后按照S中点数的奇偶性设置系数
 */

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 32
#define SMAX (1 << 17)

typedef long long i64;

static int n, m;
static int G[NMAX];
static vector<int> T[NMAX];
static i64 f[NMAX][NMAX];
static int cnt[SMAX + 10];
static int tail;
static int seq[NMAX];

void dfs(int u, int f) {
    for (int v : T[u]) {
        if (v != f)
            dfs(v, u);
    }

    if (f >= 0)
        T[u].erase(find(T[u].begin(), T[u].end(), f));
    seq[tail++] = u;
}

void initialize() {
    scanf("%d%d", &n, &m);

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        u--, v--;
        G[u] |= 1 << v;
        G[v] |= 1 << u;
    }

    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        u--, v--;
        T[u].push_back(v);
        T[v].push_back(u);
    }

    dfs(0, -1);
    for (int i = 1; i < (1 << n); i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }
}

int main() {
    initialize();

    i64 answer = 0;
    for (int s = 1; s < (1 << n); s++) {
        for (int pos = 0; pos < n; pos++) {
            int u = seq[pos];

            for (int i = 0; i < n; i++) {
                if ((s >> i) & 1) {
                    i64 ans = 1;
                    for (int v : T[u]) {
                        i64 sum = 0;
                        for (int j = 0; j < n; j++) {
                            if ((G[i] & (1 << j)) && ((s >> j) & 1))
                                sum += f[v][j];
                        }

                        ans *= sum;
                    }

                    f[u][i] = ans;
                }
            }
        }

        i64 sum = 0;
        for (int i = 0; i < n; i++) {
            if ((s >> i) & 1)
                sum += f[0][i];
        }

        answer += ((cnt[s] & 1) == (n & 1) ? 1 : -1) * sum;
    }
    
    printf("%lld\n", answer);

    return 0;
}
