// TLE on topological graph

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int capacity;

    Edge *reverse_edge;
};  // struct Edge

#define NMAX 1000000

static int n, m;
static vector<Edge *> G[NMAX + 10];

inline void add_edge(int from, int to, int c) {
    Edge *e = new Edge;
    Edge *re = new Edge;

    e->to = to;
    e->capacity = c;
    e->reverse_edge = re;

    re->to = from;
    re->capacity = 0;
    re->reverse_edge = e;

    G[from].push_back(e);
    G[to].push_back(re);
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        add_edge(u, v, c);
    }  // for
}

static int s = 1, t;
static bool marked[NMAX + 10];
static int dfs(int x, int maxflow) {
    if (x == t) {
        return maxflow;
    }

    marked[x] = true;
    int current = 0;
    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];

        if (e->capacity == 0 || marked[e->to]) {
            continue;
        }

        int flow = min(maxflow - current, e->capacity);
        flow = dfs(e->to, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current == maxflow) {
            break;
        }
    }  // for

    marked[x] = false;
    return current;
}

int main() {
    freopen("networkflow.in", "r", stdin);
    freopen("networkflow.out", "w", stdout);

    initialize();

    t = n;
    printf("%d\n", dfs(1, INT_MAX));

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
