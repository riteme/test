#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define EPS 1e-10
#define INF 1e99

#define NMAX 1000
#define MMAX 3000000

struct vec {
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

    vec operator*(double k) const {
        return {x * k, y * k};
    }

    vec &operator/=(double k) {
        x /= k;
        y /= k;
        return *this;
    }
};

struct seg {
    vec u, v;
    double len() const {
        return (u - v).len();
    }
};

struct cir {
    vec p;
    double r;
};

void tangent(const cir &a, const cir &b, seg &s1, seg &s2) {
    // a.r >= b.r
    vec p = b.p - a.p;
    double R = a.r, r = b.r, d = p.len();
    double
    k = r / R,
    t1 = (R - r) / d, /*t2 = (R + r) / d,*/
    L1 = R * t1, H1 = R * sqrt(max(0.0, 1 - t1*t1)),
    // L2 = R * t2, H2 = R * sqrt(max(0.0, 1 - t2*t2)),
    l1 = L1 * k, h1 = H1 * k;
    // l2 = L2 * k, h2 = H2 * k;
    p /= d;

    vec
    o = {p.y, -p.x},
    P1 = a.p + p * L1,
    O1 = o * H1,
    p1 = b.p + p * l1,
    o1 = o * h1;
    s1 = {P1 + O1, p1 + o1};
    s2 = {P1 - O1, p1 - o1};
}

int n, m;
cir C0[NMAX + 10], C[NMAX + 10];
vec P[MMAX + 10];

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &C0[i].p.x, &C0[i].p.y, &C0[i].r);
    sort(C0 + 1, C0 + n + 1, [](const cir &a, const cir &b) {
        return a.r < b.r;
    });

    int n0 = 0;
    for (int i = 1; i <= n; i++) {
        bool ok = true;
        for (int j = i + 1; ok && j <= n; j++)
            ok &= (C0[i].p - C0[j].p).len() > (C0[j].r + C0[i].r - EPS);
        if (ok)
            C[++n0] = C0[i];
    }
    n = n0;
}

double cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

template <typename T>
bool eq(T x, T y) {
    return x - EPS < y && y < x + EPS;
}

int sp;
vec stk[MMAX + 10];

void convex() {
    int u = 1;
    for (int i = 2; i <= m; i++)
    if (P[i].x < P[u].x || (eq(P[i].x, P[u].x) && P[i].y < P[u].y))
        u = i;
    swap(P[1], P[u]);
    sort(P + 2, P + m + 1, [](const vec &a, const vec &b) {
        auto a0 = a - P[1];
        auto b0 = b - P[1];
        auto cr = cross(a0, b0);
        return (eq(cr, 0.0) && a0.len() < b0.len()) || cr > 0;
    });

    stk[sp = 1] = P[1];
    for (int i = 2; i <= m; i++) {
        while (sp > 1 && cross(P[i] - stk[sp - 1], stk[sp] - stk[sp - 1]) > -EPS)
            sp--;
        stk[++sp] = P[i];
    }
}

vector<int> buc[NMAX + 10];

double dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

double p2arc(double r, const vec &u, const vec &v) {
    if (eq(u.x, v.x) && eq(u.y, v.y))
        return 0;
    double d = dot(u, v);
    double cr = cross(u, v);
    double t = acos(max(-1.0, min(1.0, d / r / r)));  // avoid nan
    return cr > 0 ? t : 2 * M_PI - t;
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++) {
        seg s1, s2;
        tangent(C[j], C[i], s1, s2);
        P[++m] = s1.u;
        P[++m] = s1.v;
        P[++m] = s2.u;
        P[++m] = s2.v;
    }

    convex();

    for (int i = 1; i <= sp; i++)
    for (int j = 1; j <= n; j++)
    if (eq((C[j].p - stk[i]).len(), C[j].r)) {
        buc[j].push_back(i);
        break;
    }

    double ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j + 1 < buc[i].size(); j++)
        if (buc[i][j] + 1 == buc[i][j + 1]) {
            vec u = stk[buc[i][j]] - C[i].p;
            vec v = stk[buc[i][j + 1]] - C[i].p;
            double a = p2arc(C[i].r, u, v);
            ans = max(ans, a * C[i].r);
        }

        if (!buc[i].empty()) {
            int a = buc[i][0];
            int b = buc[i].back();
            if (a == 1 && b == sp) {
                vec u = stk[b] - C[i].p;
                vec v = stk[a] - C[i].p;
                double a = p2arc(C[i].r, u, v);
                ans = max(ans, a * C[i].r);
            }
        }
    }

    printf("%.12lf\n", ans);
    return 0;
}