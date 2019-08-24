#pragma GCC optimize(3)

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200
#define INF 1e99

struct Edge {
    Edge(int _u, int _v, double _w) : u(_u), v(_v), w(_w), nxt(NULL) {}

    int u, v;
    double w;
    Edge *nxt;
};

struct Point {
    double x, y;
};

inline double dist(const Point &a, const Point &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

static int n, m;
static Point P[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

void initialize() {
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
    }

    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u == v)
            continue;

        G[u].push_back(new Edge(u, v, dist(P[u], P[v])));
    }
}

void finalize() {
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < G[u].size(); i++)
            delete G[u][i];
        G[u].clear();
    }
}

struct State {
    State(int _x) : st(_x) {}

    int st;
    Edge *in[NMAX + 10];
};

static int cnt;
static bool del[NMAX + 10];
static int mark[NMAX + 10];
static Edge *in[NMAX + 10];

int test(int x) {
    int ret = 1;
    del[x] = true;
    for (int i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->v;

        if (!del[v])
            ret += test(v);
    }

    return ret;
}

State *find_cycle() {
    memset(mark, 0, sizeof(mark));
    for (int i = 1; i <= cnt; i++) {
        mark[i] = del[i] ? cnt + 1 : 0;
    }

    for (int i = 1; i <= cnt; i++) {
        if (mark[i])
            continue;
        
        int x = i;
        while (in[x]) {
            mark[x] = i;
            x = in[x]->u;

            if (mark[x] == i) {
                mark[x] = x;
                for (int y = in[x]->u; y != x; y = in[y]->u)
                    mark[y] = x;
                return new State(x);
            }
            if (mark[x])
                break;
        }
    }

    return NULL;
}

void _mdst(int r) {
    memset(in, 0, sizeof(in));
    for (int u = 1; u <= cnt; u++) {
        if (del[u])
            continue;

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (v != r && (!in[v] || e->w < in[v]->w))
                in[v] = e;
        }
    }

    for (int i = 2; i <= cnt; i++) {
        if (!del[i])
        printf("%d -> %d\n", in[i]->u, in[i]->v);
    }

    State *s = find_cycle();
    if (!s)
        return;

    printf("cycle: %d\n", s->st);
    memcpy(s->in, in, sizeof(in));

    cnt++;
    int x, y;
    x = y = s->st;
    do {
        del[y] = true;

        for (int i = 0; i < G[y].size(); i++) {
            Edge *e = G[y][i];
            int v = e->v;

            if (mark[v] != x)
                G[cnt].push_back(new Edge(y, v, e->w));
        }

        y = in[y]->u;
    } while (y != x);

    for (int u = 1; u < cnt; u++) {
        if (del[u])
            continue;

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (mark[v] == x) {
                Edge *ne = new Edge(u, cnt, e->w - in[v]->w);
                ne->nxt = e;
                G[u].push_back(ne);
            }
        }
    }

    x = cnt;
    _mdst(r);

    Edge *e = in[x]->nxt;
    printf("back: %d -> %d\n", e->u, e->v);
    memcpy(in, s->in, sizeof(in));
    in[e->v] = e;
    delete s;
}

double mdst(int r) {
    cnt = n;
    memset(del, 0, sizeof(del));
    if (test(r) < n)
        return INF;
    memset(del, 0, sizeof(del));

    _mdst(r);

    double ret = 0;
    for (int i = 1; i <= n; i++) {
        if (i != r)
            ret += in[i]->w;
    }

    for (int u = n + 1; u <= cnt; u++) {
        for (int i = 0; i < G[u].size(); i++)
            delete G[u][i];
        G[u].clear();
    }

    for (int u = 1; u <= n; u++) {
        while (!G[u].empty()) {
            Edge *e = G[u][G[u].size() - 1];
            if (e->v > n) {
                delete e;
                G[u].pop_back();
            } else
                break;
        }
    }

    return ret;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();

        double ans = mdst(1);

        if (ans >= INF)
            puts("poor snoopy");
        else
            printf("%.2lf\n", ans);

        finalize();
    }

    return 0;
}
// 23285517.51
