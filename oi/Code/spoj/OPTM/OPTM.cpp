// #define DEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 500
#define MMAX 20000
#define INFTY 1000000000

struct Edge {
    int v, c, nxt;
};

static int n, m, K, cnt, s, t;
static bool has[NMAX + 10];
static int val[NMAX + 10];
static int head[NMAX + 10];
static int cpy[NMAX + 10];
static Edge edge[MMAX + 10];

void restore() {
    for (int i = 2; i <= cnt; i += 2) {
        edge[i].c += edge[i ^ 1].c;
        edge[i ^ 1].c = 0;
    }
}

void add_edge(int u, int v, int c) {
    cnt += 2;
    edge[cnt - 1] = {v, c, head[u]};
    edge[cnt] = {u, 0, head[v]};
    head[u] = cnt - 1;
    head[v] = cnt;
}

void initialize() {
    scanf("%d%d", &n, &m);

    cnt = 1;
    s = n + 1;
    t = s + 1;
    memset(head, 0, sizeof(head));

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        add_edge(u, v, 1);
        add_edge(v, u, 1);
    }

    memcpy(cpy, head, sizeof(cpy));
    memset(has, 0, sizeof(has));
    memset(val, 0, sizeof(val));
    
    scanf("%d", &K);

    for (int i = 0; i < K; i++) {
        scanf("%d%d", &u, &v);
        has[u] = true;
        val[u] = v;
    }
}

static int level[NMAX + 10];
static int pos[NMAX + 10];

void bfs() {
    memset(level, 0, sizeof(level));

    queue<int> q;
    q.push(s);
    level[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i; i = edge[i].nxt) {
            Edge &e = edge[i];
            int v = e.v;

            if (level[v] || e.c == 0)
                continue;

            level[v] = level[u] + 1;
            q.push(v);
        }
    }
}

int dfs(int u, int maxflow) {
    if (u == t)
        return maxflow;

    int cur = 0;
    for (int &i = pos[u]; i; i = edge[i].nxt) {
        Edge &e = edge[i];
        int v = e.v;

        if (level[u] + 1 != level[v] || e.c == 0)
            continue;

        int flow = min(maxflow - cur, e.c);
        flow = dfs(v, flow);
        cur += flow;
        e.c -= flow;
        edge[i ^ 1].c += flow;

        if (cur == maxflow)
            break;
    }

    return cur;
}

void dinic() {
    restore();

    while (true) {
        bfs();

        if (!level[t])
            break;

        memcpy(pos, head, sizeof(pos));
        dfs(s, INT_MAX);
    }
}

static bool marked[NMAX + 10];

void mark(int u, int mask) {
    marked[u] = true;

    if (u <= n)
        val[u] |= mask;

    for (int i = head[u]; i; i = edge[i].nxt) {
        Edge &e = edge[i];
        int v = e.v;

        if (marked[v] || e.c == 0)
            continue;

        mark(v, mask);
    }
}

int main() {
    // freopen("data.in", "r", stdin);
    int ca;
    scanf("%d", &ca);

    while (ca--) {
        initialize();

        int backup = cnt;
        for (int i = 0; i <= 30; i++) {
            memcpy(head, cpy, sizeof(head));
            for (int j = 1; j <= n; j++) {
                if (has[j]) {
                    if ((val[j] >> i) & 1)
                        add_edge(s, j, INFTY);
                    else
                        add_edge(j, t, INFTY);
                }
            }

            if (!head[t] && head[s]) {
                for (int j = 1; j <= n; j++) {
                    val[j] |= 1 << i;
                }
            } else {
                dinic();

                memset(marked, 0, sizeof(marked));
                mark(s, 1 << i);
            }

            cnt = backup;
        }

        for (int i = 1; i <= n; i++) {
            printf("%d\n", val[i]);
        }
    }

    return 0;
}
