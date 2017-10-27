#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300
#define MMAX 500
#define EPS 1e-9

inline bool equ(double a, double b) {
    return fabs(a - b) < EPS;
}

struct Edge {
    Edge(int _v, int _id, double _r, bool _d)
        : v(_v), id(_id), r(_r), dir(_d) {}

    int v, id;
    double r;
    bool dir;
    Edge *rev;
};

static int n, m;
static vector<Edge *> G[NMAX + 10];

// TODO:
//   1. Guassian elimination
//   2. Operation on the DFS tree

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v;
        double r;
        scanf("%d%d%lf", &u, &v, &r);

        Edge *e = new Edge(v, i, r, true);
        Edge *re = new Edge(u, i, r, false);
        e->rev = re;
        re->rev = e;
        G[u].push_back(e);
        G[v].push_back(re);
    }
}
