#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000

class NetworkFlow {
 public:
    NetworkFlow(int _n) : n(_n) {}

    void link(int u, int v, int w) {
        Edge *e = new Edge(v, 0, w);
        Edge *re = new Edge(u, w, w);
        e->reverse_edge = re;
        re->reverse_edge = e;

        G[u].push_back(e);
        G[v].push_back(re);
    }

    void reset() {
        for (int u = 1; u <= n; u++) {
            for (size_t i = 0; i < G[u].size(); i++) {
                G[u][i]->reset();
            }
        }
    }

    int dinic(int _s, int _t) {
        int ret = 0;
        s = _s;
        t = _t;

        while (true) {
            bfs();

            if (!level[t])
                break;

            memset(cur, 0, sizeof(cur));
            ret += dfs(s, INT_MAX);
        }

        return ret;
    }

 private:
    struct Edge {
        Edge(int _to, int _flow, int _capacity)
            : to(_to), initial(_flow), flow(_flow), capacity(_capacity) {}

        int to;
        int initial;
        int flow;
        int capacity;
        Edge *reverse_edge;

        void reset() {
            flow = initial;
        }

        bool full() {
            return flow == capacity;
        }

        int remain() {
            return capacity - flow;
        }
    };

    int n, s, t;
    vector<Edge *> G[NMAX + 10];
    int level[NMAX + 10];
    size_t cur[NMAX + 10];

    void bfs() {
        memset(level, 0, sizeof(level));
        level[s] = 1;

        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (size_t i = 0; i < G[u].size(); i++) {
                Edge *e = G[u][i];
                int v = e->to;

                if (level[v] || e->full())
                    continue;

                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }

    int dfs(int x, int maxflow) {
        if (x == t)
            return maxflow;

        int current = 0;
        for (size_t &i = cur[x]; i < G[x].size(); i++) {
            Edge *e = G[x][i];
            int v = e->to;

            if (level[v] != level[x] + 1 || e->full())
                continue;

            int flow = min(maxflow - current, e->remain());
            flow = dfs(v, flow);
            e->flow += flow;
            e->reverse_edge->flow -= flow;
            current += flow;

            if (current == maxflow)
                break;
        }

        return current;
    }
};

static int n, m;
static NetworkFlow *network;

void initialize() {
    scanf("%d%d", &n, &m);
    network = new NetworkFlow(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        network->link(u, v, w);
        network->link(v, u, w);
    }
}

int main() {
    initialize();

    long double answer = 0.0L;
    for (int s = 1; s <= n; s++) {
        for (int t = 1; t <= n; t++) {
            if (s != t) {
                network->reset();
                int flow = network->dinic(s, t);
                answer += flow;
                printf("%d -> %d: %d\n", s, t, flow);
            }
        }
    }
    answer /= n * (n - 1);
    printf("%.10Lf\n", answer);

    return 0;
}
