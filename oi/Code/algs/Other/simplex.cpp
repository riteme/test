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

#define NMAX 50
#define EPS 1e-11
#define INF 1e100

// x0 = 1
static int n, m, t, cnt;
static double A[NMAX + 10][NMAX + 10];  // A[1..n]为等式约束, A[0]为目标函数系数
static bool B[NMAX + 10];  // 是否为基本变量

void pivot(int x, int y) {
    memcpy(A[x], A[y], sizeof(double) * (n + 1));
    A[x][x] = 0; A[x][y] = -1;
    B[x] = true; B[y] = false;

    for (int i = 0; i <= n; i++) {
        A[x][i] /= -A[y][x];
    }

    for (int i = 0; i <= n; i++) {
        if (!B[i] || i == x)
            continue;

        for (int j = 0; j <= n; j++) {
            A[i][j] += A[i][x] * A[x][j];
        }

        A[i][x] = 0;
    }
}

void simplex() {
    B[0] = true;

    // 注意寻找可行解时需要随机扰动
    while (true) {
        double d = -EPS;
        int x = 0, y = 0;
        for (int i = 1; i <= n; i++) {
            if (B[i] && A[i][0] < d && (y == 0 || (rand() & 1))) {
                y = i;
                d = A[i][0];
            }
        }

        if (!y)
            break;

        for (int i = 1; i <= n && !x; i++) {
            if (A[y][i] > EPS && (x == 0 || (rand() & 1)))
                x = i;
        }

        if (!x) {
            puts("Infeasible");
            return;
        }

        pivot(x, y);
    }

    // 一定选取最小的标号（Bland法则）
    while (true) {
        int x, y;
        for (x = 1; x <= n; x++) {
            if (!B[x] && A[0][x] > EPS)
                break;
        }

        if (x > n)
            break;

        double d = INF;
        for (int i = 1; i <= n; i++) {
            if (!B[i])
                continue;

            double delta = A[i][x] > -EPS ? INF : A[i][0] / -A[i][x];
            if (delta < d) {
                y = i;
                d = delta;
            }
        }

        if (d >= INF) {
            puts("Unbounded");
            return;
        }

        pivot(x, y);
    }

    printf("%.8lf\n", A[0][0]);

    if (t == 1) {
        for (int i = 1; i <= cnt; i++) {
            if (B[i])
                printf("%.8lf ", A[i][0]);
            else
                printf("0 ");
        }

        printf("\n");
    }
}

void initialize() {
    srand(time(0));
    scanf("%d%d%d", &n, &m, &t);

    for (int i = 1; i <= n; i++) {
        scanf("%lf", A[0] + i);
    }

    for (int i = n + 1; i <= n + m; i++) {
        B[i] = true;
        for (int j = 1; j <= n; j++) {
            scanf("%lf", A[i] + j);
            A[i][j] *= -1;
        }

        scanf("%lf", A[i]);
    }

    cnt = n;
    n += m;
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();
    simplex();

    return 0;
}
