#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 300
#define MMAX 500
#define EPS 1e-9

inline bool equ(double a, double b) {
    return fabs(a - b) < EPS;
}

struct Edge {
    Edge(int _u, int _v, int _id, int _d, double _r)
            : u(_u), v(_v), id(_id), dir(_d), r(_r) {}

    int u, v, id, dir;
    double r;
};

static int n, m;
static vector<Edge *> G[NMAX + 10];
static double A[MMAX + NMAX + 10][MMAX + 10];
static int dep[NMAX + 10];
static Edge *edge[NMAX + 10];

// TODO:
//   1. Guassian elimination
//   2. Operation on the DFS tree

void dfs(int u, int f = 0) {
    static int cnt = n - 1;

    for (auto &e : G[u]) {
        int v = e->v;

        if (v == f)
            continue;

        if (dep[v] && dep[v] < dep[u]) {
            A[++cnt][e->id] = e->dir * e->r;
            for (int x = u; x != v; x = edge[x]->u) {
                A[cnt][edge[x]->id] = edge[x]->dir * edge[x]->r;
            }  // for
        } else if (!dep[v]) {
            dep[v] = dep[u] + 1;
            edge[v] = e;
            dfs(v, u);
        }
    }  // foreach in G[u]
}

void guass() {
    int c = n + m - 1;
    for (int i = 1; i < m; i++) {
        int p = i;
        for (int j = i + 1; j <= m; j++) {
            if (fabs(A[j][i]) > fabs(A[p][i]))
                p = j;
        }  // for

        if (p != i) {
            for (int j = i; j <= c; j++) {
                swap(A[p][j], A[i][j]);
            }  // for
        }

        for (int j = i + 1; j <= m; j++) {
            double r = A[j][i] / A[i][i];
            for (int k = i; k <= c; k++) {
                A[j][k] -= A[i][k] * r;
            }  // for
        }      // for
    }          // for

    for (int i = m; i >= 1; i--) {
        for (int j = m + 1; j <= c; j++) {
            A[i][j] /= A[i][i];
        }  // for

        for (int j = 1; j < i; j++) {
            for (int k = m + 1; k <= c; k++) {
                A[j][k] += A[j][i] * A[i][k];
            }  // for
        }      // for
    }          // for
}

int lca(int u, int v) {
    while (u != v) {
        if (dep[u] > dep[v])
            u = edge[u]->u;
        else
            v = edge[v]->u;
    }  // while

    return u;
}

inline double I(int x, int y) {
    return y < n ? -A[x][m + y] : 0;
}

double query(int s, int t) {
    int p = lca(s, t);
    double r = 0;
    Edge *e;

#define EVAL(x, op)                                      \
    for (int u = x; u != p; u = e->u) {                  \
        e = edge[u];                                     \
        r op(I(e->id, s) - I(e->id, t)) * e->dir * e->r; \
    }  // for

    EVAL(s, +=)
    EVAL(t, -=)

#undef EVAL

    return r;
}

void initialize() {
    freopen("data.in", "r", stdin);
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v;
        double r;
        scanf("%d%d%lf", &u, &v, &r);

        Edge *e = new Edge(u, v, i, 1, r);
        Edge *re = new Edge(v, u, i, -1, r);
        G[u].push_back(e);
        G[v].push_back(re);
    }

    for (int u = 1; u < n; u++) {
        A[u][m + u] = 1;
        for (auto &e : G[u]) {
            A[u][e->id] = e->dir;
        }  // foreach in G[u]
    }      // for

    dep[1] = 1;
    dfs(1);
    guass();
}

int main() {
    initialize();

    for (int s = 1; s <= n; s++) {
        for (int t = s + 1; t <= n; t++) {
            printf("%d -> %d: %.6lf\n", s, t, query(s, t));
        }  // for
    }      // for

    return 0;
}  // function main
