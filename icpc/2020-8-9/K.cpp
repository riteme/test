#include <cmath>
#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define TMAX 40
#define NMAX 100
#define EPS 1e-10

bool eq(double x, double y) {
    return fabs(x - y) < EPS;
}

struct vec {
    vec() : x(0), y(0) {}
    vec(double _x, double _y) : x(_x), y(_y) {}

    double x, y;

    int idx() const {
        if (x >= 0 && y >= 0)
            return 1;
        if (x <= 0 && y >= 0)
            return 2;
        if (x <= 0 && y <= 0)
            return 3;
        return 4;
    }

    double len() const {
        return hypot(x, y);
    }

    vec norm() const {
        double l = len();
        return {x / l, y / l};
    }

    vec cw() const {
        return vec(y, -x);
    }

    vec ccw() const {
        return vec(-y, x);
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }

    vec operator*(double k) const {
        return {x * k, y * k};
    }

    double operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    double operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }

    vec &operator+=(const vec &z) {
        x += z.x;
        y += z.y;
        return *this;
    }

    bool operator<(const vec &z) const {
        if (idx() != z.idx())
            return idx() < z.idx();
        double c = (*this) % z;
        return eq(c, 0.0) ? len() < z.len() : c > 0;
    }
};

struct line {
    line() : u(0, 0), v(0, 0) {}
    line(vec _u, vec _v) : u(_u), v(_v) {}

    vec u, v;

    bool include(const vec &p) const {
        return v % (p - u) > EPS;
    }

    bool same_dir(const line &z) const {
        return eq(v % z.v, 0.0) && v * z.v > EPS;
    }

    bool operator<(const line &z) const {
        if (same_dir(z))
            return z.include(u);
        return v < z.v;
    }
};

vec isect(const line &a, const line &b) {
    vec z = b.u - a.u;
    double t = (b.v % z) / (b.v % a.v);
    return a.u + a.v * t;
}

int n, m;
vec A[NMAX + 10], B[NMAX + 10];

void initialize() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &A[i].x, &A[i].y);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lf%lf", &B[i].x, &B[i].y);
    }
}

int cnt;
line ln[NMAX * NMAX + 10];

int sgn(double x) {
    if (eq(x, 0.0))
        return 0;
    return x > 0 ? 1 : -1;
}

bool chk(const line &a, const line &b, const line &c) {
    return c.include(isect(a, b));
}

bool half_plane_intersection() {
    sort(ln, ln + cnt);
    deque<line> q;
    for (int i = 0; i < cnt; i++) {
        if (i && ln[i].same_dir(ln[i - 1]))
            continue;
        while (q.size() > 1 && !chk(q[q.size() - 2], q[q.size() - 1], ln[i])) {
            q.pop_back();
        }
        while (q.size() > 1 && !chk(q[1], q[0], ln[i])) {
            q.pop_front();
        }
        q.push_back(ln[i]);
    }
    while (q.size() > 2 && !chk(q[q.size() - 2], q[q.size() - 1], q[0])) {
        q.pop_back();
    }
    while (q.size() > 2 && !chk(q[1], q[0], q[q.size() - 1])) {
        q.pop_front();
    }
    return q.size() > 2;
}

int nxtp(int i) {
    return i + 1 < n ? i + 1 : 0;
}

bool test(double d) {
    cnt = 0;
    for (int i = 0; i < n; i++) {
        vec v = A[nxtp(i)] - A[i];
        vec w = v.ccw().norm();
        for (int j = 0; j < m; j++) {
            ln[cnt++] = {A[i] + w * d - B[j], v};
        }
    }

    return half_plane_intersection();
}

int main() {
    initialize();

    double l = 0, r = 1e4;
    for (int _ = 0; _ < TMAX; _++) {
        double mi = (l + r) / 2;
        if (test(mi))
            l = mi;
        else
            r = mi;
    }
    printf("%.12lf\n", l / 2);

    return 0;
}
