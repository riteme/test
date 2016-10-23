#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

namespace Cactus {

const int NMAX = 10000;
const int MMAX = 20000;
// const int NMAX = 100;
// const int MMAX = 200;

struct Edge {
    int u, v;
    int color;
    int id;

    int either(int x) const {
        return x == u ? v : u;
    }
};  // struct Edge

static int n, m;
static int pos = 1;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static bool marked[NMAX + 10];
static Edge *father[NMAX + 10];
static int depth[NMAX + 10];
static int ref[MMAX + 10];
static int colorcnt;
static int cnt = 1;

inline void add_edge(int u, int v, int color) {
    Edge *e = edges + pos;
    pos++;
    e->u = u;
    e->v = v;
    e->color = color;

    if (ref[color] == 0)
        colorcnt++;
    ref[color]++;
    G[u].push_back(e);
    G[v].push_back(e);
}

static void generate_tree(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (!marked[v]) {
            e->id = 1;
            father[v] = e;
            depth[v] = depth[x] + 1;
            generate_tree(v);
        }
    }  // for
}

static void remark() {
    for (int i = 1; i <= m; i++) {
        if (edges[i].id == 0) {
            edges[i].id = ++cnt;
            int u = edges[i].u;
            int v = edges[i].v;

            if (depth[u] < depth[v])
                swap(u, v);

            while (depth[u] != depth[v]) {
                father[u]->id = cnt;
                u = father[u]->either(u);
            }  // while

            while (u != v) {
                father[u]->id = cnt;
                father[v]->id = cnt;
                u = father[u]->either(u);
                v = father[v]->either(v);
            }  // while
        }
    }  // for
}

}  // namespace Cactus

namespace NetworkFlow {

const int NMAX = 30000;
// const int NMAX = 300;

struct Edge {
    int from, to;
    int cost;
    int capacity;
    Edge *reverse_edge;
};  // struct Edge

static int n;
static int s, t;
static vector<Edge *> G[NMAX + 10];

inline void add_edge(int from, int to, int capacity, int cost) {
    Edge *e = new Edge;
    Edge *re = new Edge;

    e->from = from;
    e->to = to;
    e->capacity = capacity;
    e->cost = cost;
    e->reverse_edge = re;
    re->from = to;
    re->to = from;
    re->capacity = 0;
    re->cost = -cost;
    re->reverse_edge = e;

    G[from].push_back(e);
    G[to].push_back(re);
}

static bool in_queue[NMAX + 10];
static int dist[NMAX + 10];
static Edge *edge_to[NMAX + 10];

static void spfa() {
    memset(in_queue, 0, sizeof(in_queue));
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }  // for

    queue<int> q;
    q.push(s);
    in_queue[s] = true;
    dist[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->to;

            if (e->capacity == 0)
                continue;

            if (dist[u] + e->cost < dist[v]) {
                dist[v] = dist[u] + e->cost;
                edge_to[v] = e;

                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }  // for
    }      // while
}

static int maxflow, mincost;

static void sap() {
    while (true) {
        spfa();

        if (dist[t] == INT_MAX)
            break;

        int minpoint = INT_MAX;
        int x = t;
        while (x != s) {
            minpoint = min(minpoint, edge_to[x]->capacity);

            x = edge_to[x]->from;
        }

        maxflow += minpoint;
        mincost += dist[t];

        x = t;
        while (x != s) {
            edge_to[x]->capacity -= minpoint;
            edge_to[x]->reverse_edge->capacity += minpoint;

            x = edge_to[x]->from;
        }
    }  // while
}

}  // namespace NetworkFlow

static void initialize() {
    scanf("%d%d", &Cactus::n, &Cactus::m);

    for (int i = 1; i <= Cactus::m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        Cactus::add_edge(u, v, c);
    }  // for
}

int main() {
    initialize();

    Cactus::generate_tree(1);
    Cactus::remark();

    NetworkFlow::n = Cactus::n + Cactus::m + 2;
    NetworkFlow::s = Cactus::n + Cactus::m + 1;
    NetworkFlow::t = Cactus::n + Cactus::m + 2;
    for (int i = 1; i <= Cactus::m; i++) {
        if (Cactus::ref[i]) {
            NetworkFlow::add_edge(NetworkFlow::s, i, 1, 1);

            if (Cactus::ref[i] > 1)
                NetworkFlow::add_edge(NetworkFlow::s, i, Cactus::ref[i] - 1, 0);
        }
    }  // for

    for (int i = 2; i <= Cactus::cnt; i++) {
        NetworkFlow::add_edge(Cactus::m + i, NetworkFlow::t, 1, 0);
    }  // for

    for (int i = 1; i <= Cactus::m; i++) {
        Cactus::Edge &e = Cactus::edges[i];

        if (e.id < 2)
            continue;

        NetworkFlow::add_edge(e.color, Cactus::m + e.id, 1, 0);
    }  // for

    NetworkFlow::sap();

    if (NetworkFlow::maxflow != Cactus::cnt - 1)
        puts("Invalid flow.");
    else
        printf("%d\n", Cactus::colorcnt - NetworkFlow::mincost);

    return 0;
}  // function main
