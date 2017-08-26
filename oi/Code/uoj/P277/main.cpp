#pragma GCC optimize(3)

#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 500
#define MMAX 1000000
#define EPS 1e-8
#define PI2 (M_PI * 2)

template <typename T1, typename T2>
inline bool equ(const T1 &a, const T2 &b) {
    return fabs(a - b) < EPS;
}

template <typename T>
inline T sqr(const T &x) {
    return x * x;
}

// 求解一元二次方程
inline void solvex2(
    double a, double b, double c,
    double &x1, double &x2
) {
    double d = sqrt(sqr(b) - 4 * a * c);
    x1 = (-b + d) / a * 0.5;
    // x2 = (-b - d) / a * 0.5;
    x2 = -b / a - x1;
}

struct Point {
    Point() : x(0), y(0) {}
    Point(double _x, double _y)
        : x(_x), y(_y) {}

    double x, y;

    bool operator==(const Point &b) const {
        return equ(x, b.x) && equ(y, b.y);
    }

    Point operator+(const Point &b) const {
        return Point(x + b.x, y + b.y);
    }

    Point operator-(const Point &b) const {
        return Point(x - b.x, y - b.y);
    }

    Point operator*(double b) const {
        return Point(x * b, y * b);
    }

    double operator*(const Point &b) const {
        return x * b.x + y * b.y;
    }

    double operator%(const Point &b) const {
        return x * b.y - y * b.x;
    }
};

Point p(double x, double y) {
    return Point(x, y);
}

// 两点之间距离
inline double dist(
    const Point &A,
    const Point &B
) {
    return hypot(A.x - B.x, A.y - B.y);
}

// 两点之间距离的平方
inline double dist2(
    const Point &A,
    const Point &B
) {
    return sqr(A.x - B.x) + sqr(A.y - B.y);
}

// 插值，A -> B
inline Point interp(
    const Point &A,
    const Point &B,
    double r
) {
    return A + (B - A) * r;
}

// 判断一个点是否在线段上，前提是在线段的直线上
inline bool onseg(
    const Point &A, const Point &B,
    const Point &C
) {
    return fmin(A.x, B.x) - EPS < C.x && C.x < fmax(A.x, B.x) + EPS &&
           fmin(A.y, B.y) - EPS < C.y && C.y < fmax(A.y, B.y) + EPS;
}

inline double dir(
    const Point &A, const Point &B,
    const Point &C
) {
    return (B - A) % (C - A);
}

// 点到直线距离
inline double pll(
    const Point &A,
    double a, double b, double c
) {
    return fabs(a * A.x + b * A.y + c) / hypot(a, b);
}

inline double pll2(
    const Point &A,
    double a, double b, double c
) {
    return sqr(a * A.x + b * A.y + c) / (sqr(a) + sqr(b));
}

// 判断线段是否有交点
inline bool seg2sect(
    const Point &A, const Point &B,
    const Point &C, const Point &D
) {
    double d1 = dir(A, B, C);
    double d2 = dir(A, B, D);
    double d3 = dir(C, D, A);
    double d4 = dir(C, D, B);
    return (d1 * d2 <= -EPS && d3 * d4 <= -EPS) ||
           (equ(d1, 0) && onseg(A, B, C)) ||
           (equ(d2, 0) && onseg(A, B, D)) ||
           (equ(d3, 0) && onseg(C, D, A)) ||
           (equ(d4, 0) && onseg(C, D, B));
}

// 判断线段和圆是否有交点
inline bool segarcsect(
    const Point &A, const Point &B,
    const Point &C, double r
) {
    double AB = dist2(A, B);
    double BC = dist2(B, C);
    double CA = dist2(C, A);
    if (AB + CA <= BC - EPS)
        return CA <= sqr(r) - EPS;
    else if (AB + BC <= CA - EPS)
        return BC <= sqr(r) - EPS;

    double dx = A.x - B.x;
    double dy = A.y - B.y;
    return pll2(C, dy, -dx, -dy * A.x + dx * A.y) <= sqr(r) - EPS;
}

// 圆弧上 A -> B 逆时针距离
inline double arcl(
    const Point &C, double r,
    const Point &A,
    const Point &B
) {
    double a = dist(A, B);
    double len = acos(1 - sqr(a / r) * 0.5) * r;
    return (A - C) % (B - C) > -EPS ? len : PI2 - len;
}

// 线圆交点
inline void larccr(
    double a, double b, double c,
    const Point &A, double r,
    Point &C, Point &D
) {
    if (equ(b, 0)) {
        C.x = D.x = -c / a;

        solvex2(
            1, -2 * A.y, sqr(A.y) + sqr(C.x - A.x) - sqr(r),
            C.y, D.y
        );
    } else {
        double k = -a / b;
        double d = -c / b;
        double e = d - A.y;

        solvex2(
            1 + sqr(k), 2 * (k * e - A.x), sqr(A.x) + sqr(e) - sqr(r),
            C.x, D.x
        );
        C.y = k * C.x + d;
        D.y = k * D.x + d;
    }
}

// 圆圆交点
inline void arc2cr(
    const Point &A, double r1,
    const Point &B, double r2,
    Point &C, Point &D
) {
    double a = 2 * (B.x - A.x);
    double b = 2 * (B.y - A.y);
    double c = sqr(r2) - sqr(r1) + sqr(A.x) - sqr(B.x) + sqr(A.y) - sqr(B.y);
    larccr(a, b, c, A, r1, C, D);
}

// 点圆切线
inline void parctan(
    const Point &A,
    const Point &B, double r,
    Point &C, Point &D
) {
    arc2cr(B, r, (A + B) * 0.5, dist(A, B) * 0.5, C, D);
}

