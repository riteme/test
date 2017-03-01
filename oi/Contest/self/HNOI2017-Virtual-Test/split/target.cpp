// #define USE_FILE_IO
// #define NDEBUG

#define NAME "split"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define WMAX 30
#define NMAX 900
#define EMAX 2000

struct Edge {
    Edge(int _u, int _v, int _c, int _w)
        : u(_u), v(_v), c(_c), w(_w) {}

    int u, v, c, w;

    int either(int x) {
        return u == x ? v : u;
    }

    int &select(int x) {
        return u == x ? u : v;
    }
};

struct Graph {
    Graph() {
        edges.reserve(EMAX);
    }

    Graph &operator=(const Graph &g) {
        edges = g.edges;

        for (int i = 1; i <= NMAX; i++) {
            adj[i].clear();
        }

        for (size_t i = 0; i < edges.size(); i++) {
            Edge *e = &edges[i];
            adj[e->u].push_back(e);
            adj[e->v].push_back(e);
        }

        return *this;
    }

    vector<Edge> edges;
    vector<Edge *> adj[NMAX + 10];

    void link(int u, int v, int c, int w) {
        edges.push_back(Edge(u, v, c, w));
        Edge *e = &edges[edges.size() - 1];
        adj[u].push_back(e);
        adj[v].push_back(e);
    }

    void merge(int u, int v) {
        for (size_t i = 0; i < adj[v].size(); i++) {
            Edge *e = adj[v][i];

            if (e->either(v) != u) {
                e->select(v) = u;
                adj[u].push_back(e);
            }
        }
    }

    vector<Edge *> &operator[](const int u) {
        return adj[u];
    }
};

#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) | 1)
#define FATHER(x) (x >> 1)

template <typename TCompare>
struct Heap {
    Heap() : heapsize(0) {}

    void swim(int x) {
        int &p = index[x];

        while (p > 1) {
            int &fp = index[heap[FATHER(p)]];

            if (cmp(x, heap[fp])) {
                // swap(heap[p], heap[fp]);
                heap[p] = heap[fp];
                heap[fp] = x;
                swap(p, fp);
            } else
                break;
        }
    }

    void sink(int x) {
        int &p = index[x];

        while (true) {
            int nxt = p;
            if (LEFT(p) <= heapsize && cmp(heap[LEFT(p)], heap[nxt]))
                nxt = LEFT(p);
            if (RIGHT(p) <= heapsize && cmp(heap[RIGHT(p)], heap[nxt]))
                nxt = RIGHT(p);

            if (nxt == p)
                break;
            
            int &c = index[heap[nxt]];
            // swap(heap[p], heap[nxt]);
            heap[p] = heap[nxt];
            heap[nxt] = x;
            swap(p, c);
        }
    }

    void push(int x) {
        heap[++heapsize] = x;
        index[x] = heapsize;
        swim(x);
    }

    void pop() {
        heap[1] = heap[heapsize--];
        index[heap[1]] = 1;
        sink(heap[1]);
    }

    int top() {
        return heap[1];
    }

    int size() {
        return heapsize;
    }

    int index[NMAX + 10];
    int heap[NMAX + 10];
    int heapsize;
    TCompare cmp;
};

#undef LEFT
#undef RIGHT
#undef FATHER

static int n, m, money;
static Graph N;
static int tail;
static int sorted[EMAX + 10];

inline int id(int i, int j) {
    return (i - 1) * m + j;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &money);

    tail = 2;
    sorted[1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            int c, w;
            scanf("%d%d", &c, &w);
            sorted[tail++] = c;
            N.link(id(i, j), id(i, j + 1), c, w);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            int c, w;
            scanf("%d%d", &c, &w);
            sorted[tail++] = c;
            N.link(id(i, j), id(i + 1, j), c, w);
        }
    }

    sort(sorted + 1, sorted + tail);
    tail = unique(sorted + 1, sorted + tail) - sorted;

    n = id(n, m);
}

static Graph G;
static int limit;
static int marked[NMAX + 10];
static int visited[NMAX + 10];
static int weight[NMAX + 10];

struct cmp {
    bool operator()(const int a, const int b) const {
        return weight[a] > weight[b] ||
              (weight[a] == weight[b] && a < b);
    }
};

int maximum_adjacency_search(int &s, int &t) {
    memset(weight, 0, sizeof(weight));
    memset(visited, 0, sizeof(visited));

    Heap<cmp> q;
    for (int u = 1; u <= n; u++) {
        if (!marked[u])
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

            if (e->c > limit || visited[v] || marked[v])
                continue;

            weight[v] += e->w;
            q.swim(v);
        }
    }

    t = q.top();
    return weight[t];
}

int mincut(int cnt) {
    int ret = INT_MAX;
    for (int u = 1; u <= n; u++) {
        int sum = 0;

        for (size_t i = 0; i < N[u].size(); i++) {
            Edge *e = N[u][i];

            if (e->c > limit)
                continue;

            sum += e->w;
        }

        ret = min(ret, sum);
    }

    return ret;
}

bool test(int w) {
    limit = w;
    return mincut(n) > money;
}

int main() {
#ifdef USE_FILE_IO
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();

    // int left = 1, right = tail - 1;
    // while (left + 1 < right) {
    //     int mid = (left + right) / 2;

    //     if (test(sorted[mid]))
    //         right = mid;
    //     else
    //         left = mid + 1;
    // }

    // if (left != right && !test(sorted[left]))
    //     left = right;

    // if (!test(sorted[left]))
    //     puts("-1");
    // else
    //     printf("%d\n", sorted[left]);

    int pos = 1;
    for (; pos < tail; pos++) {
        if (test(sorted[pos]))
            break;
    }

    if (pos >= tail)
        puts("-1");
    else
        printf("%d\n", sorted[pos]);

    return 0;
}

