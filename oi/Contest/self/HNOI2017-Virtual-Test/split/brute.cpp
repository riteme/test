#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define WMAX 30
#define NMAX 900
#define EMAX 2000

class NetworkFlow {
 public:
    NetworkFlow(int _n) : n(_n) {}

    void link(int u, int v, int c, int w) {
        Edge *e = new Edge(v, c, 0, w);
        Edge *re = new Edge(u, c, w, w);
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

    int dinic(int _s, int _t, int _limit) {
        int ret = 0;
        s = _s;
        t = _t;
        limit = _limit;

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
        Edge(int _to, int _cost, int _flow, int _capacity)
            : to(_to), cost(_cost),
              initial(_flow), flow(_flow), capacity(_capacity) {}

        int to;
        int cost;
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

    int n, s, t, limit;
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

                if (level[v] || e->full() || e->cost > limit)
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

            if (level[v] != level[x] + 1 || e->full() || e->cost > limit)
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

static int n, m, money;
static NetworkFlow *network;
static int tail;
static int sorted[EMAX + 10];

inline int id(int i, int j) {
    return (i - 1) * m + j;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &money);

    network = new NetworkFlow(id(n, m));
    tail = 2;
    sorted[1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            int c, w;
            scanf("%d%d", &c, &w);
            sorted[tail++] = c;
            network->link(id(i, j), id(i, j + 1), c, w);
            network->link(id(i, j + 1), id(i, j), c, w);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            int c, w;
            scanf("%d%d", &c, &w);
            sorted[tail++] = c;
            network->link(id(i, j), id(i + 1, j), c, w);
            network->link(id(i + 1, j), id(i, j), c, w);
        }
    }

    sort(sorted + 1, sorted + tail);
    tail = unique(sorted + 1, sorted + tail) - sorted;

    n = id(n, m);
}

static int limit;

int mincut() {
    int ret = INT_MAX;
    for (int s = 1; s <= n; s++) {
        for (int t = s + 1; t <= n; t++) {
            network->reset();
            ret = min(ret, network->dinic(s, t, limit));
        }
    }

    return ret;
}

bool test(int w) {
    limit = w;
    return mincut() > money;
}

int main() {
    initialize();

    int left = 1, right = tail - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (test(sorted[mid]))
            right = mid;
        else
            left = mid + 1;
    }

    if (left != right && !test(sorted[left]))
        left = right;

    if (!test(sorted[left]))
        puts("-1");
    else
        printf("%d\n", sorted[left]);

    return 0;
}

