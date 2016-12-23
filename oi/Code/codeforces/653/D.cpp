#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 50
#define ITERATION_TIMES 100

typedef double Number;
typedef unsigned long long Integer;

struct Edge {
    int from;
    int to;
    Number origin_capacity;
    Integer capacity;
    Edge *reverse_edge;
};  // struct Edge

typedef vector<Edge *> FlowNetwork;

static int n, m, x;
static int s, t;
static Number maxbound;
static FlowNetwork G[NMAX + 10];
static int level[NMAX + 10];

static void add_edge(int u, int v, Integer capacity) {
    Edge *e = new Edge;
    Edge *re = new Edge;

    e->from = u;
    e->to = v;
    e->origin_capacity = e->origin_capacity = capacity;
    e->reverse_edge = re;

    re->from = v;
    re->to = u;
    re->origin_capacity = re->capacity = 0;
    re->reverse_edge = e;

    G[u].push_back(e);
    G[v].push_back(re);
}

static void initialize() {
    scanf("%d%d%d", &n, &m, &x);

    s = 1;
    t = n;
    maxbound = 0.0L;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        maxbound += w;
        add_edge(u, v, w);
    }  // for
}

static void update_network(Number unit) {
    for (int i = 1; i <= n; i++) {
        for (auto e : G[i]) {
            e->capacity = static_cast<Number>(e->origin_capacity) / unit;
        }  // foreach in G[i]
    }      // for
}

static void bfs() {
    memset(level, 0, sizeof(int) * (n + 10));

    level[s] = 1;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto e : G[u]) {
            int v = e->to;

            if (e->capacity == 0 || level[v] != 0)
                continue;

            level[v] = level[u] + 1;
            q.push(v);
        }  // foreach in G[u]
    }      // while
}

static Integer dfs(int u, Integer maxflow) {
    if (u == t)
        return maxflow;

    Integer current = 0;
    for (auto e : G[u]) {
        int v = e->to;

        if (e->capacity == 0 || level[u] + 1 != level[v])
            continue;

        Integer flow = min(maxflow - current, e->capacity);
        flow = dfs(v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current >= maxflow)
            break;
    }  // foreach in G[u]

    return current;
}

static Integer dinic() {
    Integer result = 0;

    while (true) {
        bfs();

        if (level[t] == 0)
            break;

        result += dfs(s, INT_MAX);
    }  // while

    return result;
}

int main() {
    initialize();

    Number left = 0.0000001, right = maxbound;
    // while (right - left >= MISS) {
    for (int iter = 0; iter < ITERATION_TIMES; iter++) {
        Number mid = (left + right) / 2.0L;

        update_network(mid);
        Integer maxflow = dinic();

        if (maxflow < x)
            right = mid;
        else
            left = mid;
    }  // while

    cout.precision(7);
    cout << fixed << right *x;
    // printf("%.7Lf", right * static_cast<Number>(x));

    return 0;
}  // function main
