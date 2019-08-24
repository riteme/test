#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

#define NDEBUG

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define EPS 1e-9

struct Point {
    Point() : x(0), y(0) {}
    Point(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    i64 len2() const {
        return x * x + y * y;
    }

    Point ortho() const {
        return {-y, x};
    }

    Point operator+(const Point &z) const {
        return {x + z.x, y + z.y};
    }

    Point operator-(const Point &z) const {
        return {x - z.x, y - z.y};
    }

    Point operator*(i64 k) const {
        return {x * k, y * k};
    }

    bool operator==(const Point &z) const {
        return x == z.x && y == z.y;
    }
};

inline i64 dot(const Point &u, const Point &v) {
    return u.x * v.x + u.y * v.y;
}

inline i64 cross(const Point &u, const Point &v) {
    return u.x * v.y - u.y * v.x;
}

inline int convex(Point *p, int n) {
    static Point tmp[NMAX + 10];
    static int stk[NMAX + 10], cnt;
    int oi = 0;
    for (int i = 1; i < n; i++)
        if (p[i].x < p[oi].x || (p[i].x == p[oi].x && p[i].y < p[oi].y))
            oi = i;
    swap(p[0], p[oi]);
    sort(p + 1, p + n, [p](const Point &u, const Point &v) {
        auto u0 = u - p[0], v0 = v - p[0];
        i64 x = cross(u0, v0);
        return x > 0 || (x == 0 && u0.len2() < v0.len2());
    });
    cnt = 1;
    for (int i = 1; i < n; i++) {
        while (cnt > 1 && cross(p[i] - p[stk[cnt - 2]], p[stk[cnt - 1]] - p[stk[cnt - 2]]) >= 0)
            cnt--;
        stk[cnt++] = i;
    }
    int head = 0, tail = n - 1;
    for (int i = 0, j = 0; i < n; i++)
        if (j < cnt && i == stk[j]) tmp[head++] = p[i], j++;
        else tmp[tail--] = p[i];
    memcpy(p, tmp, sizeof(Point) * n);
    return cnt;
}

static int n;
static Point p[NMAX + 10];

inline double dist(const Point &u, const Point &a, const Point &b) {
    if (a == b) return sqrt((u - a).len2());
    if (dot(u - a, b - a) >= 0 && dot(u - b, a - b) >= 0) {
        i64 l2 = (u - a).len2();
        double s = dot(u - a, b - a) / sqrt((b - a).len2());
        //printf("u = (%lld, %lld), (%lld, %lld) - (%lld, %lld), %.4lf\n",
        //        u.x, u.y, a.x, a.y, b.x, b.y, sqrt(l2 - s * s));
        return sqrt(max(0.0, l2 - s * s));
    } else return sqrt(min((u - a).len2(), (u - b).len2()));
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", &p[i].x, &p[i].y);
    int m = n >> 1;
    double ans = 0;

    srand(time(0));
    sort(p + 1, p + n + 1, [](const Point &u, const Point &v) {
        return u.x < v.x || (u.x == v.x && u.y < v.y);
    });
    for (int c = 0; c < 5 * n; c++) {
        int lc = convex(p + 1, m);
        int rc = convex(p + m + 1, m);
        double mi = 1e9;
        for (int i = 1; i <= lc; i++) for (int j = 1; j <= rc; j++)
            mi = min(mi, dist(p[i], p[m + j], p[j == rc ? m + 1 : m + j + 1]));
        for (int j = 1; j <= rc; j++) for (int i = 1; i <= lc; i++)
            mi = min(mi, dist(p[m + j], p[i], p[i == lc ? 1 : i + 1]));
        ans = max(ans, mi);
#ifndef NDEBUG
        printf("lc = %d, rc = %d\n", lc, rc);
        for (int i = 1; i <= m; i++) printf("(%lld, %lld) ", p[i].x, p[i].y);
        puts("");
        for (int i = m + 1; i <= n; i++) printf("(%lld, %lld) ", p[i].x, p[i].y);
        printf("\nmi = %.4lf\n", mi * 0.5);
#endif

        int ct = 0;
        for (; ct <= m; ct++) {
            auto *ir = min_element(p + m + 1, p + n + 1, [m](const Point &u, const Point &v) {
                auto u0 = u - p[m], v0 = v - p[m];
                i64 x = cross(u0, v0);
                return x > 0 || (x == 0 && u0.len2() < v0.len2());
            });
            auto *il = max_element(p + 1, p + m + 1, [m](const Point &u, const Point &v) {
                auto u0 = u - p[m + 1], v0 = v - p[m + 1];
                i64 x = cross(u0, v0);
                return x < 0 || (x == 0 && u0.len2() < v0.len2());
            });
            swap(*il, p[m]);
            swap(*ir, p[m + 1]);
            bool ok = true;
            for (int i = 1; i <= m && ok; i++)
                ok &= cross(p[i] - p[m + 1], p[m] - p[m + 1]) <= 0;
            for (int i = m + 1; i <= n && ok; i++)
                ok &= cross(p[i] - p[m], p[m + 1] - p[m]) <= 0;
            if (ok) break;
        }
        swap(p[m], p[m + 1]);
        if (ct > m) {
            Point d = p[m] - p[m + 1];
            d = {d.x * 10000 + rand() % 11 - 5, d.y * 10000 + rand() % 11 - 5};
            sort(p + 1, p + n + 1, [&d](const Point &u, const Point &v) {
                return cross(u - v, d) > 0;
            });
            c--;
        }
    }
    printf("%.12lf\n", ans * 0.5);
    return 0;
}
