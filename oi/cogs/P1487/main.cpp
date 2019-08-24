/**
 * 设f(m)为一个毛球开始，m天之前死掉的概率，于是可以递推：
 * f(m) = \sum_{k = 0}^{n - 1} p_{k} f^{k}(m - 1)
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 1000
#define KMAX 1000

static int n, K, m;
static double p[NMAX + 10];
static double f[MMAX + 10];

static void initialize() {
    memset(f, 0, sizeof(f));

    scanf("%d%d%d", &n, &K, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lf", p + i);
    }
}

int main() {
    freopen("tribbles.in", "r", stdin);
    freopen("tribbles.out", "w", stdout);

    int t;
    scanf("%d", &t);

    for (int cnt = 1; cnt <= t; cnt++) {
        initialize();

        f[1] = p[0];
        for (int i = 2; i <= m; i++) {
            f[i] = p[0];
            double iter = f[i - 1];
            for (int j = 1; j < n; j++) {
                f[i] += p[j] * iter;
                iter *= f[i - 1];
            }
        }

        double answer = 1.0;
        for (int i = 0; i < K; i++) {
            answer *= f[m];
        }

        printf("Case #%d: %.7lf\n", cnt, answer);
    }

    return 0;
}
