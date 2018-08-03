#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 200
#define INF 1e9
#define EPS 1e-9

inline bool eq(double x, double y) {
    return x - EPS < y && y < x + EPS;
}

struct Point {
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}

    int id;
    double x, y;

    Point operator+(const Point &v) const {
        return {x + v.x, y + v.y};
    }

    Point operator-(const Point &v) const {
        return {x - v.x, y - v.y};
    }

    Point operator*(double v) const {
        return {x * v, y * v};
    }

    Point operator/(double v) const {
        return {x / v, y / v};
    }

    Point operator*() const {
        return {y, -x};
    }
};

struct Circle {
    double x, y, r;

    bool operator<(const Circle &z) const {
        return r < z.r;
    }
};

inline double dot(const Point &u, const Point &v) {
    return u.x * v.x + u.y * v.y;
}

inline double cross(const Point &u, const Point &v) {
    return u.x * v.y - u.y * v.x;
}

inline double len(const Point &u) {
    return hypot(u.x, u.y);
}

inline Point nor(const Point &u) {
    return u / len(u);
}

static int n, m;
static Circle C[NMAX + 10];
static Point P[4 * NMAX * NMAX + 10];

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &C[i].x, &C[i].y, &C[i].r);
        C[i].r += 10;
    }
}

void filter() {
    sort(C + 1, C + n + 1);
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (C[i].r - C[j].r > hypot(C[i].x - C[j].x, C[i].y - C[j].y) - EPS)
                C[j].r = INF;
        }
    }

    int i = 0;
    for (int j = 1; j <= n; j++) {
        if (C[j].r < INF - EPS)
            C[++i] = C[j];
        // else printf("Circle (%.2lf, %.2lf) removed.\n", C[j].x, C[j].y);
    }
    n = i;
}

void setup() {
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
        Point p = Point(C[i].x, C[i].y), q = Point(C[j].x, C[j].y);
        Point d = q - p, u = nor(*d), v;

        double R1 = C[i].r, R2 = C[j].r;
        if (eq(R1, R2)) {
            P[++m] = p + u * R1;
            P[++m] = p - u * R1;
            P[m].id = P[m - 1].id = i;
            P[++m] = q + u * R2;
            P[++m] = q - u * R2;
            P[m].id = P[m - 1].id = j;
        } else {
            Point c;
            if (R1 > R2) c = p + d / (R1 - R2) * R1;
            else c = q - d / (R2 - R1) * R2;

#define CALC(p, r, i) \
            l = len(p - c); \
            x = sqrt(l * l - r * r); \
            h = x / l * r; \
            v = p + nor(c - p) * sqrt(r * r - h * h); \
            P[++m] = v + u * h; \
            P[++m] = v - u * h; \
            P[m].id = P[m - 1].id = i;

            double h, l, x;
            CALC(p, R1, i);
            CALC(q, R2, j);
        }
    }
}

inline double arc(const Point &u, const Point &v) {
    if (u.id == v.id) {
        Point p(C[u.id].x, C[u.id].y);
        double r = C[u.id].r;
        double l = len(u - v), t = asin(l / 2 / r);
        if (cross(v - u, p - u) > -EPS) t = M_PI - t;
        return 2 * t * r;
    } else return len(u - v);
}

static int t;
static Point seq[4 * NMAX * NMAX + 10];

double eval() {
    int p = 1;
    for (int i = 2; i <= m; i++)
        if ((eq(P[i].x, P[p].x) && P[i].y < P[p].y) ||
            (!eq(P[i].x, P[p].x) && P[i].x < P[p].x))
            p = i;
    // printf("%.2lf, %.2lf\n", P[p].x, P[p].y);
    swap(P[1], P[p]);
    Point loc = P[1];
    sort(P + 2, P + m + 1, [loc](const Point &u, const Point &v) {
        Point pu = u - loc, pv = v - loc;
        double val = cross(pu, pv);
        if (eq(val, 0)) return len(pu) < len(pv);
        return val > 0;
    });

    deque<Point> q;
    for (int i = 1; i <= m; i++) {
        Point u = P[i];
        while (q.size() > 1 && cross(u - q[1], q[0] - q[1]) > -EPS)
            q.pop_front();
        q.push_front(u);
    }

    // for (auto p : q)
    //     printf("%d: %.2lf, %.2lf\n", p.id, p.x, p.y);

    for (int i = 0; i < q.size(); i++) {
        int k = q[i].id;
        bool fucked = false;
        for (int j = 1; !fucked && j <= n; j++) {
            if (j == k) continue;
            if (len(q[i] - Point(C[j].x, C[j].y)) < C[j].r + EPS)
                fucked = true;
        }
        if (!fucked) seq[t++] = q[i];
    }

    // for (int i = 0; i < t; i++)
    //     printf("%d: %.2lf, %.2lf\n", seq[i].id, seq[i].x, seq[i].y);

    double ret = arc(seq[t - 1], seq[0]);
    // printf("%.10lf\n", arc(seq[t - 1], seq[0]));
    for (int i = 0; i < t - 1; i++) {
        ret += arc(seq[i], seq[i + 1]);
        // printf("%.10lf\n", arc(seq[i], seq[i + 1]));
    }
    return ret;
}

int main() {
    initialize();
    filter();
    if (n == 1) printf("%.9lf\n", 2 * M_PI * C[1].r);
    else {
        setup();
        printf("%.9lf\n", eval());
    }

    return 0;
}
