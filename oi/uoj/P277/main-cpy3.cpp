#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define EPS 1e-8
#define INF 1e99

template <typename T>
inline bool eq(T x, decltype(x) y) {
    return abs(x - y) < EPS;
}

#define NMAX 500
#define MMAX 500000

struct vec {
    vec() : x(0), y(0) {}
    vec(double _x, double _y) : x(_x), y(_y) {}

    double x, y;

    double len() const {
        return hypot(x, y);
    }

    double len2() const {
        return x * x + y * y;
    }

    int region() const {
        if (x >= 0 && y >= 0) return 1;
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

    vec operator-() const {
        return {-x, -y};
    }

    vec operator*(double k) const {
        return {x * k, y * k};
    }

    vec &operator/=(double k) {
        x /= k;
        y /= k;
        return *this;
    }

    // unreliable: intended for unordered_map
    bool operator==(const vec &z) const {
        return x == z.x && y == z.y;
    }
};

namespace std {
template <>
struct hash<vec> {
    size_t operator()(const vec &v) const {
        static std::hash<double> H;
        return H(v.x) ^ H(v.y);
    }
};
}

double dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

double cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

struct cir {
    vec c;
    double r;
};

struct line {
    vec p, u;
};

struct seg {
    vec u, v;

    double len() const {
        return (u - v).len();
    }
};

enum TangentStatus {
    TPOINT = 1,
    TNORMAL = 2,
    TINNERT = 3,
    TCROSS = 4,
    TOUTERT = 5,
    TCONTAIN = 6
};

struct TangentResult {
    seg s[4];
    TangentStatus stat;
    bool swapped;
};

TangentResult tangent(cir a, cir b) {
    // assert: a.c != b.c
    bool swapped = false;
    if (a.r < b.r) {
        swap(a, b);
        swapped = true;
    }

    vec p = b.c - a.c;
    double R = a.r, r = b.r, d = p.len();
    TangentStatus stat;
    if (eq(r, 0))            stat = TPOINT;
    else if (R + r <= d - EPS) stat = TNORMAL;
    else if (eq(R + r, d))     stat = TINNERT;
    else if (d - EPS >= R - r) stat = TCROSS;
    else if (eq(R - r, d))     stat = TOUTERT;
    else                       stat = TCONTAIN;

    // branch out if optimization is needed.
    double
    k = r / R,
    t1 = (R - r) / d, t2 = (R + r) / d,
    L1 = R * t1, H1 = R * sqrt(max(0.0, 1 - t1 * t1)),
    L2 = R * t2, H2 = R * sqrt(max(0.0, 1 - t2 * t2)),
    l1 = L1 * k, h1 = H1 * k,
    l2 = L2 * k, h2 = H2 * k;

    p /= d;
    vec o = {p.y, -p.x};
    return {{
        {a.c + p * L1 + o * H1, b.c + p * l1 + o * h1},
        {a.c + p * L1 - o * H1, b.c + p * l1 - o * h1},
        {a.c + p * L2 + o * H2, b.c - p * l2 - o * h2},
        {a.c + p * L2 - o * H2, b.c - p * l2 + o * h2}
    }, stat, swapped};
}

double pldist(const vec &v, const line &l) {
    return abs(cross(v - l.p, l.u) / l.u.len());
}

double psdist(const vec &v, const seg &s) {
    vec p = s.v - s.u;
    if (dot(v - s.u, p) > -EPS &&
        dot(v - s.v, -p) > -EPS)
        return pldist(v, {s.u, p});
    return min((v - s.u).len(), (v - s.v).len());
}

double p2arc(const cir &c, const vec &p1, const vec &p2) {
    vec u = p1 - c.c;
    vec v = p2 - c.c;
    double d = dot(u, v);
    double cr = cross(u, v);
    double t = acos(d / c.r / c.r);
    return c.r * (cr > 0 ? t : 2 * M_PI - t);
}

bool no_intersect(const seg &s, const cir &c) {
    return psdist(c.c, s) > c.r - EPS;
}

struct Edge {
    int v;
    double w;
};

static vec sp, tp;
static int n, m;
static cir C[NMAX + 10];
static vector<vec> P[NMAX + 10];
static unordered_map<vec, int> id;
static vector<Edge> G[MMAX + 10];

int add(const vec &v) {
    auto it = id.find(v);
    if (it == id.end()) {
        id[v] = ++m;
        return m;
    } else
        return it->second;
}

void link(int u, int v, double w) {
    G[u].push_back({v, w});
    G[v].push_back({u, w});
}

void connect(const cir &c1, const cir &c2, int i, int j) {
    auto r = tangent(c1, c2);
    if (r.swapped)
        swap(i, j);

    int c;
    switch (r.stat) {
        case TPOINT: c = 2; break;
        case TNORMAL: c = 4; break;
        case TINNERT: c = 3; break;
        default: c = 0;
    }

    for (int k = 0; k < c; k++) {
        seg &s = r.s[k];
        bool ok = true;
        for (int p = 1; ok && p <= n; p++) if (p != i && p != j)
            ok &= no_intersect(s, C[p]);
        if (!ok) continue;

        int u = add(s.u), v = add(s.v);
        if (i) P[i].push_back(s.u);
        if (j) P[j].push_back(s.v);

        fprintf(stderr, "(%.4lf, %.4lf) - (%.4lf, %.4lf): %.4lf\n",
            s.u.x, s.u.y, s.v.x, s.v.y, s.len());
        link(u, v, s.len());
    }
}

double shortest(int s, int t) {
    static double dist[MMAX + 10];
    for (int i = 1; i <= m; i++)
        dist[i] = INF;
    dist[s] = 0;

    struct State {
        int u;
        double t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    priority_queue<State> q;
    q.push({s, 0});
    while (!q.empty()) {
        auto _ = q.top();
        q.pop();
        int u = _.u;
        if (_.t > dist[u])
            continue;

        for (auto &e : G[u]) {
            int v = e.v;
            if (dist[v] > dist[u] + e.w) {
                dist[v] = dist[u] + e.w;
                q.push({v, dist[v]});
            }
        }
    }

    return dist[t];
}

int main() {
    scanf("%lf%lf%lf%lf%d", &sp.x, &sp.y, &tp.x, &tp.y, &n);
    int s = add(sp);
    int t = add(tp);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &C[i].c.x, &C[i].c.y, &C[i].r);

    bool ok = true;
    for (int i = 1; ok && i <= n; i++)
        ok &= no_intersect({sp, tp}, C[i]);
    if (ok)
        link(s, t, (sp - tp).len());
    for (int i = 1; i <= n; i++) {
        connect({sp, 0}, C[i], 0, i);
        connect({tp, 0}, C[i], 0, i);
    }
    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
        connect(C[i], C[j], i, j);
    for (int i = 1; i <= n; i++) {
        sort(P[i].begin(), P[i].end(),
        [i](const vec &_u, const vec &_v) {
            vec u = _u - C[i].c;
            vec v = _v - C[i].c;
            int ui = u.region();
            int vi = v.region();
            return ui < vi ||
                (ui == vi && cross(u, v) > 0);
        });

        for (int j = 0; j < P[i].size(); j++) {
            int k = j + 1 < P[i].size() ? j + 1 : 0;
            vec &u = P[i][j], &v = P[i][k];
            double w = p2arc(C[i], u, v);

            fprintf(stderr, "(%.4lf, %.4lf) - (%.4lf, %.4lf): %.4lf\n",
                u.x, u.y, v.x, v.y, w);
            link(id[u], id[v], w);
        }
    }

    printf("%.1lf\n", shortest(s, t));
    return 0;
}

/*
int main() {
    cir a, b;
    while (
        scanf("%lf%lf%lf%lf%lf%lf",
        &a.c.x, &a.c.y, &a.r, &b.c.x, &b.c.y, &b.r) != EOF
    ) {
        auto ret = tangent(a, b);
        for (int i = 0; i < 4; i++) {
            auto &u = ret.s[i].u, &v = ret.s[i].v;
            printf("(%.4lf, %.4lf) - (%.4lf, %.4lf) [%d]\n",
                    u.x, u.y, v.x, v.y, ret.stat);
        }
    }
    return 0;
}
*/