// 内公切线
inline void arc2tan1(
    const Point &A, double r1,
    const Point &B, double r2,
    Point &C, Point &D, Point &E, Point &F
) {
    Point M = interp(A, B, r1 / (r1 + r2));
    parctan(M, A, r1, C, E);
    parctan(M, B, r2, D, F);

    if (!seg2sect(C, D, E, F))
        swap(D, F);
}

// 外公切线
inline void arc2tan2(
    Point A, double r1,
    Point B, double r2,
    Point &C, Point &D, Point &E, Point &F
) {
    if (equ(r1, r2)) {
        double dx = A.x - B.x;
        double dy = A.y - B.y;
        larccr(dx, dy, -dx * A.x - dy * A.y, A, r1, C, E);
        larccr(dx, dy, -dx * B.x - dy * B.y, B, r1, D, F);
    } else {
        if (r1 < r2) {
            swap(A, B);
            swap(r1, r2);
        }

        double l = dist(A, B);
        double x = r2 * l / (r1 - r2);
        Point M = interp(A, B, (l + x) / l);
        parctan(M, A, r1, C, E);
        parctan(M, B, r2, D, F);
    }

    if (seg2sect(C, D, E, F))
        swap(D, F);
}

static int n, m;
static Point S, T;
static Point C[NMAX + 10];
static double R[NMAX + 10];
static vector<int> arc[NMAX + 10];
static Point P[MMAX + 10];

struct Edge {
    Edge(int _v, double _w)
        : v(_v), w(_w) {}

    int v;
    double w;
};

static vector<Edge> G[MMAX + 10];

void initialize() {
    scanf("%lf%lf%lf%lf%d", &S.x, &S.y, &T.x, &T.y, &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &C[i].x, &C[i].y, R + i);
    }
}

inline bool valid(const Point &A, const Point &B, int x, int y) {
    for (int i = 1; i <= n; i++) {
        if (i == x || i == y)
            continue;
        if (segarcsect(A, B, C[i], R[i]))
            return false;
    }

    return true;
}

inline void addseg(int i, int j, const Point &A, const Point &B) {
    if (!valid(A, B, i, j))
        return;

    if (!equ(R[i], dist(C[i], A)))
        swap(i, j);

    P[++m] = A;
    P[++m] = B;
    arc[i].push_back(m - 1);
    arc[j].push_back(m);

    double w = dist(A, B);
    G[m - 1].push_back(Edge(m, w));
    G[m].push_back(Edge(m - 1, w));
}

inline void linkseg(int i, int j, const Point &A, const Point &B) {
    if (!valid(A, B, i, 0))
        return;

    P[++m] = A;
    arc[i].push_back(m);

    double w = dist(A, B);
    G[m].push_back(Edge(j, w));
    G[j].push_back(Edge(m, w));
}

inline int idx(const Point &A) {
    if (A.x >= 0 && A.y >= 0)
        return 1;
    if (A.x >= 0 && A.y <= 0)
        return 2;
    if (A.x <= 0 && A.y <= 0)
        return 3;
    return 4;
}

void construct() {
    if (valid(S, T, 0, 0)) {
        double w = dist(S, T);
        G[1].push_back(Edge(2, w));
        G[2].push_back(Edge(1, w));
    }

    m = 2;
    Point A1, B1, A2, B2;
    for (int i = 1; i <= n; i++) {
        parctan(S, C[i], R[i], A1, A2);
        linkseg(i, 1, A1, S);
        linkseg(i, 1, A2, S);
        parctan(T, C[i], R[i], A1, A2);
        linkseg(i, 2, A1, T);
        linkseg(i, 2, A2, T);

        for (int j = i + 1; j <= n; j++) {
            arc2tan1(C[i], R[i], C[j], R[j], A1, B1, A2, B2);
            addseg(i, j, A1, B1);
            addseg(i, j, A2, B2);
            arc2tan2(C[i], R[i], C[j], R[j], A1, B1, A2, B2);
            addseg(i, j, A1, B1);
            addseg(i, j, A2, B2);
        }
    }

    for (int i = 1; i <= n; i++) {
        sort(arc[i].begin(), arc[i].end(),
             [i](int x, int y) {
                 Point A = P[x] - C[i], B = P[y] - C[i];
                 if (idx(A) == idx(B))
                     return A % B <= -EPS;
                 return idx(A) < idx(B);
             });
        
        for (size_t j = 0; j < arc[i].size(); j++) {
            int u = arc[i][j], v = arc[i][(j + 1) % arc[i].size()];
            double w = arcl(C[i], R[i], P[v], P[u]);
            G[u].push_back(Edge(v, w));
            G[v].push_back(Edge(u, w));
        }
    }
}

struct State {
    State(int _u, double _d)
        : x(_u), d(_d) {}

    int x;
    double d;

    bool operator<(const State &b) const {
        return d > b.d;
    }
};

static double dis[MMAX + 10];

void dijkstra() {
    for (int i = 2; i <= m; i++) {
        dis[i] = 1e100;
    }

    priority_queue<State> q;
    q.push(State(1, 0));
    while (!q.empty()) {
        State u = q.top();
        q.pop();

        if (u.d > dis[u.x])
            continue;
        
        for (auto &e : G[u.x]) {
            int v = e.v;

            if (dis[v] > dis[u.x] + e.w) {
                dis[v] = dis[u.x] + e.w;
                q.push(State(v, dis[v]));
            }
        }
    }
}

int main() {
    initialize();
    construct();
    dijkstra();
    printf("%.1lf\n", dis[2]);

    return 0;
}
