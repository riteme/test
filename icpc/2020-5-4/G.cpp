#include <cstdio>
#include <cassert>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 300
#define QMAX 100000
#define BASE 1000000000
#define INF 0x3f3f3f3f3f3f3f3f

struct Edge {
    int v;
    i64 c;
    Edge *rev;
};

int n, m, s, t;
i64 w[NMAX + 10];
vector<Edge*> G[NMAX + 10];

void link(int u, int v, i64 c) {
    auto e1 = new Edge{v, c};
    auto e2 = new Edge{u, 0, e1};
    e1->rev = e2;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

int col[NMAX + 10];

void color(int x, int c) {
    if (col[x])
        return;
    col[x] = c;
    for (auto e : G[x]) {
        if (c == 1)
            e->c = INF;
        color(e->v, -c);
    }
}

int lev[NMAX + 10];

void bfs() {
    memset(lev + 1, 0, sizeof(int) * t);
    queue<int> q;
    q.push(s);
    lev[s] = 1;
    do {
        int u = q.front();
        q.pop();
        for (auto e : G[u])
        if (e->c && !lev[e->v]) {
            lev[e->v] = lev[u] + 1;
            q.push(e->v);
        }
    } while (!q.empty());
}

int cur[NMAX + 10];

i64 dfs(int x, i64 maxf = INF) {
    if (x == t)
        return maxf;

    i64 ret = 0;
    for (int &i = cur[x]; i < G[x].size(); i++) {
        auto e = G[x][i];
        int v = e->v;
        if (!e->c || lev[x] + 1 != lev[v])
            continue;

        i64 flow = min(e->c, maxf - ret);
        flow = dfs(v, flow);
        ret += flow;
        e->c -= flow;
        e->rev->c += flow;
        if (ret >= maxf)
            break;
    }

    return ret;
}

i64 dinic() {
    i64 ret = 0;
    while (true) {
        bfs();
        if (!lev[t])
            break;
        memset(cur + 1, 0, sizeof(int) * t);
        ret += dfs(s);
    }

    return ret;
}

bool mark[NMAX + 10];

void search(int x) {
    if (mark[x])
        return;
    mark[x] = true;
    for (auto e : G[x])
    if (e->c)
        search(e->v);
}

int seq[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    s = n + 1;
    t = n + 2;
    for (int i = 1; i <= n; i++)
        scanf("%lld", w + i);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        link(u, v, 0);
    }

    for (int i = 1; i <= n; i++) if (!col[i])
        color(i, 1);
    for (int i = 1; i <= t; i++)
    for (auto e : G[i])
        assert(e->c || e->rev->c);

    for (int i = 1; i <= n; i++) {
        i64 c = BASE + QMAX - w[i];
        if (col[i] == 1)
            link(s, i, c);
        else
            link(i, t, c);
    }

    dinic();

    search(s);
    int cnt = 0;
    for (int v = 1; v <= n; v++)
    if ((mark[v] && col[v] == -1) ||
        (!mark[v] && col[v] == 1))
        seq[cnt++] = v;

    i64 ans = 0;
    for (int i = 0; i < cnt; i++)
        ans += w[seq[i]];

    printf("%lld %d\n", ans, cnt);
    for (int i = 0; i < cnt; i++)
        printf("%d ", seq[i]);
    puts("");

    return 0;
}