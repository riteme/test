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

static int n, k, m;
static int s, t;
static vector<vector<Edge *>> G;
static vector<bool> marked;
static vector<int> level;
static int answer;

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

void print_answer();

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    initialize();

    dinic();

    print_answer();

    fcloseall();
    return 0;
}  // function main

void initialize() {
    scanf("%d%d", &k, &n);

    s = 0;
    t = k + n + 1;
    m = 0;

    G.resize(t + 1);

    for (int i = 1; i <= n; i++) {
        add_edge(s, i, 1);
    }  // for

    for (int i = n + 1; i <= k + n; i++) {
        int a;
        scanf("%d", &a);

        m += a;
        add_edge(i, t, a);
    }  // for

    for (int i = 1; i <= n; i++) {
        int q;
        scanf("%d", &q);

        while (q > 0) {
            int x;
            scanf("%d", &x);

            add_edge(i, x + n, 1);
            q--;
        }  // while
    }      // for

    marked.resize(t + 1);
    level.resize(t + 1);

    answer = 0;
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

        answer += dfs(s, INT_MAX);
    }  // while
}

void print_answer() {
    if (answer < m) {
        printf("No Solution!");

        return;
    }

    for (int i = n + 1; i <= n + k; i++) {
        printf("%d:", i - n);
        for (auto e : G[i]) {
            if (e->capacity > 0) {
                printf(" %d", e->to);
            }
        }  // foreach in G[i]
        printf("\n");
    }  // for
}
