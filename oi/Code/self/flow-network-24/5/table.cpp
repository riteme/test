/**
 * 圆桌问题
 * 简单最大流：
 *     源点到每个单位的容量为单位的人数
 *     每个单位只能有一个人坐一张桌子，故单位到每个桌子的容量为1
 *     同理，按照每个桌子的最大人数向汇点连边
 */

#include <cstdio>
#include <cstring>
#include <climits>
#include <cassert>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NO_SOLUTION "No Solution!"

struct Edge {
    int u;
    int v;
    int w;
    Edge *reverse_edge;
};  // struct Edge

static int m;
static int n;
static int cnt;
static int s, t;
static vector<vector<Edge *>> G;
static vector<int> level;
static vector<bool> marked;

inline void add_edge(int u, int v, int w) {
    Edge *e = new Edge();
    Edge *re = new Edge();

    e->u = u;
    e->v = v;
    e->w = w;
    e->reverse_edge = re;

    re->u = v;
    re->v = u;
    re->w = 0;
    re->reverse_edge = e;

    G[e->u].push_back(e);
    G[re->u].push_back(re);
}

void initialize() {
    scanf("%d%d", &m, &n);

    G.resize(m + n + 10);
    level.resize(m + n + 10);
    marked.resize(m + n + 10);

    cnt = 0;
    s = 0;
    t = m + n + 1;

    for (int i = 1; i <= m; i++) {
        int a;
        scanf("%d", &a);

        add_edge(s, i, a);
        cnt += a;
    }  // for

    for (int i = m + 1; i <= m + n; i++) {
        int a;
        scanf("%d", &a);

        add_edge(i, t, a);
    }  // for

    for (int i = 1; i <= m; i++) {
        for (int j = m + 1; j <= m + n; j++) {
            add_edge(i, j, 1);
        }  // for
    }      // for
}

void bfs() {
    for (auto &e : level) {
        e = INT_MAX;
    }  // foreach in level

    for (int i = 0; i < marked.size(); i++) {
        marked[i] = false;
    }  // for

    queue<int> q;
    q.push(s);
    marked[s] = true;
    level[s] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (!marked[v] and e->w != 0) {
                marked[v] = true;
                level[v] = level[u] + 1;

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

        int flow = min(maxflow - current, e->w);
        flow = dfs(v, flow, t);
        e->w -= flow;
        e->reverse_edge->w += flow;
        current += flow;

        if (current >= maxflow) {
            return maxflow;
        }
    }  // for

    return current;
}

void dinic() {
    while (true) {
        bfs();

        if (level[t] == INT_MAX) {
            return;
        }

        dfs(s, INT_MAX, t);
    }  // while
}

int main() {
    freopen("table.in", "r", stdin);
    freopen("table.out", "w", stdout);
    initialize();

    dinic();

    int people_count = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            if (G[i][j]->v == s) {
                people_count += G[i][j]->w;
            }
        }  // for
    }      // for

    if (people_count < cnt) {
        printf("0");
    } else {
        printf("1\n");

        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < G[i].size(); j++) {
                Edge *e = G[i][j];

                if (e->w == 0) {
                    printf("%d ", e->v - m);
                }
            }  // for

            printf("\n");
        }  // for
    }

    fcloseall();
    return 0;
}  // function main
