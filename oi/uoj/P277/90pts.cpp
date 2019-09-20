//#define NDEBUG

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#include <chrono>
inline double tick() {
    using namespace std::chrono;
    typedef high_resolution_clock clock;
    static clock::time_point tm;
    static bool cur;
    if (cur) {
        cur = 0;
        return duration<double>(clock::now() - tm).count();
    } else tm = clock::now(), cur = 1;
    return 0;
}

#define NMAX 500
#define MMAX 1000000
#define INF 1e99

typedef double ld;

#define EPS 1e-8
inline bool eq(ld x, ld y) {
    return x - EPS < y && y < x + EPS;
}

inline ld sqrt_s(ld x) {
    return sqrt(max(0.0, x));
}

struct vec {
    vec() : x(0), y(0) {}
    vec(ld _x, ld _y) : x(_x), y(_y) {}

    ld x, y;

    ld len() const {
        return hypot(x, y);
    }

    ld len2() const {
        return x * x + y * y;
    }

    vec norm() const {
        ld l = len();
        return vec(x / l, y / l);
    }

    vec cw() const {
        return vec(y, -x);
    }

    vec cw(ld t) const {
        ld c = cos(t), s = sin(t);
        return vec(-c * x + s * y, -s * x - c * y);
    }

    vec ccw() const {
        return vec(-y, x);
    }

    vec ccw(ld t) const {
        ld c = cos(t), s = sin(t);
        return vec(c * x - s * y, s * x + c * y);
    }

    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }

    vec operator-() const {
        return vec(-x, -y);
    }

    friend vec operator*(ld k, const vec &z);
    vec operator*(ld k) const {
        return vec(x * k, y * k);
    }

    vec operator/(ld k) const {
        return vec(x / k, y / k);
    }

    vec &operator+=(const vec &z) {
        x += z.x;
        y += z.y;
        return *this;
    }

    vec &operator-=(const vec &z) {
        x -= z.x;
        y -= z.y;
        return *this;
    }

    vec &operator*=(ld k) {
        x *= k;
        y *= k;
        return *this;
    }

    bool operator==(const vec &z) const {
        return x - EPS < z.x && z.x < x + EPS &&
               y - EPS < z.y && z.y < y + EPS;
    }

    bool operator!=(const vec &z) const {
        return x - EPS >= z.x || z.x >= x + EPS ||
               y - EPS >= z.y || z.y >= y + EPS;
    }
};

inline vec operator*(ld k, const vec &z) {
    return vec(z.x * k, z.y * k);
}

inline ld dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

inline ld cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

struct seg {
    seg() {}
    seg(const vec &_u, const vec &_v) : u(_u), v(_v) {}

    vec u, v;

    ld len() const {
        return (u - v).len();
    }

    ld len2() const {
        return (u - v).len2();
    }

    bool operator==(const seg &z) const {
        return (u == z.u && v == z.v) ||
               (u == z.v && v == z.u);
    }

    bool operator!=(const seg &z) const {
        return (u != z.u || v != z.v) &&
               (u != z.v || v != z.u);
    }
};

inline ld dist(const vec &u, const seg &s) {
    vec dv = s.v - s.u;
    ld c = dot(u - s.u, dv);
    if (c > -EPS && dot(u - s.v, dv) < EPS) {
        ld d = c / dv.len();
        return sqrt_s((u - s.u).len2() - d * d);
    } else return min((u - s.u).len(), (u - s.v).len());
}

struct cir {
    cir() {}
    cir(const vec &_p, ld _r) : p(_p), r(_r) {}

    vec p;
    ld r;

    ld arcl(vec u, vec v) {
        u -= p; v -= p;
        assert(u.len() < r + EPS);
        assert(v.len() < r + EPS);
        ld c = dot(u, v) / u.len() / v.len();
        if (c > 1) c = 1;
        if (c < -1) c = -1;
        ld t = acos(c);
        if (cross(u, v) <= -EPS) t = 2 * M_PI - t;
        return t * r;
    }

