/**
 * 考虑每一轮谁被选中不好考虑，考虑按照顺序前i个会用掉j次机会的概率比较方便
 * 设f(i, j)为这个概率，那么考虑它可以递推到什么地方去
 * 自然是考虑i + 1，那么i + 1要么在后面的r - j轮中没有被选中一次
 * 要么被选中一次
 * 这概率分别为(1 - p(i + 1))^(r - j)和1 - (1 - p(i + 1))^(r - j)
 * (因为这两个加起来肯定是1)
 * 于是可以分别更新到f(i + 1, j)和f(i + 1, j + 1)
 * 对于初值：f(0, 0) = 1是肯定的
 * 对于每个卡牌的概率，就是第二个递推的时候累计一下
 * 然后计算期望
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define TMAX 444
#define NMAX 220
#define RMAX 132

static int n, r;
static double p[NMAX + 10];
static double tpow[NMAX + 10][RMAX + 10];
static int d[NMAX + 10];
static double coeff[NMAX + 10];
static double f[NMAX + 10][RMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &r);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%d", p + i, d + i);

        tpow[i][0] = 1.0;
        tpow[i][1] = 1.0 - p[i];
        for (int j = 2; j <= r; j++) {
            tpow[i][j] = tpow[i][j - 1] * tpow[i][1];
        }
    }

    memset(f, 0, sizeof(f));
    memset(coeff, 0, sizeof(coeff));
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        f[0][0] = 1.0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= r; j++) {
                double ppow = tpow[i + 1][r - j];
                f[i + 1][j] += f[i][j] * ppow;

                double delta = f[i][j] * (1 - ppow);
                f[i + 1][j + 1] += delta;
                coeff[i + 1] += delta;
            }
        }

        double answer = 0.0;
        for (int i = 1; i <= n; i++) {
            answer += coeff[i] * d[i];
        }

        printf("%.11lf\n", answer);
    }

    return 0;
}
