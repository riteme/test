#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 3000
#define MMAX 18000
#define INF 0x3f3f3f3f

inline int mmin(int a, int b) {
    return a < b ? a : b;
}

class NetworkFlow {
 public:
    NetworkFlow(int n) : s(n + 1), t(n + 2), ecnt(1) {
        memset(head, 0, sizeof(head));
    }

    void link(int u, int v, int c) {
        ecnt++;
        e[ecnt].u = u;
        e[ecnt].v = v;
        e[ecnt].c = c;
        e[ecnt].next = head[u];
        head[u] = ecnt;
        ecnt++;
        e[ecnt].u = v;
        e[ecnt].v = u;
        e[ecnt].c = 0;
        e[ecnt].next = head[v];
        head[v] = ecnt;
    }

    void reset(int _u, int _v) {
        head[s] = head[t] = 0;
        head[_u] = e[head[_u]].next;
        head[_v] = e[head[_v]].next;
        ecnt -= 4;

        for (int i = 2; i <= ecnt; i += 2) {
            e[i].c += e[i | 1].c;
            e[i | 1].c = 0;
        }
    }

    int dinic(int u, int v) {
        link(s, u, INF);
        link(v, t, INF);

        int ret = 0;
        while (true) {
            memset(fa, 0, sizeof(fa));
            fa[s] = -1;
            dfs(s);

            if (!fa[t])
                return ret;

            int minw = INF;
            int x = t;
            while (x != s) {
                minw = mmin(minw, e[fa[x]].c);
                x = e[fa[x]].u;
            }

            ret += minw;
            x = t;
            while (x != s) {
                e[fa[x]].c -= minw;
                e[fa[x] ^ 1].c += minw;
                x = e[fa[x]].u;
            }
        }
    }

    void find(bool *mark) {
        _find(s, mark);
    }

 private:
    struct Edge {
        int u, v, c, next;
    };

    int s, t;
    int fa[NMAX + 10];
    int head[NMAX + 10];
    Edge e[MMAX + 10];
    int ecnt;

    void _find(int u, bool *mark) {
        mark[u] = true;

        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;

            if (mark[v] || e[i].c == 0)
                continue;

            _find(v, mark);
        }
    }

    void dfs(int u) {
        if (u == t)
            return;

        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].v;

            if (fa[v] || e[i].c == 0)
                continue;

            fa[v] = i;
            dfs(v);
        }
    }
};

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};

static int n, m;
static NetworkFlow *solver;
static bool mark[NMAX + 10];
static int fa[NMAX + 10];
static vector<Edge *> T[NMAX + 10];

void gomory() {
    for (int i = 2; i <= n; i++) {
        fa[i] = 1;
    }

    for (int v = 2; v <= n; v++) {
        int u = fa[v];
        int w = solver->dinic(v, u);
        Edge *e = new Edge(u, v, w);
        T[u].push_back(e);
        T[v].push_back(e);

        memset(mark, 0, sizeof(mark));
        solver->find(mark);

        for (int k = v + 1; k <= n; k++) {
            if (fa[k] == u && mark[k])
                fa[k] = v;
        }

        solver->reset(v, u);
    }
}

void initialize() {
    scanf("%d%d", &n, &m);

    solver = new NetworkFlow(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        solver->link(u, v, 1);
        solver->link(v, u, 1);
    }
}

static int ans;

void dfs(int u, int f, int maxflow) {
    if (f)
        ans += maxflow;

    for (size_t i = 0; i < T[u].size(); i++) {
        Edge *e = T[u][i];
        int v = e->either(u);

        if (v == f)
            continue;

        dfs(v, u, min(maxflow, e->w));
    }
}

int main() {
    freopen("flow.in", "r", stdin);
    freopen("flow.out", "w", stdout);
    initialize();
    gomory();

    for (int u = 1; u <= n; u++) {
        dfs(u, 0, INF);
    }

    ans /= 2;
    printf("%d\n", ans);

    return 0;
}
