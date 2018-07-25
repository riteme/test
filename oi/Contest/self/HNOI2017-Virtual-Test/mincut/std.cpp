// #define USE_FILE_IO
// #define NDEBUG

#define NAME "mincut"

#include <cassert>
#include <cstdio>
#include <cstring>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }

    int &select(int x) {
        return u == x ? u : v;
    }
};

static int n, m;
static vector<Edge *> T[NMAX + 10];

struct Graph {
    Graph() {
        edges.reserve(m);
    }

    void reset() {
        edges.clear();

        for (int u = 1; u <= n; u++) {
            G[u].clear();
        }
    }

    void copy(Graph &g) {
        edges = g.edges;

        for (int u = 1; u <= n; u++) {
            G[u] = g[u];
        }
    }

    void merge(int dest, int src) {
        for (size_t i = 0; i < G[src].size(); i++) {
            Edge *e = G[src][i];

            if (e->either(src) == src)
                continue;

            e->select(src) = dest;
            G[dest].push_back(e);
        }
    }

    void link(int u, int v, int w) {
        edges.push_back(Edge(u, v, w));
        G[u].push_back(&edges[edges.size() - 1]);
        G[v].push_back(&edges[edges.size() - 1]);
    }

    vector<Edge *> &operator[](const int u) {
        return G[u];
    }

    vector<Edge> edges;
    vector<Edge *> G[NMAX + 10];
};

static Graph *G1;

void initialize() {
    scanf("%d%d", &n, &m);
    G1 = new Graph;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        G1->link(u, v, w);
    }
}

template <typename TCompare>
struct Heap {
    void push(int x) {
        s.insert(x);
    }

    void pop(int x) {
        typename set<int, TCompare>::iterator iter = s.find(x);

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

    set<int, TCompare> s;
};

static bool marked[NMAX + 10];
static bool visited[NMAX + 10];
static int weight[NMAX + 10];

struct cmp {
    bool operator()(const int a, const int b) const {
        return weight[a] > weight[b] ||
              (weight[a] == weight[b] && a < b);
    }
};

int mincut(Graph &G, int a, int &s, int &t) {
    if (a == 0) {
        for (int u = 1; u <= n; u++) {
            if (!marked[u] && !G[u].empty()) {
                a = u;
                break;
            }
        }
    }

    memset(visited, 0, sizeof(visited));
    memset(weight, 0, sizeof(weight));
    Heap<cmp> q;
    for (size_t i = 0; i < G[a].size(); i++) {
        Edge *e = G[a][i];
        int v = e->either(a);

        assert(!marked[v]);
        weight[v] += e->w;
    }

    visited[a] = true;
    for (int u = 1; u <= n; u++) {
        if (!marked[u] && u != a)
            q.push(u);
    }

    while (q.size() > 1) {
        int u = q.top();
        q.pop();

        s = u;
        visited[u] = true;
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            assert(!marked[v]);
            if (!visited[v]) {
                q.pop(v);
                weight[v] += e->w;
                q.push(v);
            }
        }
    }

    t = q.top();
    return weight[t];
}

int constrcut(Graph &G, int sp = 0) {
    int remain = 0, p;
    for (int u = 1; u <= n; u++) {
        if (!marked[u]) {
            remain++;

            if (u != sp)
                p = u;
        }
    }

    if (remain <= 2)
        return p;

    int s, t;
    int w = mincut(G, sp, s, t);
    printf("s = %d, t = %d, w = %d\n", s, t, w);

    if (sp) {
        G.merge(sp, t);
        marked[t] = true;
    } else
        sp = t;

    int v = constrcut(G, sp);

    Edge *e = new Edge(v, t, w);
    T[v].push_back(e);
    T[t].push_back(e);

    return v;
}

int main() {
    freopen(NAME ".in", "r", stdin);
#ifdef USE_FILE_IO
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();
    constrcut(*G1);

    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < T[u].size(); i++) {
            Edge *e = T[u][i];

            if (e->either(u) > u)
                printf("(%d, %d, %d)\n", e->u, e->v, e->w);
        }
    }

    return 0;
}
