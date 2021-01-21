#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000;
constexpr i64 INF = 0x3f3f3f3f;

int n, m;
i64 f[NMAX + 10];
i64 s[NMAX + 10], p[NMAX + 10];
i64 w[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int i = 1; i <= m; i++) {
            scanf("%lld%lld", s + i, p + i);
        }

        for (int i = 0; i <= NMAX + 5; i++) {
            w[i] = INF;
        }

        for (int i = 1; i <= m; i++) {
            w[s[i]] = min(w[s[i]], p[i]);
        }

        for (int i = NMAX; i >= 0; i--) {
            w[i] = min(w[i], w[i + 1]);
            f[i] += w[i];
        }
    }

    i64 s0 = 1, p0 = f[1];
    for (int i = 2; i <= NMAX; i++) {
        i64 d = i * p0 - s0 * f[i];
        if (d > 0 || (d == 0 && p0 > f[1])) {
            s0 = i;
            p0 = f[i];
        }
    }

    printf("%lld\n", p0);

    return 0;
}
