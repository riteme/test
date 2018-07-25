#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define LMAX 10000

struct Edge {
    int to;
    int capacity;
    Edge *reverse_edge;
};  // struct Edge

static unsigned _memcnt;
static Edge _memory[10000000];
inline Edge *allocate() {
    return &_memory[_memcnt++];
}

static int n, L;
static int cnt;
static int s = 1, t = 2;
static vector<Edge *> G[NMAX + LMAX + 10];

inline void add_edge(int u, int v, int capacity) {
    Edge *e = allocate();
    Edge *re = allocate();

    e->to = v;
    e->capacity = capacity;
    re->to = u;
    re->capacity = 0;
    e->reverse_edge = re;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

static void initialize() {
    scanf("%d%d", &n, &L);

    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        add_edge(s, t + i, 1);
        add_edge(t + i, t + n + a, 1);
        add_edge(t + i, t + n + b, 1);
    }  // for

    for (int i = 1; i <= L; i++) {
        add_edge(t + n + i, t, 1);
    }  // for
}

static int level[NMAX + LMAX + 10];
static bool marked[NMAX + LMAX + 10];

static void bfs() {
    memset(marked, false, sizeof(marked));
    memset(level, 0, sizeof(level));

    marked[s] = true;
    level[s] = 1;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (unsigned i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->to;

            if (marked[v] || e->capacity == 0)
                continue;

            marked[v] = true;
            level[v] = level[u] + 1;
            q.push(v);
        }  // for
    }      // while
}

static int dfs(int x, int maxflow) {
    if (x == t) {
        return maxflow;
    }

    int current = 0;
    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (level[x] + 1 != level[v] || e->capacity == 0)
            continue;

        int flow = min(e->capacity, maxflow - current);
        flow = dfs(v, flow);
        current += flow;
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;

        if (current >= maxflow)
            break;
    }  // for

    return current;
}

static int dinic() {
    int answer = 0;

    while (true) {
        bfs();

        if (level[t] == 0) {
            break;
        }

        answer += dfs(s, INT_MAX);
    }  // while

    return answer;
}

int main() {
    initialize();

    if (dinic() == L) {
        puts("Yes");
    } else {
        puts("No");
    }

    return 0;
}  // function main
