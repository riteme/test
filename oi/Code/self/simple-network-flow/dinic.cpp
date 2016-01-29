#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200
#define MMAX 1000

struct Edge {
    int u;
    int v;
    int w;
    Edge *reverse_edge;
};  // struct Edge

static int n;
static int m;
static int level[NMAX + 10];
static Edge edges[2 * (MMAX + 10)];
static vector<Edge *> G[NMAX + 10];
static bool marked[NMAX + 10];
static int answer;

void bfs() {
    for (int i = 1; i <= n; i++) {
        level[i] = INT_MAX;
    }  // for
    level[1] = 0;

    memset(marked, false, sizeof(marked));
    marked[1] = true;
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (e->w == 0) {
                continue;
            }

            if (!marked[v]) {
                level[v] = level[u] + 1;
                marked[v] = true;
                q.push(v);
            }
        }  // for
    }      // while
}

int dfs(int u, int maxflow, int t) {
    if (u == t) {
        return maxflow;
    }

    int current = 0;  // 表示当前已经增广的流
    for (int i = 0; i < G[u].size(); i++) {
        Edge *e = G[u][i];
        int v = e->v;

        if (level[u] + 1 != level[v] or e->w == 0) {
            continue;
        }

        int flow =
            min(maxflow - current, e->w);  // 减去当前已获得的流确保不会超出限制
        flow = dfs(v, flow, t);
        e->w -= flow;
        e->reverse_edge->w += flow;
        current += flow;

        if (current == maxflow) {
            return current;  // 如果流量已到上限，则不再继续增广
        }
    }  // for

    return current;
}

void dinic() {
    int s = 1;
    int t = n;

    while (true) {
        bfs();

        if (level[n] == INT_MAX) {
            return;
        }

        answer += dfs(s, INT_MAX, t);
    }  // while
}

void initialize() {
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }  // for

    for (int i = 1; i <= m; i++) {
        int u, v;
        int w;
        scanf("%d%d%d", &u, &v, &w);

        Edge &e = edges[i];
        Edge &re = edges[i + m];
        e.u = u;
        e.v = v;
        e.w = w;
        e.reverse_edge = &re;

        re.u = v;
        re.v = u;
        re.w = 0;
        re.reverse_edge = &e;

        G[u].push_back(&e);
        G[v].push_back(&re);
    }  // for

    answer = 0;
}

int main() {
    freopen("dinic.in", "r", stdin);
    freopen("dinic.out", "w", stdout);

    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();

        dinic();

        printf("%d\n", answer);
    }  // while

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
