#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 500
#define INF 0x3f3f3f3f

class NetworkFlow {
 public:
    void link(int u, int v, int c) {
        Edge *e = new Edge(v, c);
        Edge *re = new Edge(u, 0);
        e->pivot = true;
        e->rev = re;
        re->rev = e;
        G[u].push_back(e);
        G[v].push_back(re);
    }

    void solve() {
        while (true) {
            bfs();

            if (!dist[t])
                break;

            dfs(s, INF);
        }
    }

    struct Edge {
        Edge(int _v, int _c)
            : pivot(false), v(_v), c(_c) {}

        bool pivot;
        int v, c;
        Edge *rev;
    };

    int s, t;
    vector<Edge *> G[NMAX + 10];
    int dist[NMAX + 10];

    void bfs() {
        memset(dist, 0, sizeof(dist));
        queue<int> q;
        dist[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto e : G[u]) {
                int v = e->v;

                if (e->c && !dist[v]) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }

    int dfs(int u, int maxflow) {
        if (u == t)
            return maxflow;

        int cur = 0;
        for (auto e : G[u]) {
            int v = e->v;

            if (dist[u] + 1 != dist[v] || e->c == 0)
                continue;

            int flow = min(e->c, maxflow - cur);
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

static int n, m, ans;
static int d[NMAX + 10], x[NMAX + 10], y[NMAX + 10];
static NetworkFlow solver;

void initialize() {
    scanf("%d%d", &n, &m);

    int s = n + m + 1, t = s + 1;
    solver.s = s;
    solver.t = t;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", x + i, y + i);
        d[x[i]]++;
        d[y[i]]++;

        solver.link(s, n + i, 1);
        solver.link(n + i, x[i], 1);
        solver.link(n + i, y[i], 1);
    }

    for (int i = 1; i <= n; i++) {
        if (d[i] % 2 == 0) {
            ans++;
            solver.link(i, t, d[i] / 2);
        }
    }
}

int main() {
    initialize();
    solver.solve();
    for (int i = 1; i <= n; i++) {
        if (d[i] & 1)
            solver.link(i, solver.t, INF);
    }
    solver.solve();

    printf("%d\n", ans);
    for (int i = 1; i <= m; i++) {
        int v;
        for (auto e : solver.G[n + i]) {
            if (e->pivot && e->c == 0 && e->v <= n)
                v = e->v;
        }

        // putchar(rand() & 1 ? '0' : '1');
        putchar(v == y[i] ? '0' : '1');
    }

    return 0;
}