    bool operator==(const cir &z) const {
        return p == z.p && r - EPS < z.r && z.r < r + EPS;
    }

    bool operator!=(const cir &z) const {
        return p != z.p || r - EPS >= z.r || z.r >= r + EPS;
    }
};

inline bool pass(const seg &s, const cir &c) {
    return dist(c.p, s) <= c.r - EPS;
}

// 点与圆的切点
inline void pctan(const vec &p, const cir &c, vec &t1, vec &t2) {
    ld d = (p - c.p).len();
    ld l = sqrt_s(d * d - c.r * c.r);
    ld h = c.r * l / d, s = c.r * c.r / d;
    vec u = c.p + (p - c.p).norm() * s, v = (p - c.p).cw().norm() * h;
    t1 = u + v; t2 = u - v;
}

// 外公切线
inline void c2tan1(const cir &c1, const cir &c2, seg &t1, seg &t2) {
    ld dr = abs(c1.r - c2.r), d = (c1.p - c2.p).len();
    ld l = sqrt_s(d * d - dr * dr);
    ld h1 = l * c1.r / d, s1 = dr * c1.r / d;
    ld h2 = l * c2.r / d, s2 = dr * c2.r / d;
    vec v = (c1.r > c2.r ? c2.p - c1.p : c1.p - c2.p).norm();
    vec u = v.cw(), p1 = c1.p + v * s1, p2 = c2.p + v * s2;
    t1 = seg(p1 + u * h1, p2 + u * h2);
    t2 = seg(p1 - u * h1, p2 - u * h2);
}

// 内公切线
inline void c2tan2(const cir &c1, const cir &c2, seg &t1, seg &t2) {
    ld d = (c1.p - c2.p).len();
    ld d1 = d * c1.r / (c1.r + c2.r), d2 = d * c2.r / (c1.r + c2.r);
    ld l1 = sqrt_s(d1 * d1 - c1.r * c1.r), l2 = sqrt_s(d2 * d2 - c2.r * c2.r);
    ld h1 = c1.r * l1 / d1, h2 = c2.r * l2 / d2;
    ld s1 = c1.r * c1.r / d1, s2 = c2.r * c2.r / d2;
    vec v = (c1.p - c2.p).norm(), u = v.cw();
    vec p1 = c1.p - v * s1, p2 = c2.p + v * s2;
    t1 = seg(p1 + u * h1, p2 - u * h2);
    t2 = seg(p1 - u * h1, p2 + u * h2);
}

struct Edge {
    int v;
    ld w;
};

static int n, m;
static cir C[NMAX + 10];
static vector<int> cyc[NMAX + 10];
static vec P[MMAX + 10];
static vector<Edge> G[MMAX + 10];

inline bool valid(const seg &s, int j = 0, int k = 0) {
    if (s.u == s.v) return false;
    for (int i = 1; i <= n; i++)
        if (i != j && i != k && pass(s, C[i])) return false;
    return true;
}

inline void link(int u, const vec &v) {
    ld w = (P[u] - v).len();
    G[u].push_back({m + 1, w});
    G[m + 1].push_back({u, w});
    P[++m] = v;
#ifndef NDEBUG
    fprintf(stderr, "a[%d](%.3lf, %.3lf) ⇔ [%d](%.3lf, %.3lf) [%.2lf]\n",
            u, P[u].x, P[u].y, m, v.x, v.y, w);
#endif
}

inline void link(const seg &s, int i, int j) {
    if (!valid(s, i, j)) return;
    ld w = s.len();
    cyc[i].push_back(m + 1);
    cyc[j].push_back(m + 2);
    G[m + 1].push_back({m + 2, w});
    G[m + 2].push_back({m + 1, w});
    P[++m] = s.u;
    P[++m] = s.v;
#ifndef NDEBUG
    fprintf(stderr, "b[%d](%.3lf, %.3lf) ⇔ [%d](%.3lf, %.3lf) [%.2lf]\n",
            m - 1, s.u.x, s.u.y, m, s.v.x, s.v.y, w);
#endif
}

