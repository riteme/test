// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 600
#define INFTY 1000000000

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

    int solve() {
        int ret = 0;

        while (true) {
            bfs();

            if (!level[t])
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
    int level[NMAX + 10];

    void bfs() {
        memset(level, 0, sizeof(level));
        queue<int> q;
        level[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (size_t i = 0; i < G[u].size(); i++) {
                Edge *e = G[u][i];
                int v = e->v;

                if (level[v] || e->capacity == 0)
                    continue;

                level[v] = level[u] + 1;
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

            if (level[u] + 1 != level[v] || e->capacity == 0)
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

static int n, m;
static int s, t;
static int val[NMAX + 10];
static vector<int> G[NMAX + 10];
static NetworkFlow net;

inline int id(int i, int j) {
    return i * m + j + 1;
}

static int timestamp, cnt;
static int low[NMAX + 10], dfn[NMAX + 10];
static int idx[NMAX + 10], size[NMAX + 10];
static bool marked[NMAX + 10];
static stack<int> stk;

void scc(int u) {
    stk.push(u);
    low[u] = dfn[u] = ++timestamp;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (idx[v])
            continue;
        if (!dfn[v])
            scc(v);
        low[u] = min(low[u], low[v]);
    }

    if (dfn[u] == low[u]) {
        cnt++;
        size[cnt] = 1;
        while (stk.top() != u) {
            int x = stk.top();
            stk.pop();
            idx[x] = cnt;
            size[cnt]++;
        }
        
        stk.pop();
        idx[u] = cnt;
    }
}

void mark(int u) {
    marked[u] = true;
    
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (!marked[v])
            mark(v);
    }
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            G[id(i, j + 1)].push_back(id(i, j));
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int p = id(i, j);
            scanf("%d",val + p);

            int c;
            scanf("%d", &c);
            for (int k = 0; k < c; k++) {
                int x, y;
                scanf("%d%d", &x, &y);
                G[p].push_back(id(x, y));
            }
        }
    }

    n = id(n - 1, m - 1);
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            scc(i);
    }

    for (int i = 1; i <= n; i++) {
        if (!marked[i] && size[idx[i]] > 1)
            mark(i);
    }
}

int main() {
    freopen("pvz.in", "r", stdin);
    freopen("pvz.out", "w", stdout);
    initialize();

    s = n + 1;
    t = s + 1;
    net.initialize(s, t);
    int answer = 0;
    for (int u = 1; u <= n; u++) {
        if (marked[u])
            continue;

        if (val[u] > 0) {
            answer += val[u];
            net.link(s, u, val[u]);
        } else
            net.link(u, t, -val[u]);

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            net.link(v, u, INFTY);
        }
    }

    answer -= net.solve();
    printf("%d\n", answer);

    return 0;
}
