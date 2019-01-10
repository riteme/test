#include <cstdio>

#include <algorithm>

using namespace std;

typedef long long i64;

// 0 for white, 1 for black
inline i64 cnt(i64 x1, i64 y1, i64 x2, i64 y2, int c) {
    if (x1 > x2 || y1 > y2) return 0;
    i64 m = x2 - x1 + 1, n = y2 - y1 + 1;
    i64 ans = n * (m / 2) + (m & 1 ? (n + 1) / 2 : 0);
    if ((x1 + y1) & 1) ans = n * m - ans;
    if (c) ans = n * m - ans;
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        i64 n, m;
        scanf("%lld%lld", &n, &m);
        i64 w = cnt(1, 1, m, n, 0);
        i64 x1, y1, x2, y2;
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        w += cnt(x1, y1, x2, y2, 1);
        i64 x3, y3, x4, y4;
        scanf("%lld%lld%lld%lld", &x3, &y3, &x4, &y4);
        w -= cnt(x3, y3, x4, y4, 0);
        i64 xl = max(x1, x3), xr = min(x2, x4);
        i64 yl = max(y1, y3), yr = min(y2, y4);
        w -= cnt(xl, yl, xr, yr, 1);
        printf("%lld %lld\n", w, n * m - w);
    }
    return 0;
}
