#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 3000
#define INF 0x3f3f3f3f

class NetworkFlow {
 public:
    NetworkFlow(int n) : s(n + 1), t(n + 2) {}

    void link(int u, int v, int c) {
        Edge *e = new Edge(v, c);
        Edge *re = new Edge(u, 0);
        e->rev = re;
        e->pivot = true;
        re->rev = e;
        G[u].push_back(e);
        G[v].push_back(re);
    }

    void reset(int _u, int _v) {
        G[s].clear();
        G[t].clear();
        G[_u].pop_back();
        G[_v].pop_back();

        for (int u = 1; u < s; u++) {
            for (size_t i = 0; i < G[u].size(); i++) {
                Edge *e = G[u][i];

                if (e->pivot) {
                    e->c += e->rev->c;
                    e->rev->c = 0;
                }
            }
        }
    }

    int dinic(int u, int v) {
        link(s, u, INF);
        link(v, t, INF);

        int ret = 0;
        while (true) {
            bfs();

            if (!dist[t])
                return ret;

            memset(pos, 0, sizeof(pos));
            ret += dfs(s, INF);
        }
    }

    void find(bool *mark) {
        _find(s, mark);
    }

 private:
    struct Edge {
        Edge(int _v, int _c)
            : pivot(false), v(_v), c(_c), rev(NULL) {}

        bool pivot;
        int v, c;
        Edge *rev;
    };

    int s, t;
    int dist[NMAX + 10];
    size_t pos[NMAX + 10];
    vector<Edge *> G[NMAX + 10];

    void _find(int u, bool *mark) {
        mark[u] = true;

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (mark[v] || e->c == 0)
                continue;

            _find(v, mark);
        }
    }

    void bfs() {
        memset(dist, 0, sizeof(dist));
        dist[s] = 1;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (size_t i = 0; i < G[u].size(); i++) {
                Edge *e = G[u][i];
                int v = e->v;

                if (dist[v] || e->c == 0)
                    continue;

                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    int dfs(int u, int maxflow) {
        if (u == t)
            return maxflow;

        int cur = 0;
        for (size_t &i = pos[u]; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (dist[u] + 1 != dist[v] || e->c == 0)
                continue;

            int flow = min(maxflow - cur, e->c);
            flow = dfs(v, flow);
            cur += flow;
            e->c -= flow;
            e->rev->c += flow;

            if (cur == maxflow)
                break;
        }

        return cur;
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
    initialize();
    gomory();

    for (int u = 1; u <= n; u++) {
        dfs(u, 0, INF);
    }

    ans /= 2;
    printf("%d\n", ans);

    return 0;
}
