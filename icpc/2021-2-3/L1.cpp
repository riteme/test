#include <cmath>
#include <cstdio>

using d8 = long double;
using i64 = long long;

constexpr d8 INF0 = 1e30;
constexpr i64 T = 5000;

d8 f[5500][5500];

int main() {
    for (int i = 0; i < T; i++) {
        f[i][0] = f[0][i] = pow(2, i);
    }
    for (int s = 1; s < T; s++)
    for (int i = 1; i < s; i++) {
        int j = s - i;
        f[i][j] = 2 * f[i - 1][j] * f[i][j - 1] / (f[i - 1][j] + f[i][j - 1]);
        if (f[i][j] >= INF0)
            f[i][j] = INF0;
    };

    i64 n, m;
    scanf("%lld%lld", &n, &m);
    d8 ans;
    if (n + m < T) {
        ans = std::log(f[n][m]);
    } else {
        d8 c = std::sqrt(2.0L) + std::log(M_PI) + std::log(n) + std::log(m) - std::log(n + m);
        d8 lc = std::log(c);
        d8 ln = std::log(d8(n));
        d8 lm = std::log(d8(m));
        d8 lp = std::log(2.0L) - std::log(n + m);
        ans = lc + n * ln + m * lm + (n + m) * lp;
    }

    if (ans >= std::log(0.99e9L))
        puts("Extreme Wealth");
    else
        printf("%.15Lf\n", std::exp(ans));

    return 0;
}