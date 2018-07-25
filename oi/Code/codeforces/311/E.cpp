#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 20000
#define INFTY 1000000000
#define BLACK 0
#define WHITE 1

class NetworkFlow {
 public:
    void initialize(int _s, int _t) {
        s = _s;
        t = _t;
    }

    void link(int u, int v, int capacity) {
        Edge *e = new Edge(v, capacity);
        Edge *re = new Edge(u, 0);
        e->reverse_edge = re;
        re->reverse_edge = e;
        G[u].push_back(e);
        G[v].push_back(re);
    }

    void print() {
        for (int u = 1; u <= NMAX; u++) {
            for (auto e : G[u]) {
                if (e->capacity > 0)
                    printf("%d -> %d : %d\n", u, e->v, e->capacity);
            }
        }
    }

    int solve() {
        int ret = 0;

        while (true) {
            bfs();

            if (!dist[t])
                break;

            memset(pos, 0, sizeof(pos));
            ret += dfs(s, INFTY);
        }

        return ret;
    }

 private:
    struct Edge {
        Edge(int _v, int _capacity)
            : v(_v), capacity(_capacity) {}

        int v;
        int capacity;
        Edge *reverse_edge;
    };

    int s, t;
    vector<Edge *> G[NMAX + 10];
    size_t pos[NMAX + 10];
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

                if (dist[v] || e->capacity == 0)
                    continue;

                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    int dfs(int u, int maxflow) {
        if (u == t)
            return maxflow;

        int ret = 0;
        for (size_t &i = pos[u]; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (dist[u] + 1 != dist[v] || e->capacity == 0)
                continue;

            int flow = min(maxflow - ret, e->capacity);
            flow = dfs(v, flow);
            e->capacity -= flow;
            e->reverse_edge->capacity += flow;
            ret += flow;

            if (ret == maxflow)
                break;
        }

        return ret;
    }
};

static int n, m, g, s, t;
static int col[NMAX + 10];
static NetworkFlow net;

void initialize() {
    scanf("%d%d%d", &n, &m, &g);

    s = n + m + 1;
    t = s + 1;
    net.initialize(s, t);
}

int main() {
    initialize();

    int answer = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", col + i);
    }

    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);

        if (col[i] == BLACK)
            net.link(s, i, v);
        else
            net.link(i, t, v);
    }

    for (int i = 1; i <= m; i++) {
        int c, w, k, f;
        scanf("%d%d%d", &c, &w, &k);
        answer += w;

        if (c == BLACK) {
            for (int j = 0; j < k; j++) {
                int a;
                scanf("%d", &a);
                net.link(n + i, a, INFTY);
            }
        } else {
            for (int j = 0; j < k; j++) {
                int a;
                scanf("%d", &a);
                net.link(a, n + i, INFTY);
            }
        }

        scanf("%d", &f);

        if (c == BLACK)
            net.link(s, n + i, w + f * g);
        else if (c == WHITE)
            net.link(n + i, t, w + f * g);
    }

    // net.print();
    answer -= net.solve();
    printf("%d\n", answer);

    return 0;
}

