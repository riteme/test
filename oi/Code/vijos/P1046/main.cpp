

/**
 * 观光旅游
 * tags: Floyd 最小环
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 10000
#define INFTY 2000000000
#define NO_ANSWER "No solution."

#define FMT "%lld"
typedef long long ntype;

static ntype n;
static ntype m;
static ntype G[NMAX + 10][NMAX + 10];
static ntype dist[NMAX + 10][NMAX + 10];
static ntype answer;

void initialize() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = G[i][j] = INFTY;
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        dist[i][i] = G[i][i] = 0;
    }  // for

    answer = INFTY;

    for (int i = 0; i < m; i++) {
        ntype u, v, w;
        scanf(FMT FMT FMT, &u, &v, &w);

        dist[u][v] = G[u][v] = w;
        dist[v][u] = G[v][u] = w;
    }  // for
}

void floyd() {
    // 一个环可以表示为u -> ... -> v -> k -> u，其中u, v, k是固定的
    // 基于此我们枚举u, v, k即可
    // 同时要使环的权值尽可能小，即使u到v的距离最短，这个最短值使用Floyd计算
    // 由于环上的点不能重复，故u, v, k在枚举时不能重复
    // 因此我们令k为其中编号最大的，u其次，v最小，从而避免重复

    for (int k = 1; k <= n; k++) {
        // 注意此处要先计算最小环，再计算Floyd。
        // 因为Floyd会更新dist[i][j]，可能更新为dist[i][k] + dist[k][j]
        // 而计算最小环要获得G[i][k] + G[k][j]的值
        // 如果i, k, j直接相连，将导致找出的环是i, k, j循环走
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                answer = min(answer, dist[i][j] + G[i][k] + G[k][j]);
            }  // for j
        }      // for i

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }  // for j
        }      // for i
    }          // for k
}

int main() {
    while (scanf(FMT FMT, &n, &m) != EOF) {
        initialize();

        floyd();

        if (answer >= INFTY) {
            printf(NO_ANSWER "\n");
        } else {
            printf(FMT "\n", answer);
        }
    }  // while

    return 0;
}  // function main
