#pragma GCC optimize(3)

#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>

#include <random>
#include <algorithm>

using namespace std;

using d8 = double;

constexpr int NMAX = 500;
constexpr d8 EPS0 = 1e-10;
constexpr d8 EPS = 1e-9;
constexpr d8 INF = 1e99;

bool eq(d8 x, d8 y) {
    return fabsl(x - y) < EPS;
}

static random_device rd;
static mt19937 gen(rd());

struct vec {
    d8 x, y, z;

    d8 norm2() const {
        return x * x + y * y + z * z;
    }

    d8 norm() const {
        return sqrt(norm2());
    }

    void randmov() {
        static uniform_real_distribution<d8> dist(-EPS0, EPS0);
        x += dist(gen);
        y += dist(gen);
        z += dist(gen);
    }

    vec unit() const {
        return (*this) / norm();
    }

    vec operator+(const vec &w) const {
        return {x + w.x, y + w.y, z + w.z};
    }

    vec operator-(const vec &w) const {
        return {x - w.x, y - w.y, z - w.z};
    }

    vec operator*(d8 k) const {
        return {x * k, y * k, z * k};
    }

    vec operator/(d8 k) const {
        return {x / k, y / k, z / k};
    }

    d8 operator*(const vec &w) const {
        return x * w.x + y * w.y + z * w.z;
    }

    vec operator%(const vec &w) {
        return {
            y * w.z - z * w.y,
            -x * w.z + z * w.x,
            x * w.y - y * w.x
        };
    }
};

int m;
int s[NMAX + 10];
vec p[NMAX + 10];
d8 ans = -INF;
d8 mi[2], mx[2];

d8 _eval(vec n) {
    n = n.unit();
    if (!isfinite(n.x))
        return -INF;

    mi[0] = mi[1] = INF;
    mx[0] = mx[1] = -INF;
    for (int i = 1; i <= m; i++) {
        d8 t = p[i] * n;
        int a = s[i], b = a ^ 1;

        // NOTE: crucial to performance!
        if (mi[b] - EPS < t && t < mx[b] + EPS)
            return -INF;

        mi[a] = min(mi[a], t);
        mx[a] = max(mx[a], t);
    }

    if ((mi[0] - EPS < mi[1] && mi[1] < mx[0] + EPS) ||
        (mi[0] - EPS < mx[1] && mx[1] < mx[0] + EPS) ||
        (mi[1] - EPS < mi[0] && mi[0] < mx[1] + EPS) ||
        (mi[1] - EPS < mx[0] && mx[0] < mx[1] + EPS))
        return -INF;

    if (mx[0] <= mi[1] + EPS)
        return mi[1] - mx[0];
    return mi[0] - mx[1];
}

void eval(vec n) {
    ans = max(ans, _eval(n));
}

struct Face {
    vec a, b, c;
};

struct Edge {
    vec a, b;
};

struct ConvexHull {
    ConvexHull() : n(0) {
        memset(off, 0, sizeof(off));
    }

    int n;
    vec P[NMAX + 10];
    int idx[NMAX + 10];
    bool off[NMAX + 10][NMAX + 10];

    vector<Face> fs;
    vector<Edge> es;

    void initialize(int &u, int &v) {
        fs.reserve(2 * NMAX);
        es.reserve(10 * NMAX);

        u = 0;
        for (int i = 1; i < n; i++) {
            if ((eq(P[i].x, P[u].x) && P[i].y < P[u].y)||
                (P[i].x < P[u].x))
                u = i;
        }

        swap(P[0], P[u]);
        swap(idx[0], idx[u]);
        u = 0;
        v = 1;
        for (int i = 2; i < n; i++) {
            vec dv = P[v] - P[0];
            vec di = P[i] - P[0];
            d8 c = di.x * dv.y - di.y * dv.x;
            if (c >= EPS)
                v = i;
        }
    }

    void wrap(int i, int j) {
        if (off[i][j])
            return;
        vec v = P[j] - P[i];
        int k = -1;
        for (int p = 0; p < n; p++)
        if (p != i && p != j) {
            if (k == -1 || ((P[p] - P[i]) % (P[k] - P[i])) * v >= EPS)
                k = p;
        }

        // NOTE: it's possible when n < 4.
        if (k < 0)
            return;

        fs.push_back({p[idx[i]], p[idx[k]], p[idx[j]]});
        off[i][j] = off[k][i] = off[j][k] = true;
        wrap(i, k);
        wrap(k, j);
    }

    void construct_edges() {
        // NOTE: be careful when n < 4.
        if (n <= 3) {
            for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                es.push_back({p[idx[i]], p[idx[j]]});
            }
        } else {
            for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            if (off[i][j] || off[j][i]) {
                es.push_back({p[idx[i]], p[idx[j]]});
            }
        }

        //shuffle(es.begin(), es.end(), gen);
        //shuffle(fs.begin(), fs.end(), gen);

        fprintf(stderr, "fs=%zu, es=%zu\n", fs.size(), es.size());
    }
};

ConvexHull con[2];

void try_edge(vec a, vec b, int k) {
    vec u = (b - a).unit();
    for (int i = 1; i <= m; i++)
    if (s[i] != k) {
        vec v = p[i] - a;
        d8 l = u * v;
        vec o = a + u * l;
        eval(p[i] - o);
    }
}

void try_twin(vec a, vec b, vec c, vec d) {
    eval((a - b) % (c - d));
}

int main() {
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%lf%lf%lf%d", &p[i].x, &p[i].y, &p[i].z, s + i);
        s[i]--;

        int j = con[s[i]].n++;
        con[s[i]].P[j] = p[i];
        con[s[i]].idx[j] = i;
    }

    for (int k = 0; k < 2; k++) {
        int u, v;

        // NOTE: DO NOT purturb original points to prevent potential precision loss.
        for (int i = 0; i < con[k].n; i++) {
            con[k].P[i].randmov();
        }

        con[k].initialize(u, v);
        con[k].wrap(u, v);
        con[k].construct_edges();
    }

    for (int i = 1; i <= m; i++)
    for (int j = i + 1; j <= m; j++)
    if (s[i] != s[j]) {
        vec n = p[i] - p[j];
        eval(n);
    }

    for (int k = 0; k < 2; k++) {
        for (auto &f : con[k].fs) {
            vec n = (f.b - f.a) % (f.c - f.a);
            eval(n);
        }

        for (auto &e : con[k].es) {
            try_edge(e.a, e.b, k);
        }
    }

    for (auto &e1 : con[0].es)
    for (auto &e2 : con[1].es) {
        try_twin(e1.a, e1.b, e2.a, e2.b);
    }

    if (ans < -10 * EPS)
        puts("-1");
    else
        printf("%.15lf\n", ans);

    return 0;
}
