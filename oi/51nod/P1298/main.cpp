#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define EPS 1e-8

template <typename T>
bool eq(T x, decltype(x) y) {
    return abs(x - y) < EPS;
}

struct vec {
    vec() : x(0), y(0) {}
    vec(double _x, double _y) : x(_x), y(_y) {}

    double x, y;

    double len() const {
        return hypot(x, y);
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }
};

double dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

double cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

double psdist(const vec &p, const vec &u, const vec &v) {
    vec d = u - v;
    if (dot(p - v, d) > -EPS && dot(p - u, d) < EPS)
        return abs(cross(p - v, d) / d.len());
    return min((p - v).len(), (p - u).len());
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        vec O, A, B, C;
        double r;
        scanf("%lf%lf%lf", &O.x, &O.y, &r);
        scanf("%lf%lf", &A.x, &A.y);
        scanf("%lf%lf", &B.x, &B.y);
        scanf("%lf%lf", &C.x, &C.y);

        double mi = min(
            psdist(O, A, B),
            min(
            psdist(O, B, C),
            psdist(O, C, A)
        ));
        double mx = max(
            (A - O).len(),
            max(
            (B - O).len(),
            (C - O).len()
        ));
        puts(mi - EPS < r && r < mx + EPS? "Yes" : "No");
    }
    return 0;
}
