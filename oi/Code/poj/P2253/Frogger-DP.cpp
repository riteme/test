/**
 * Frogger
 * tags: 动态规划
 * time: O(n^3)
 */

#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

#define NMAX 200
#define INFTY 10000000.0
#define SCENARIO "Scenario #%d"
#define DISTANCE "Frog Distance = %.3lf"

struct Point {
    double x;
    double y;
};  // struct Point

typedef set<double>::iterator iterator_t;

static int n;
static Point stone[NMAX + 10];
static double G[NMAX + 10][NMAX + 10];

inline double length(int a, int b) {
    return sqrt((stone[a].x - stone[b].x) * (stone[a].x - stone[b].x) +
                (stone[a].y - stone[b].y) * (stone[a].y - stone[b].y));
}

void initialize() {
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &stone[i].x, &stone[i].y);
    }  // for

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            G[i][j] = G[j][i] = length(i, j);
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        G[i][i] = INFTY;
    }  // for
}

int main() {
    int id = 0;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) {
            break;
        }

        id++;
        initialize();

        /**
         * 动态规划：
         * 思想：
         *     这张图是一张完全图
         *     假设一条路径i -> ... -> k -> ... -> j，设这条路径上的最长边为G(i,
         * j)
         *     则G(i, j)肯定为路径i -> ... -> k的最长边和路径k -> ... ->
         * j的最长边的最大值
         *     故：
         *     G(i, j) = max{G(i, k), G(k, j)}
         *
         *     得到的状态转移方程：
         *     G(i, j) = min{G(i, j), max{G(i, k), G(k, j)}}
         *     使用Floyd的方式来计算
         */
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    double minlength = max(G[i][k], G[k][j]);

                    if (minlength < G[i][j]) {
                        G[i][j] = minlength;
                    }  // if  update min
                }      // for j
            }          // for i
        }              // for k

        printf(SCENARIO "\n", id);
        printf(DISTANCE "\n\n", G[1][2]);
    }  // while

    return 0;
}  // function main
