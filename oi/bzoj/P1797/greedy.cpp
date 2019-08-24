// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

using namespace std;

#define NMAX 4000
#define MMAX 60000

struct Graph {
    struct Edge {
        Edge(int _id, int _v, int _w) : id(_id), v(_v), w(_w) {}

        int id, v, w;
    };  // struct Edge

    void link(int u, int v, int w, int id) {
        G[u].push_back(new Edge(id, v, w));
    }

    int n;
    vector<Edge *> G[NMAX + 10];

    vector<Edge *> &operator[](int u) {
        return G[u];
    }

    const vector<Edge *> &operator[](int u) const {
        return G[u];
    }
};  // struct Graph

class NetworkFlow {
 public:
    NetworkFlow(const Graph &g, int _n) : n(_n) {
        for (int u = 1; u <= n; u++) {
            for (size_t i = 0; i < g[u].size(); i++) {
                Graph::Edge *e = g[u][i];
                link(u, e->v, e->w);
            }  // for
        }      // for
    }

    int dinic_once(int u, int v) {
        int ret = 0;
        s = u, t = v;

        while (true) {
            bfs();

            if (!marked[t])
                break;

            ret += dfs(s, INT_MAX);
        }  // while

        return ret;
    }

 private:
    static int level[NMAX + 10];
    static bool marked[NMAX + 10];

    struct Edge {
        Edge(int v, int w) : to(v), capacity(w) {}

        int to;
        int capacity;
        Edge *reverse_edge;
    };  // struct Edge

    void link(int u, int v, int w) {
        Edge *e = new Edge(v, w);
        Edge *re = new Edge(u, 0);
        e->reverse_edge = re;
        re->reverse_edge = e;
        G[u].push_back(e);
        G[v].push_back(re);
    }

    void bfs() {
        memset(level, 0, sizeof(level));
        memset(marked, 0, sizeof(marked));

        queue<int> q;
        q.push(s);
        marked[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (size_t i = 0; i < G[u].size(); i++) {
                Edge *e = G[u][i];
                int v = e->to;

                if (e->capacity == 0 || marked[v])
                    continue;

                marked[v] = true;
                level[v] = level[u] + 1;
                q.push(v);
            }  // for
        }      // while
    }

    int dfs(int x, int maxflow) {
        if (x == t)
            return maxflow;

        int current = 0;
        for (size_t i = 0; i < G[x].size(); i++) {
            Edge *e = G[x][i];
            int v = e->to;

            if (level[v] != level[x] + 1 || e->capacity == 0)
                continue;

            int flow = min(maxflow - current, e->capacity);
            flow = dfs(v, flow);
            e->capacity -= flow;
            e->reverse_edge->capacity += flow;
            current += flow;

            if (current == maxflow)
                break;
        }  // for

        return current;
    }

    int n, s, t;
    vector<Edge *> G[NMAX + 10];
};  // class NetworkFlow

int NetworkFlow::level[NMAX + 10];
bool NetworkFlow::marked[NMAX + 10];

template <typename TCompare>
class Heap {
 public:
    void push(int x) {
        s.insert(x);
    }

    void pop(int x) {
        typename multiset<int, TCompare>::iterator iter = s.find(x);
        assert(iter != s.end());
        s.erase(iter);
    }

    void pop() {
        s.erase(s.begin());
    }

    int top() {
        return *s.begin();
    }

    bool empty() {
        return s.empty();
    }

    size_t size() {
        return s.size();
    }

 private:
    multiset<int, TCompare> s;
};  // class Heap

static int n, m, s, t;
static Graph G;
static int W[NMAX + 10][NMAX + 10];

static int all, ans;
static int weight[NMAX + 10];
static int cnt[MMAX + 10];
static bool exist[NMAX + 10];
static vector<int> S;

struct Compare {
    bool operator()(const int a, const int b) const {
        return weight[a] > weight[b] || (weight[a] == weight[b] && a < b);
    }
};  // struct Compare

void update() {
    all++;
    for (size_t i = 0; i < S.size(); i++) {
        int u = S[i];
        for (size_t j = 0; j < G[u].size(); j++) {
            Graph::Edge *e = G[u][j];
            int v = e->v;

            if (!exist[v])
                cnt[e->id]++;
        }  // for
    }      // for
}

void search() {
    int cut = 0;

    exist[s] = true;
    S.push_back(s);

    for (size_t i = 0; i < G[s].size(); i++) {
        Graph::Edge *e = G[s][i];
        int v = e->v;
        weight[v] += e->w;
        cut += e->w;
    }  // for

    Heap<Compare> q;
    for (int i = 1; i <= n; i++) {
        if (i != s && i != t)
            q.push(i);
    }  // for

    if (cut == ans)
        update();

    while (!q.empty()) {
        int u = q.top();
        q.pop();

        for (size_t i = 0; i < S.size(); i++) {
            cut -= W[S[i]][u];
        }  // for

        exist[u] = true;
        S.push_back(u);

        for (size_t i = 0; i < G[u].size(); i++) {
            Graph::Edge *e = G[u][i];
            int v = e->v;

            if (!exist[v]) {
                cut += e->w;

                if (v != t) {
                    q.pop(v);
                    weight[v] += e->w;
                    q.push(v);
                }
            }
        }  // for

        if (cut == ans)
            update();
    }  // while
}

void initialize() {
    scanf("%d%d%d%d", &n, &m, &s, &t);

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        G.link(u, v, c, i);
        W[u][v] = c;
    }  // for
}

int main() {
    initialize();

    NetworkFlow net(G, n);
    ans = net.dinic_once(s, t);
    search();

    for (int i = 1; i <= m; i++) {
        printf("%d %d\n", cnt[i] ? 1 : 0, cnt[i] == all ? 1 : 0);
    }  // for

    return 0;
}  // function main
