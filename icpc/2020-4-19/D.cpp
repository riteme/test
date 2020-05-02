#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;
typedef long double d8;
typedef unsigned long long u64;

#define NMAX 500000

int sgn(i64 x1, i64 y1, i64 x2, i64 y2) {
    d8 hi1 = d8(x1) * y2;
    d8 hi2 = d8(x2) * y1;
    if (hi1 < hi2)
        return -1;
    if (hi1 > hi2)
        return 1;

    int s = hi1 >= 0 ? +1 : -1;
    u64 lo1 = u64(abs(x1)) * abs(y2);
    u64 lo2 = u64(abs(x2)) * abs(y1);
    if (lo1 == lo2)
        return 0;
    return (lo1 < lo2 ? -1 : 1) * s;
}

int n;
struct Foo {
    i64 a, b;
    i64 x, y;

    bool operator!=(const Foo &z) const {
        i64 x1 = x, y1 = y - a;
        i64 x2 = z.x, y2 = z.y - z.a;
        return sgn(x1, y1, x2, y2) != 0;
    }

    bool operator<(const Foo &z) const {
        i64 x1 = x, y1 = y - a;
        i64 x2 = z.x, y2 = z.y - z.a;
        return sgn(x1, y1, x2, y2) < 0;
    }
} p[NMAX + 10];

int f[NMAX + 10], m;
i64 lp[NMAX + 10];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &p[i].a, &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1);
    p[1].b = 1;
    for (int i = 2, j = 1; i <= n; i++) {
        if (p[i] != p[i - 1])
            j++;
        p[i].b = j;
    }

    sort(p + 1, p + n + 1, [](const Foo &u, const Foo &v) {
        return u.a > v.a;
    });

    m = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = upper_bound(lp, lp + m, p[i].b) - lp;
        if (f[i] >= m)
            lp[m++] = LLONG_MAX;
        lp[f[i]] = min(lp[f[i]], p[i].b);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}