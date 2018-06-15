#pragma GCC optimize(3)

#include <cmath>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100

// Union-Find DS
static int *_fa;
static stack<int *> _stk;

inline void setup() {
    _fa = new int[NMAX + 10];
    memset(_fa, 0, sizeof(int) * (NMAX + 10));
}

inline void push() {
    _stk.push(_fa);
    _fa = new int[NMAX + 10];
    memcpy(_fa, _stk.top(), sizeof(int) * (NMAX + 10));
}

inline void pop() {
    delete[] _fa;
    _fa = _stk.top();
    _stk.pop();
}

inline int id(int x) {
    return _fa[x] ? _fa[x] = id(_fa[x]) : x;
}

inline int idl(int x) {
    int *fa = _stk.top();
    return fa[x] ? fa[x] = idl(fa[x]) : x;
}

inline void set(int x, int y) {
    _fa[x] = y;
}

struct Edge {
    Edge(int _u, int _v, double _w) : u(_u), v(_v), w(_w) {}

    int u, v;
    double w;
};

static int n, m;
static double X[NMAX + 10], Y[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

inline double dist(int i, int j) {
    return hypot(X[i] - X[j], Y[i] - Y[j]);
}

void initialize() {
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", X + i, Y + i);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u == v) continue;
        G[u].push_back(new Edge(u, v, dist(u, v)));
    }
}

void finalize() {
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < G[u].size(); i++)
            delete G[u][i];
        G[u].clear();
    }

    memset(_fa, 0, sizeof(int) * (NMAX + 10));
}

#define rep(u) for (size_t i = 0; i < G[u].size(); i++)
#define ok(u, v) (id(u) != id(v))
#define nxt(x) id(in[x]->u)

static Edge *in[NMAX + 10];
static int mark[NMAX + 10];

int cycle() {
    memset(mark, 0, sizeof(mark));
    for (int u = 2; u <= n; u++) {
        int x = id(u);
        if (mark[x]) continue;

        mark[x] = u;
        while (in[x]) {
            x = nxt(x);
            if (mark[x] == u) return x;
            if (mark[x]) break;
            mark[x] = u;
        }
    }

    return 0;
}

void _mdst() {
    memset(in, 0, sizeof(in));
    for (int u = 1; u <= n; u++) rep(u) {
        Edge *e = G[u][i];
        int v = id(e->v);
        if (v > 1 && id(u) != v && (!in[v] || e->w < in[v]->w))
            in[v] = e;
    }

    int x = cycle();
    if (!x) return;

    push();
    vector<Edge *> cyc;
    cyc.push_back(in[x]);
    for (int y = nxt(x); y != x; y = nxt(y)) {
        cyc.push_back(in[y]);
        set(y, x);
    }
    for (int u = 1; u <= n; u++) rep(u) {
        Edge *e = G[u][i];
        int v = e->v;
        if (id(u) != x && id(v) == x) e->w -= in[idl(v)]->w;
    }

    _mdst();
    pop();

    Edge *ie = in[x];
    int t = id(ie->v);
    for (size_t i = 0; i < cyc.size(); i++) {
        Edge *e = cyc[i];
        x = id(e->v);
        if (x == t) in[x] = ie;
        else in[x] = e;
    }
}

int dfs(int x) {
    mark[x] = 1;
    int ret = 1;
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->v;
        if (!mark[v]) ret += dfs(v);
    }

    return ret;
}

// root: 1
double mdst() {
    memset(mark, 0, sizeof(mark));
    if (dfs(1) < n) return -1;

    _mdst();

    double ret = 0.0;
    for (int u = 2; u <= n; u++)
        ret += dist(u, in[u]->u);
    return ret;
}

int main() {
    setup();
    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();

        double ans = mdst();
        if (ans < 0) puts("poor snoopy");
        else printf("%.2f\n", ans);

        finalize();
    }

    return 0;
}
