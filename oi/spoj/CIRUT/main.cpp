#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define EPS 1e-8
#define NMAX 1000

template <typename T>
bool eq(T x, decltype(x) y) {
    return std::abs(x - y) < EPS;  // abs != std::abs
}

struct vec {
    vec() : x(0), y(0) {}
    vec(double _x, double _y) : x(_x), y(_y) {}

    double x, y;

    double len() const {
        return hypot(x, y);
    }

    int region() const {
        if (x > -EPS && y > -EPS) return 1;  // vec(1, 0) should be place at first element. avoid floating poing discrepencies
        if (x <= 0 && y >= 0) return 2;
        if (x <= 0 && y <= 0) return 3;
        return 4;
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

    vec &operator/=(double k) {
        x /= k;
        y /= k;
        return *this;
    }

    friend bool operator<(const vec &u, const vec &v);
};

double dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

double cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

bool operator<(const vec &u, const vec &v) {
    int ui = u.region();
    int vi = v.region();
    return ui < vi || (ui == vi && cross(u, v) > 0);
}

struct cir {
    vec C;
    double r;
};

double p2arc(double r, const vec &u, const vec &v) {
    if (eq(u.x, v.x) && eq(u.y, v.y))
        return 0;
    double d = dot(u, v);
    double cr = cross(u, v);
    double t = acos(max(-1.0, min(1.0, d / r / r)));  // avoid nan
    return cr > 0 ? t : 2 * M_PI - t;
}

enum IntersectStatus {
    ISEPARATE = 1,
    IOUTERT,
    ICROSS,
    IINNERT,
    ICONTAIN
};

struct IntersectResult {
    vec u, v;  // counterclockwise w.r.t. circle a
    IntersectStatus stat;
};

IntersectResult intersect(const cir &a, const cir &b) {
    vec p = b.C - a.C;
    double d = p.len(), d0 = max(a.r, b.r) - min(a.r, b.r);

    IntersectStatus stat;
    if (a.r + b.r <= d - EPS) stat = ISEPARATE;
    else if (eq(a.r + b.r, d)) stat = IOUTERT;
    else if (d - EPS >= d0) stat = ICROSS;
    else if (eq(d, d0)) stat = IINNERT;
    else stat = ICONTAIN;

    double
    R2 = a.r * a.r,
    t = (R2 - b.r * b.r) / d,
    L = (d + t) * 0.5,
    H = sqrt(max(0.0, R2 - L * L));

    p /= d;
    vec v = vec(p.y, -p.x) * H;
    vec O = a.C + p * L;
    return {O + v, O - v, stat};
}

struct Point {
    vec v;
    int d;
};

static int n, m;
static cir C[NMAX + 10];
Point p[2 * NMAX + 10];
static double area[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &C[i].C.x, &C[i].C.y, &C[i].r);

    // assert C[i] != C[j]
    for (int i = 1; i <= n; i++) {
        m = 0;
        int cov = 0;
        for (int j = 1; j <= n; j++) if (i != j) {
            auto r = intersect(C[i], C[j]);
            if (r.stat == IINNERT || r.stat == ICONTAIN)
                cov += C[i].r < C[j].r + EPS;
            if (r.stat != ICROSS)
                continue;
            p[m++] = {r.u - C[i].C, +1};
            p[m++] = {r.v - C[i].C, -1};
            double cr = cross(r.v - r.u, vec(C[i].r, 0) - p[m - 2].v);
            //assert(!eq(cr, 0));
            cov += cr <= -EPS || (eq(cr, 0) && !eq(p[m - 2].v.x, C[i].r));  // endpoint overlap
            //printf("i = %d, j = %d, cov = %d\n", i, j, cov);
        }

        if (m) {
            sort(p, p + m, [](const Point &u, const Point &v) {
                return u.v < v.v;
            });
            for (int j = 0; j < m; j++) {
                if (j)
                    p[j].d += p[j - 1].d;
                int k = j + 1 < m ? j + 1 : 0;
                double t = p2arc(C[i].r, p[j].v, p[k].v);
                area[cov + p[j].d + 1] += (
                    t * C[i].r * C[i].r -
                    cross(p[j].v, p[k].v) +
                    cross(C[i].C + p[j].v, C[i].C + p[k].v)
                ) * 0.5;
            }
        } else
            area[cov + 1] += M_PI * C[i].r * C[i].r;
    }
    for (int i = 1; i < n; i++)
        area[i] -= area[i + 1];

    for (int i = 1; i <= n; i++)
        printf("[%d] = %.3lf\n", i, max(0.0, area[i]));  // avoid -0.0

    return 0;
}

/*
int main() {
    cir a, b;
    while (
        scanf("%lf%lf%lf%lf%lf%lf",
            &a.C.x, &a.C.y, &a.r, &b.C.x, &b.C.y, &b.r) != EOF) {
        auto r = intersect(a, b);
        printf("[%d] (%.4lf, %.4lf), (%.4lf, %.4lf)\n",
                r.stat, r.u.x, r.u.y, r.v.x, r.v.y);
    }

    return 0;
}
*/