inline void link(int u, int v, ld w) {
    G[u].push_back({v, w});
    G[v].push_back({u, w});
#ifndef NDEBUG
    fprintf(stderr, "c[%d](%.3lf, %.3lf) ⇔ [%d](%.3lf, %.3lf) [%.2lf]\n",
            u, P[u].x, P[u].y, v, P[v].x, P[v].y, w);
#endif
}

inline int idx(const vec &A) {
    if (A.x >= 0 && A.y >= 0)
        return 1;
    if (A.x >= 0 && A.y <= 0)
        return 2;
    if (A.x <= 0 && A.y <= 0)
        return 3;
    return 4;
}

inline void setup() {
    m = 2;
    if (valid({P[1], P[2]})) link(1, 2, (P[1] - P[2]).len());
    for (int i = 1; i <= 2; i++) for (int j = 1; j <= n; j++) if (C[j].r > EPS) {
        if (eq((P[i] - C[j].p).len(), C[j].r)) cyc[j].push_back(i);
        else {
            vec p1, p2;
            pctan(P[i], C[j], p1, p2);
            if (valid({P[i], p1}, j)) {
                link(i, p1);
                cyc[j].push_back(m);
            }
            if (valid({P[i], p2}, j)) {
                link(i, p2);
                cyc[j].push_back(m);
            }
        }
    }

    for (int i = 1; i <= n; i++) if (C[i].r > EPS)
    for (int j = i + 1; j <= n; j++) if (C[j].r > EPS) {
        seg s1, s2;
        c2tan1(C[i], C[j], s1, s2);
        link(s1, i, j);
        link(s2, i, j);
        if (eq((C[i].p - C[j].p).len(), C[i].r + C[j].r)) {
            vec p = C[j].p + (C[i].p - C[j].p) * C[j].r / (C[i].r + C[j].r);
            P[++m] = p;
            cyc[i].push_back(m);
            cyc[j].push_back(m);
        } else if ((C[i].p - C[j].p).len() > C[i].r + C[j].r) {
            c2tan2(C[i], C[j], s1, s2);
            link(s1, i, j);
            link(s2, i, j);
        }
    }

    for (int i = 1; i <= n; i++) {
        //fprintf(stderr, "i = %d\n", i);
        sort(cyc[i].begin(), cyc[i].end(),
             [i](int x, int y) {
                 vec A = P[x] - C[i].p, B = P[y] - C[i].p;
                 if (idx(A) == idx(B))
                     return cross(A, B) >= EPS;
                 return idx(A) > idx(B);
             });
        for (int j = 0; j < cyc[i].size(); j++) {
            int u = cyc[i][j], v = cyc[i][(j + 1) % cyc[i].size()];
            link(u, v, C[i].arcl(P[u], P[v]));
        }
    }
}

static ld D[MMAX + 10];

inline void shortest() {
    struct State {
        int u;
        ld s;
        bool operator<(const State &z) const {
            return s > z.s;
        }
    };
    queue<State> q;
    for (int i = 2; i <= m; i++) D[i] = INF;
    q.push({1, 0});
    while (!q.empty()) {
        auto s = q.front();
        q.pop();
        if (s.s > D[s.u]) continue;
        for (auto &e : G[s.u]) {
            if (D[e.v] > s.s + e.w) {
                D[e.v] = s.s + e.w;
                q.push({e.v, D[e.v]});
            }
        }
    }
}

int main() {
    scanf("%lf%lf%lf%lf%d", &P[1].x, &P[1].y, &P[2].x, &P[2].y, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &C[i].p.x, &C[i].p.y, &C[i].r);

    tick();
    setup();
    auto t = tick();
    fprintf(stderr, "time = %.2lf\n", t);
    shortest();
    printf("%.1lf\n", D[2]);

#ifndef NDEBUG
    for (int i = 3; i <= m; i++)
        fprintf(stderr, "P_{%d}=(%.6lf,%.6lf)\n", i, P[i].x, P[i].y);
#endif
    return 0;
}
