#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr i64 MOD = 998244353;
constexpr i64 INV2 = (MOD + 1) / 2;

i64 l(i64 l, i64 r) {
    return r - l + 1;
}

i64 s(i64 n) {
    return n * (n + 1) % MOD * INV2 % MOD;
}

i64 s(i64 l, i64 r) {
    return (s(r) - s(l - 1)) % MOD;
}

int main() {
    i64 n, m, q;
    scanf("%lld%lld%lld", &n, &m, &q);

    while (q--) {
        i64 a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        i64 ans = 0;

        i64 imax = b / 2;
        i64 imin = (a + 1) / 2;
        i64 jmax = d / 2;
        i64 jmin = (c + 1) / 2;
        ans = (ans + 2 * m * s(imin, imax) % MOD * l(jmin, jmax)) % MOD;
        ans = (ans - m * l(imin, imax) % MOD * l(jmin, jmax)) % MOD;
        ans = (ans + 2 * l(imin, imax) * s(jmin, jmax)) % MOD;

        imax = (b - 1) / 2;
        imin = a / 2;
        jmax = (d - 1) / 2;
        jmin = c / 2;
        ans = (ans + 2 * m * s(imin, imax) % MOD * l(jmin, jmax)) % MOD;
        ans = (ans + l(imin, imax) % MOD * l(jmin, jmax)) % MOD;
        ans = (ans + 2 * l(imin, imax) * s(jmin, jmax)) % MOD;

        if (ans < 0)
            ans += MOD;
        printf("%lld\n", ans);
    }

    return 0;
}
