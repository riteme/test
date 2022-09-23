#include <cmath>
#include <cstdio>

using d8 = long double;
using i64 = long long;

int main() {
    i64 n, m;
    scanf("%lld%lld", &n, &m);
    d8 c = std::sqrt(2.0L * M_PI * n * m / (n + m));
    d8 lc = std::log(c);
    d8 ln = std::log(d8(n));
    d8 lm = std::log(d8(m));
    d8 lp = std::log(2.0L / (n + m));
    d8 e = lc + n * ln + m * lm + (n + m) * lp;
    d8 ans = std::exp(e);

    if (ans >= 0.99e9)
        puts("Extreme Wealth");
    else
        printf("%.15Lf\n", ans);

    return 0;
}