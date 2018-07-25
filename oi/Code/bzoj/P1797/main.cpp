/**
 * 考虑到最小割只会割掉满流边，因为根据最大流最小割定理
 * 如果割了未满流的边，那么割的权值会比最大流大，不会称为最小割
 * 因此，未满流的边对我们来说是没用的
 * 是不是所有的满流边都有最小割？
 * 不是的，因为可能有下面的情况：
 *       / 3 \
 * 1 - 2 - 4 - 6 - 7
 *       \ 5 /
 * 中间的三条路径可以任选一条来增广，从而变成满流边
 * 解决的方案就是，将残留网络缩点，然后去掉自环，剩下的边就都可以成为割边
 * 如何一定被割？
 * 只有它连接s和t的强连通分量时才会被割
 */

#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#define NMAX 4000
#define MMAX 60000

struct Edge {
    Edge(int _id, int v, int w) : id(_id), to(v), capacity(w) {}

    int id;
    int to;
    int capacity;
    Edge *reverse_edge;
};  // struct Edge

static int n, m, s, t;
static vector<Edge *> G[NMAX + 10];
static int bound[MMAX + 10];

static int level[NMAX + 10];
static bool marked[NMAX + 10];

void bfs() {
    memset(level, 0, sizeof(level));
    memset(marked, 0, sizeof(marked));

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

int dfs(int x, int maxflow) {
    if (x == t)
        return maxflow;

    int current = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (level[v] != level[x] + 1 || e->capacity == 0)
            continue;

        int flow = min(maxflow - current, e->capacity);
        flow = dfs(v, flow);
        e->capacity -= flow;
        e->reverse_edge->capacity += flow;
        current += flow;

        if (current == maxflow)
            break;
    }  // for

    return current;
}

int dinic() {
    int ret = 0;

    while (true) {
        bfs();

        if (!marked[t])
            break;

        ret += dfs(s, INT_MAX);
    }  // while

    return ret;
}

static stack<int> stk;
static int timestamp;
static int dfn[NMAX + 10];
static int low[NMAX + 10];
static int id[NMAX + 10];

void scc(int x) {
    low[x] = dfn[x] = ++timestamp;
    stk.push(x);

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (e->capacity == 0 || marked[v])
            continue;

        if (!dfn[v])
            scc(v);
        if (!marked[v])
            low[x] = min(low[x], low[v]);
    }  // for

    if (low[x] == dfn[x]) {
        while (true) {
            int u = stk.top();
            stk.pop();

            marked[u] = true;
            id[u] = x;

            if (u == x)
                break;
        }  // while
    }
}

void initialize() {
    scanf("%d%d%d%d", &n, &m, &s, &t);

    for (int i = 1; i <= m; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        bound[i] = c;
        Edge *e = new Edge(i, v, c);
        Edge *re = new Edge(0, u, 0);
        e->reverse_edge = re;
        re->reverse_edge = e;
        G[u].push_back(e);
        G[v].push_back(re);
    }  // for
}

static int ans1[MMAX + 10];
static int ans2[MMAX + 10];

int main() {
    initialize();

    dinic();

    memset(marked, 0, sizeof(marked));
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            scc(i);
    }  // for

    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->to;

            if (e->id && e->capacity == 0) {
                if (id[u] != id[v]) {
                    ans1[e->id] = 1;

                    if ((id[u] == id[s] && id[v] == id[t]) ||
                        (id[u] == id[t] && id[v] == id[s]))
                        ans2[e->id] = 1;
                }
            }
        }  // for
    }      // for

    for (int i = 1; i <= m; i++) {
        printf("%d %d\n", ans1[i], ans2[i]);
    }  // for

    return 0;
}  // function main
