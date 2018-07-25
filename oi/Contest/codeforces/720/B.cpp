/**
 * 想法好劲......
 * 最开始想的是费用流，但是SPFA卡成狗......
 * 标解用最大流，是考虑用环来尽可能多保护颜色
 *
 * 首先，每个颜色只在在一条边上出现就可以对答案造成贡献
 * 颜色 : 1 -> t
 * 这样只要有任意流流过，这个颜色就可以保留
 *
 * 桥边不会被删掉，因此桥边上的颜色肯定会被留下来
 * s -> 桥边 : 桥边数量 -> 对应颜色 : 1 -> t
 *
 * 对于环，设环的长度为L，那么它至多保留L - 1中颜色
 * 因此
 * s -> 环编号 : L - 1 -> 环上颜色 : 1 -> t
 *
 * 同时可以发现，只要环中有颜色出现次数超过一次，那么环上所有的颜色就都可以保留
 * 同时只要有环保留过某一中颜色，那么对于其它的环就不用考虑它了。
 * 使用最大流来保证答案最大
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <queue>
#include <bitset>
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
static int cyclesize[MMAX + 10];
static bitset<MMAX + 10> colormap[NMAX + 10];
static int cnt = 1;

inline void add_edge(int u, int v, int color) {
    Edge *e = edges + pos;
    pos++;
    e->u = u;
    e->v = v;
    e->color = color;

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

static void process_colormap() {
    for (int i = 1; i <= m; i++) {
        Edge &e = edges[i];

        colormap[e.id][e.color] = true;
        cyclesize[e.id]++;
    }  // for
}

}  // namespace Cactus

namespace NetworkFlow {

const int NMAX = 30000;
// const int NMAX = 300;

struct Edge {
    int from, to;
    int capacity;
    Edge *reverse_edge;
};  // struct Edge

static int n;
static int s, t;
static vector<Edge *> G[NMAX + 10];

inline void add_edge(int from, int to, int capacity) {
    Edge *e = new Edge;
    Edge *re = new Edge;

    e->from = from;
    e->to = to;
    e->capacity = capacity;
    e->reverse_edge = re;
    re->from = to;
    re->to = from;
    re->capacity = 0;
    re->reverse_edge = e;

    G[from].push_back(e);
    G[to].push_back(re);
}

static bool marked[NMAX + 10];
static int level[NMAX + 10];

static void bfs() {
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

            marked[v] = true;
            level[v] = level[u] + 1;
            q.push(v);
        }  // for
    }      // while
}

static int dfs(int x, int maxflow) {
    if (x == t)
        return maxflow;

    int current = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (e->capacity == 0 || level[x] + 1 != level[v])
            continue;

        int flow = min(maxflow - current, e->capacity);
        flow = dfs(v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current >= maxflow)
            break;
    }  // for

    return current;
}

static int dinic() {
    int flow = 0;

    while (true) {
        bfs();

        if (!marked[t])
            break;

        flow += dfs(s, INT_MAX);
    }  // while

    return flow;
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
    Cactus::process_colormap();

    NetworkFlow::n = Cactus::n + Cactus::m + 2;
    NetworkFlow::s = Cactus::n + Cactus::m + 1;
    NetworkFlow::t = Cactus::n + Cactus::m + 2;
    for (int i = 1; i <= Cactus::m; i++) {
        NetworkFlow::add_edge(Cactus::cnt + i, NetworkFlow::t, 1);
    }  // for

    for (int i = 2; i <= Cactus::cnt; i++) {
        NetworkFlow::add_edge(NetworkFlow::s, i, Cactus::cyclesize[i] - 1);

        for (int j = 1; j <= Cactus::m; j++) {
            if (Cactus::colormap[i][j])
                NetworkFlow::add_edge(i, Cactus::cnt + j, 1);
        }  // for
    }      // for

    NetworkFlow::add_edge(NetworkFlow::s, 1, Cactus::cyclesize[1]);
    for (int i = 1; i <= Cactus::m; i++) {
        if (Cactus::colormap[1][i])
            NetworkFlow::add_edge(1, Cactus::cnt + i, 1);
    }  // for

    printf("%d\n", NetworkFlow::dinic());

    return 0;
}  // function main
