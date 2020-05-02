#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define INF 0x3f3f3f3f

struct Edge {
    int v, c;
    Edge *rev;
};

int n, m, s, t, ans;
vector<Edge*> G[NMAX];

void link(int u, int v, int c) {
    Edge *e1 = new Edge{v, c};
    Edge *e2 = new Edge{u, 0};
    e1->rev = e2;
    e2->rev = e1;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

void initialize() {
    scanf("%d%d", &m, &n);
    s = n + m + 1;
    t = s + 1;
    for (int i = 1; i <= t; i++)
        G[i].clear();

    for (int i = 1; i <= m; i++) {
        int c;
        scanf("%d", &c);
        link(n + i, t, c);
    }

    ans = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        ans += a;
        link(s, i, a);
    }

    for (int u = 1; u <= n; u++) {
        int cnt;
        scanf("%d", &cnt);
        while (cnt--) {
            int v;
            scanf("%d", &v);
            link(u, n + v, INF);
        }
    }
}

int lev[NMAX], idx[NMAX];

void bfs() {
    memset(lev + 1, 0, sizeof(int) * t);
    lev[s] = 1;
    queue<int> q;
    q.push(s);
    do {
        int u = q.front();
        q.pop();

        for (auto e : G[u]) if (e->c && !lev[e->v]) {
            lev[e->v] = lev[u] + 1;
            q.push(e->v);
        }
    } while (!q.empty());
}

int dfs(int x, int maxf = INF) {
    if (x == t)
        return maxf;

    int cur = 0;
    for (int &i = idx[x]; i < G[x].size(); i++) {
        auto e = G[x][i];
        int v = e->v;
        if (lev[x] + 1 != lev[v])
            continue;

        int flow = min(maxf - cur, e->c);
        flow = dfs(v, flow);
        cur += flow;
        e->c -= flow;
        e->rev->c += flow;
        if (cur >= maxf)
            break;
    }

    return cur;
}

int dinic() {
    int ret = 0;
    while (true) {
        bfs();
        if (!lev[t])
            break;

        memset(idx + 1, 0, sizeof(int) * t);
        ret += dfs(s);
    }

    return ret;
}

int main() {
    initialize();
    printf("%d", ans - dinic());
    return 0;
}