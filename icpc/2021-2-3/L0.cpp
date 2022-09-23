#include <cmath>
#include <cstdio>
#include <cassert>

#include <algorithm>

using namespace std;

using d8 = long double;
using i64 = long long;

constexpr i64 T = 5000000;

d8 C(i64 n) {
    return 1.0L + 1.0L / 12.0L / n;
}

int main() {
    i64 n, m;
    scanf("%lld%lld", &n, &m);

    if (n > m)
        swap(n, m);

    d8 ans = 0;
    if (n < T) {
        ans += logl(2) * (n + m);

        for (i64 i = 1; i <= n; i++) {
            ans += logl(i);
            ans -= logl(m + i);
        }
    } else {
        d8 ld = logl(C(n)) + logl(C(m)) - logl(C(n + m));
        d8 lc = 0.5L * (logl(2.0L) + logl(M_PI) + logl(n) + logl(m) - logl(n + m));
        d8 ln = logl(d8(n));
        d8 lm = logl(d8(m));
        d8 lp = logl(2.0L) - logl(n + m);
        ans = ld + lc + n * ln + m * lm + (n + m) * lp;
    }

    if (ans >= logl(1e9L))
        puts("Extreme Wealth");
    else
        printf("%.15Lf\n", expl(ans));

    return 0;
}