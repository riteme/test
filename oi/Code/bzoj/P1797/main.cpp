// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

#define NMAX 4000
#define MMAX 30000

struct Edge {
    Edge (int v, int w)
        : to(v), capacity(w), reverse_edge(NULL) {}

    int to;
    int capacity;
    Edge *reverse_edge;
};

static int n, m;
static vector<Edge *> G[NMAX + 10];
static int W[NMAX + 10][NMAX + 10];

static int s, t;
static bool marked[NMAX + 10];
static int level[NMAX + 10];

void initialize_network() {
    for (int u = 1; u <= n; u++) {
        size_t tail = G[u].size();
        for (size_t i = 0; i < tail; i++) {
            Edge *e = G[u][i];
            Edge *re = new Edge(u, 0);
            e->reverse_edge = re;
            re->reverse_edge = e;
            G[u].push_back(re);
        }
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
            int v = e->to;

            if (e->capacity == 0 || marked[v])
                continue;

            q.push(v);
            marked[v] = true;
            level[v] = level[u] + 1;
        }
    }
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

        int flow = min(e->capacity, maxflow - current);
        flow = dfs(v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current == maxflow)
            break;
    }

    return current;
}

int dinic() {
    int answer = 0;

    while (true) {
        bfs();

        if (!marked[t])
            break;

        answer += dfs(s, INT_MAX);
    }

    return answer;
}

template <typename TCompare>
struct Heap {
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

    bool empty() const {
        return s.empty();
    }

    size_t size() const {
        return s.size();
    }

    multiset<int, TCompare> s;
};

static int all;
static int weight[NMAX + 10];
static int cnt[MMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        Edge *e = new Edge(v, c);
        G[u].push_back(e);
        W[u][v] = c;
    }
}

int main() {
    initialize();

    return 0;
}
