#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define TMAX 100
#define EPS 1e-8

struct Point {
    Point() = default;
    Point(double _x, double _y) : x(_x), y(_y) {}

    double x = 0, y = 0;

    bool zero() const {
        return -EPS < x && x < EPS && -EPS < y && y < EPS;
    }

    auto operator+(const Point &b) const -> Point {
        return {x + b.x, y + b.y};
    }

    auto operator-(const Point &b) const -> Point {
        return {x - b.x, y - b.y};
    }

    auto operator*(const double &k) const -> Point {
        return {x * k, y * k};
    }

    auto operator/(const double &k) const -> Point {
        return {x / k, y / k};
    }

    auto operator+=(const Point &b) -> Point& {
        x += b.x;
        y += b.y;
        return *this;
    }

    auto operator-=(const Point &b) -> Point& {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    auto operator*=(const double &k) -> Point& {
        x *= k;
        y *= k;
        return *this;
    }

    auto operator/=(const double &k) -> Point& {
        x /= k;
        y /= k;
        return *this;
    }
};

inline double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

inline Point sect(const Point &p1, const Point &v1, const Point &p2, const Point &v2) {
    double t = cross(p2 - p1, v1) / cross(v1, v2);
    return p2 + v2 * t;
}

static int n;
static Point p;
static double X[NMAX + 10], Y[NMAX + 10], w[NMAX + 10];
static double d1[NMAX + 10], d3[NMAX + 10];

inline void update() {
    for (int i = 1; i <= n; i++) {
        double d = hypot(p.x - X[i], p.y - Y[i]);
        d1[i] = w[i] / d;
        d3[i] = w[i] / (d * d * d);
    }
}

inline void f(Point &o) {
    o = {0, 0};
    for (int i = 1; i <= n; i++) {
        o.x += (p.x - X[i]) * d1[i];
        o.y += (p.y - Y[i]) * d1[i];
    }
}

inline void df(Point &o1, Point &o2) {
    o1 = {0, 0}, o2.y = 0;
    for (int i = 1; i <= n; i++) {
        double dx = p.x - X[i], dy = p.y - Y[i];
        o1.x += dy * dy * d3[i];
        o2.y += dx * dx * d3[i];
        o1.y += dx * dy * d3[i];
    }
    o2.x = o1.y = -o1.y;
}

inline double l2(const Point &b) {
    return b.x * b.x + b.y * b.y;
}

void solve() {
    Point u, dx, dy;
    for (int t = TMAX; t; t--) {
        printf("%.3lf %.3lf\n", p.x, p.y);
        update();
        f(u);
        if (u.zero()) break;
        df(dx, dy);
        Point v1 = dx * u.x / l2(dx), v2 = dy * u.y / l2(dy);
        if (v1.zero()) p -= v2;
        else if (v2.zero()) p -= v1;
        else p -= sect(u + v1, {v1.y, -v1.x}, u + v2, {v2.y, -v2.x});
    }
}

int main() {
    scanf("%d", &n);
    double W = 0.0;
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", X + i, Y + i, w + i);
        p += Point(X[i], Y[i]) * w[i];
        W += w[i];
    }
    p /= W;
    solve();
    printf("%.3lf %.3lf\n", p.x, p.y);
    return 0;
}
