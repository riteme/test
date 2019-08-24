#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
  
#include <cmath>
#include <cstdio>
#include <cstring>
  
#include <algorithm>
  
using namespace std;
  
typedef double ld;
  
#define NMAX 300
#define TMAX 40
#define EPS 1e-9
  
inline bool equ(ld a, ld b) {
    return a - EPS < b && b < a + EPS;
}
  
struct Point {
    Point() : x(0), y(0) {}
    Point(ld _x, ld _y) : x(_x), y(_y) {}
  
    ld x, y;
  
    ld len() const {
        return hypot(x, y);
    }
  
    ld len2() const {
        return x * x + y * y;
    }
  
    Point ortho() const {
        return {y, -x};
    }
  
    Point norm() const {
        ld l = len();
        return {x / l, y / l};
    }
  
    Point operator+(const Point &z) const {
        return {x + z.x, y + z.y};
    }
  
    Point operator-(const Point &z) const {
        return {x - z.x, y - z.y};
    }
  
    Point operator*(ld k) const {
        return {x * k, y * k};
    }
};
  
inline ld dot(const Point &u, const Point &v) {
    return u.x * v.x + u.y * v.y;
}
  
inline ld cross(const Point &u, const Point &v) {
    return u.x * v.y - u.y * v.x;
}
  
static int n;
static Point p[NMAX + 10];
  
inline bool test(ld r, const Point &u, const Point &v) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        auto d = p[i] - u;
        auto c = cross(v, d);
        if (equ(c, 0)) return false;
        auto l = dot(v, d) / v.len();
        auto h = sqrt(d.len2() - l * l);
        if (h <= r - EPS) return false;
        cnt += c < 0 ? 1 : -1;
    }
    return cnt == 0;
}
  
inline bool test(ld r) {
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
        auto dist = (p[i] - p[j]).len();
        if ((p[i] - p[j]).len() <= 2 * r - EPS) continue;
        auto m = (p[i] + p[j]) * 0.5;
        auto v = (m - p[i]);
        if (equ(dist, 2 * r)) {
            if (test(r, m, v.ortho())) return true;
            continue;
        }
        auto h2 = r * r * (1 - r * r / v.len2());
        v = v.ortho().norm() * sqrt(h2);
        auto u = (m - p[i]).norm() * sqrt(max(0.0, r * r - h2));
        if (test(r, m, p[i] + u + v - m) ||
            test(r, m, p[i] + u - v - m)) return true;
    }
    return false;
}
  
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
    ld l = 0, r = 4e6;
    for (int _t = 0; _t < TMAX; _t++) {
        ld m = (l + r) * 0.5;
        if (test(m)) l = m;
        else r = m;
    }
    printf("%.12lf\n", (l + r) * 0.5);
    return 0;
}
