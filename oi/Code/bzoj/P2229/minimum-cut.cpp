/**
 * 使用Dinic算法寻找s-t最小割
 * 注意要卡常，由于n = 150, m有几千级别，图比较密
 * 因此，注意if的短路，先判定是否是分层图的边
 * 然后判定是否可走，因为边数很多的情况下
 * 一般只有m / 2条边为0流量
 * 而绝大部分边都不在分层图上。该优化加速33%
 * 在递归时去掉所有自环。该优化加速22%
 * 使用前向弧优化。该优化加速45%
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 150
#define MMAX 3000
#define QMAX 30

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int &select(int x) {
        return u == x ? u : v;
    }

    int either(int x) const {
        return u == x ? v : u;
    }
};

struct Graph {
    Graph() {
        edges.reserve(MMAX * 4 + 10);
    }

    Graph(const Graph &g) {
        assign(g);
    }

    void reset(int _n) {
        n = _n;

        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }

        edges.clear();
    }

    void merge(int dest, int src) {
        for (size_t i = 0; i < adj[src].size(); i++) {
            Edge *e = adj[src][i];

            e->select(src) = dest;
            adj[dest].push_back(e);
        }

        adj[src].clear();
    }

    void link(int u, int v, int w) {
        if (u == v)
            return;

        Edge *e = allocate(u, v, w);
        adj[u].push_back(e);
        adj[v].push_back(e);
    }
    
    Edge *allocate(int u, int v, int w) {
        edges.push_back(Edge(u, v, w));
        return &edges[edges.size() - 1];
    }

    vector<Edge *> &operator[](const int u) {
        return adj[u];
    }

    const vector<Edge *> &operator[](const int u) const {
        return adj[u];
    }

    Graph &operator=(const Graph &g) {
        assign(g);

        return *this;
    }

    void assign(const Graph &g) {
        reset(g.n);

        for (size_t i = 0; i < g.edges.size(); i++) {
            const Edge &e = g.edges[i];

            if (e.u != e.v)
                edges.push_back(e);
        }

        for (size_t i = 0; i < edges.size(); i++) {
            Edge *e = &edges[i];

            adj[e->u].push_back(e);
            adj[e->v].push_back(e);
        }
    }

    int n;
    vector<Edge *> adj[NMAX + 10];
    vector<Edge> edges;
};

class NetworkFlow {
 public:
    NetworkFlow(const Graph &g) : n(g.n) {
        for (size_t i = 0; i < g.edges.size(); i++) {
            const ::Edge &e = g.edges[i];

            if (e.u == e.v)
                continue;

            add_edge(e.u, e.v, e.w);
            add_edge(e.v, e.u, e.w);
        }
    }

    ~NetworkFlow() {
        // for (int u = 1; u <= n; u++) {
        //     for (size_t i = 0; i < G[u].size(); i++) {
        //         delete G[u][i];
        //     }
        // }
    }

    int dinic_once(int _s, int _t) {
        s = _s;
        t = _t;
        int answer = 0;

        while (true) {
            bfs();

            if (!marked[t])
                break;

            memset(index, 0, sizeof(index));
            answer += dfs(s, INT_MAX);
        }

        return answer;
    }

    int find_s(int *arr) {
        memset(marked, 0, sizeof(marked));
        int pos = 0;
        search(s, arr, pos); 
        return pos;
    }

    int find_t(int *arr) {
        int pos = 0;

        for (int i = 1; i <= n; i++) {
            if (!G[i].empty() && !marked[i])
                arr[++pos] = i;
        }

        return pos;
    }

 private:
    static int level[NMAX + 10];
    static size_t index[NMAX + 10];
    static bool marked[NMAX + 10];

    struct Edge {
        int to;
        int capacity;
        Edge *reverse_edge;
    };

    void add_edge(int u, int v, int capacity) {
        Edge *e = new Edge;
        Edge *re = new Edge;

        e->to = v;
        e->capacity = capacity;
        e->reverse_edge = re;
        re->to = u;
        re->capacity = 0;
        re->reverse_edge = e;

        G[u].push_back(e);
        G[v].push_back(re);
    }

    void search(int x, int *arr, int &pos) {
        marked[x] = true;
        arr[++pos] = x;

        for (size_t i = 0; i < G[x].size(); i++) {
            Edge *e = G[x][i];

            if (e->capacity == 0 || marked[e->to])
                continue;

            search(e->to, arr, pos);
        }
    }

    void bfs() {
        memset(marked, 0, sizeof(marked));
        memset(level, 0, sizeof(level));

        queue<int> q;
        q.push(s);
        marked[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (size_t i = 0; i < G[u].size(); i++) {
                Edge *e = G[u][i];
                
                if (e->capacity == 0 || marked[e->to])
                    continue;

                marked[e->to] = true;
                level[e->to] = level[u] + 1;
                q.push(e->to);
            }
        }
    }

    int dfs(int x, int maxflow) {
        if (x == t)
            return maxflow;

        int current = 0;
        for (size_t &i = index[x]; i < G[x].size(); i++) {
            Edge *e = G[x][i];

            if (level[x] + 1 != level[e->to] || e->capacity == 0)
                continue;

            int flow = MIN(e->capacity, maxflow - current);
            flow = dfs(e->to, flow);
            e->capacity -= flow;
            e->reverse_edge->capacity += flow;
            current += flow;

            if (current == maxflow)
                break;
        }

        return current;
    }

    int n, s, t;
    vector<Edge *> G[NMAX + 10];
};

int NetworkFlow::level[NMAX + 10];
bool NetworkFlow::marked[NMAX + 10];
size_t NetworkFlow::index[NMAX + 10];

class GomoryHuTree {
 public:
    GomoryHuTree(const Graph &G) {
        T.n = G.n;
        build(G, 0);
    }

    int get_answer(int *arr) {
        int pos = 0;
        for (int i = 1; i <= T.n; i++) {
            memset(marked, 0, sizeof(marked));
            dfs(i, i, INT_MAX, arr, pos);
        }

        return pos;
    }

 private:
    static bool marked[NMAX + 10];

    Graph T;

    void dfs(int x, int s, int val, int *arr, int &pos) {
        marked[x] = true;
        if (s < x)
            arr[++pos] = val;

        for (size_t i = 0; i < T[x].size(); i++) {
            Edge *e = T[x][i];
            int v = e->either(x);

            if (marked[v])
                continue;

            dfs(v, s, min(val, e->w), arr, pos);
        }
    }

    void build(const Graph &G, int sp) {
        int s = 0, t = 0;
        for (int i = 1; i <= G.n; i++) {
            if (G[i].empty() || i == sp)
                continue;

            if (!s)
                s = i;
            else {
                t = i;
                break;
            }
        }

        if (!t)
            return;

        int scnt, tcnt;
        int sset[NMAX + 10];
        int tset[NMAX + 10];

        NetworkFlow net(G);
        int w = net.dinic_once(s, t);
        scnt = net.find_s(sset);
        tcnt = net.find_t(tset);
        
        // printf("s = %d, t = %d, w = %d\n", s, t, w);

        T.link(s, t, w);

        Graph N = G;
        for (int i = 1; i <= scnt; i++) {
            int u = sset[i];

            if (u != s && u != sp)
                N.merge(s, u);
        }

        if (sp)
            N.merge(s, sp);

        build(N, s);

        N = G;
        for (int i = 1; i <= tcnt; i++) {
            int u = tset[i];

            if (u != t && u != sp)
                N.merge(t, u);
        }

        if (sp)
            N.merge(t, sp);

        build(N, t);
    }
};

bool GomoryHuTree::marked[NMAX + 10];

static int t, n, m, q;
static Graph G;

void initialize() {
    scanf("%d%d", &n, &m);
    G.reset(n);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        G.link(u, v, c);
    }
}

static int cnt;
static int answer[NMAX * NMAX + 10];

int main() {
    scanf("%d", &t);

    while (t--) {
        initialize();

        GomoryHuTree tree(G);
        cnt = tree.get_answer(answer);
        int all = n * (n - 1) / 2;

        scanf("%d", &q);
        while (q--) {
            int x;
            scanf("%d", &x);

            int ans = all;
            for (int i = 1; i <= cnt; i++) {
                if (answer[i] > x)
                    ans--;
            }

            printf("%d\n", ans);
        }

        if (t)
            putchar('\n');
    }

    return 0;
}
