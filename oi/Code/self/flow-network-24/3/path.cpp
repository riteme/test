#include <cassert>  // <--- WARNING
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

// using namespace std;
using std::vector;
using std::queue;
using std::min;
using std::max;

// #define NDEBUG

struct Edge {
    int from;
    int to;
    int capacity;
    Edge *reverse_edge;
};  // struct Edge

static int n, m;
static int s, t;
static vector<vector<Edge *>> G;
static vector<bool> marked;
static vector<int> level;
static vector<int> prev;
static vector<int> next;

inline void add_edge(int from, int to, int capacity) {
    assert(from < G.size());
    assert(to < G.size());

    Edge *e = new Edge();
    Edge *re = new Edge();

    e->from = from;
    e->to = to;
    e->capacity = capacity;
    e->reverse_edge = re;

    re->from = to;
    re->to = from;
    re->capacity = 0;
    re->reverse_edge = e;

    assert(e->from == re->to);
    assert(e->to == re->from);

    G[from].push_back(e);
    G[to].push_back(re);
}

void initialize();

void bfs();
int dfs(int u, int maxflow);
void dinic();

void construct_path();

int main() {
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    initialize();

    dinic();

    construct_path();

    fcloseall();
    return 0;
}  // function main

void initialize() {
    scanf("%d%d", &n, &m);

    s = 0;
    t = 2 * n + 1;

    G.resize(t + 1);

    for (int i = 1; i <= n; i++) {
        add_edge(s, i, 1);
    }  // for

    for (int i = n + 1; i <= n * 2; i++) {
        add_edge(i, t, 1);
    }  // for

    for (int cnt = 0; cnt < m; cnt++) {
        int u, v;
        scanf("%d%d", &u, &v);

        assert(u < t);
        assert(v + n < t);

        add_edge(u, v + n, 1);
    }  // for

    marked.resize(t + 1);
    level.resize(t + 1);
    prev.resize(t + 1);
    next.resize(t + 1);

    for (int i = 0; i < prev.size(); i++) {
        next[i] = prev[i] = i;
    }  // for
}

void bfs() {
    for (int i = 0; i <= t; i++) {
        marked[i] = false;
        level[i] = INT_MAX;
    }  // for

    queue<int> q;

    marked[s] = true;
    level[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto e : G[u]) {
            int v = e->to;

            if (e->capacity > 0 and not marked[v]) {
                marked[v] = true;
                level[v] = level[u] + 1;

                q.push(v);
            }
        }  // foreach in G[u]
    }      // while
}

int dfs(int u, int maxflow) {
    assert(u <= t);

    if (u == t) {
        return maxflow;
    }

    int current = 0;
    for (auto e : G[u]) {
        int v = e->to;

        if (level[u] + 1 != level[v] or e->capacity == 0) {
            continue;
        }

        int flow = min(maxflow - current, e->capacity);
        flow = dfs(v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current >= maxflow) {
            return maxflow;
        }
    }  // foreach in G[u]

    return current;
}

void dinic() {
    while (true) {
        bfs();

        if (level[t] == INT_MAX) {
            return;
        }

        dfs(s, INT_MAX);
    }  // while
}

void construct_path() {
    // for (int i = 1; i <= n; i++) {
    //     for (auto e : G[i]) {
    //         if (e->capacity == 0 and e->to != s) {
    //             printf("match: %d, %d\n", i, e->to - n);
    //         }
    //     }  // foreach in G[i]
    // }      // for

    int path_count = 0;

    for (int i = 1; i <= n; i++) {
        for (auto e : G[i]) {
            if (e->capacity > 0) {
                continue;
            }

            int v = e->to;
            if (v != 0) {
                next[i] = v - n;
                prev[v - n] = i;
            }
        }  // foreach in G[i]
    }      // for

    for (int i = 1; i <= n; i++) {
        if (prev[i] == i) {
            printf("%d", i);

            int x = i;
            while (next[x] != x) {
                x = next[x];
                printf(" %d", x);
            }  // while

            path_count++;
            printf("\n");
        }
    }  // for

    printf("%d", path_count);
}
