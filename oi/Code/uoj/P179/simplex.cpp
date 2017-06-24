/**
 * 基本步骤：
 * 1. 实现pivot换主元
 * 2. 寻找初始解，将所有的负常数项用pivot掰正，注意随机化
 * 3. 求解线性规划，选取目标函数中系数为正的项调大，注意Bland法则
 * 4. 如果需要输出方案，则记录一个id
 * 时间复杂度O(nm * k)，k是迭代次数
 */

// #define NDEBUG

#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define NMAX 20
#define EPS 1e-8
#define INF 1e100

class Simplex {
 public:
    void initialize() {
        scanf("%d%d%d", &n, &m, &t);

        memset(A, 0, sizeof(A));
        for (int i = 1; i <= n; i++) {
            idx[i] = i;
            scanf("%lf", A[0] + i);
        }

        for (int i = 1; i <= m; i++) {
            idy[i] = n + i;
            for (int j = 1; j <= n; j++) {
                scanf("%lf", A[i] + j);
                A[i][j] *= -1;
            }

            scanf("%lf", A[i]);
        }
    }

    void solve() {
        srand(time(0));

        while (true) {
            int x = 0, y = 0;
            for (int i = 1; i <= m; i++) {
                if (A[i][0] < -EPS && (!y || (rand() & 1)))
                    y = i;
            }

            if (!y)
                break;

            for (int i = 1; i <= n; i++) {
                if (A[y][i] > EPS && (!x || (rand() & 1)))
                    x = i;
            }

            if (!x) {
                puts("Infeasible");
                return;
            }

            pivot(x, y);
        }

        while (true) {
            double k = INF;
            int x, y;
            for (x = 1; x <= n; x++) {
                if (A[0][x] > EPS)
                    break;
            }

            if (x > n)
                break;

            for (int i = 1; i <= m; i++) {
                double d = A[i][x] > -EPS ? INF : -A[i][0] / A[i][x];
                if (d < k) {
                    k = d;
                    y = i;
                }
            }

            if (k >= INF) {
                puts("Unbounded");
                return;
            }

            pivot(x, y);
        }

        printf("%.8lf\n", A[0][0]);

        if (t) {
            static double ans[NMAX + 10];
            for (int i = 1; i <= m; i++) {
                if (idy[i] <= n)
                    ans[idy[i]] = A[i][0];
            }

            for (int i = 1; i <= n; i++) {
                printf("%.8lf ", ans[i]);
            }
            printf("\n");
        }
    }

 private:
    void pivot(int x, int y) {
        swap(idx[x], idy[y]);
        double r = -A[y][x];
        A[y][x] = -1;
        for (int i = 0; i <= n; i++) {
            A[y][i] /= r;
        }

        for (int i = 0; i <= m; i++) {
            if (i == y)
                continue;

            r = A[i][x];
            A[i][x] = 0;
            for (int j = 0; j <= n; j++) {
                A[i][j] += r * A[y][j];
            }
        }
    }

    int n, m, t;
    double A[NMAX + 10][NMAX + 10];
    int idx[NMAX + 10], idy[NMAX + 10];
};

int main() {
    // freopen("data.in", "r", stdin);
    Simplex solver;
    solver.initialize();
    solver.solve();

    return 0;
}
