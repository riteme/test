/**
 * 这题好暴力，根本不敢想啊
 * 首先很容易发现，确定第一行和第一列就可以得知整个矩阵
 * 因此可以优化暴力
 * 如何进一步优化暴力？
 * 需要通过手动计算一个4x4的矩阵中，确定第一行和第一列后
 * 将剩下的每一个元素完全展开，就会发现
 * M[i][j]与M[1][1]、M[1][j]和M[i][1]有关
 * 当然剩下的是以(i, j)为右下角的矩形的
 * 每一个斜行的交错和
 * 计算这个交错和可以递归：
 * pre[i][j] = S[i][j] - pre[i - 1][j] - pre[i][j - 1] - pre[i - 1][j - 1]
 * 注意到M[i][j]、M[1][1]、M[1][j]、M[i][1]四个构成一个方程
 * 如果确定第一行，那么M[i][j]和M[i][1]的之和或之差为定值
 * 可以确定M[i][1]的范围
 * 因此枚举第一行，更新第一列的范围，如果已经有元素无解就放弃，
 * 否则如果第一行枚举完毕后没有问题，那么第一列可以取允许范围内的最小值
 * 神奇的剪枝.....复杂度不管了。
 */

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200
#define PMAX 10

static int n, m, q;
static int S[NMAX + 10][NMAX + 10];
static int pre[NMAX + 10][NMAX + 10];
static int mat[NMAX + 10][NMAX + 10];
static int line[NMAX + 10];
static int left[NMAX + 10][NMAX + 10];
static int right[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &S[i][j]);
            pre[i][j] = S[i][j] -
                        (pre[i - 1][j] + pre[i][j - 1] + pre[i - 1][j - 1]);
        }
    }
}

static bool dfs(int x) {
    if (x > m)
        return true;

    for (int i = 0; i < q; i++) {
        line[x] = i;

        bool ok = true;
        for (int y = 2; y <= n; y++) {
            int c = pre[y][x] +
                    (((x + y - 1) & 1) ? -1 : 1) * line[1] +
                    (((y - 1) & 1) ? -1 : 1) * line[x];

            if (x & 1) {
                left[x][y] = max(left[x - 1][y], -c);
                right[x][y] = min(right[x - 1][y], q - c - 1);
            } else {
                left[x][y] = max(left[x - 1][y], c - q + 1);
                right[x][y] = min(right[x - 1][y], c);
            }

            if (left[x][y] > right[x][y]) {
                ok = false;
                break;
            }
        }

        if (ok && dfs(x + 1))
            return true;
    }

    return false;
}

int main() {
    initialize();

    for (int i = 2; i <= n; i++) {
        left[1][i] = 0;
        right[1][i] = q - 1;
    }

    for (int i = 0; i < q; i++) {
        line[1] = i;

        if (dfs(2))
            break;
    }

    for (int i = 1; i <= m; i++) {
        mat[1][i] = line[i];
    }

    for (int i = 2; i <= n; i++) {
        mat[i][1] = left[m][i];
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            mat[i][j] = S[i][j] - 
                        mat[i - 1][j] - mat[i][j - 1] - 
                        mat[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d", mat[i][j]);

            if (j < m)
                printf(" ");
        }

        if (i < n)
            printf("\n");
    }

    return 0;
}
