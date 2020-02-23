#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 500
#define INF 0x3f3f3f3f

struct Edge {
    Edge(int _v, int _c) : v(_v), c(_c) {}

    int v, c;
    Edge *rev;
};

int n, m, p, s, t;
bool cov[NMAX + 10];
vector<Edge*> G[NMAX + 10];

void link(int u, int v, int c) {
    auto e1 = new Edge(v, c);
    auto e2 = new Edge(u, 0);
    e1->rev = e2;
    e2->rev = e1;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

int lev[NMAX + 10];
int cur[NMAX + 10];

bool bfs() {
    memset(lev, 0, sizeof(lev));
    lev[s] = 1;
    queue<int> q;
    q.push(s);
    do {
        int u = q.front();
        q.pop();
        for (auto e : G[u])
        if (e->c && !lev[e->v]) {
            lev[e->v] = lev[u] + 1;
            q.push(e->v);
        }
    } while (!q.empty());
    return lev[t];
}

int dfs(int x, int maxf) {
    if (x == t)
        return maxf;
    int ret = 0;
    for (int &i = cur[x]; i < G[x].size(); i++) {
        auto e = G[x][i];
        int v = e->v;
        if (!e->c || lev[x] + 1 != lev[v])
            continue;
        int flow = min(maxf - ret, e->c);
        flow = dfs(v, flow);
        ret += flow;
        e->c -= flow;
        e->rev->c += flow;
        if (ret >= maxf)
            break;
    }
    return ret;
}

int dinic() {
    int ret = 0;
    while (bfs()) {
        memset(cur, 0, sizeof(cur));
        ret += dfs(s, INF);
    }
    return ret;
}

int main() {
    scanf("%d%d%d", &n, &m, &p);
    s = n + m + p + 1;
    t = s + 1;

    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        scanf("%d", &cnt);
        link(i, t, 1);
        for (int j = 0; j < cnt; j++) {
            int v;
            scanf("%d", &v);
            link(n + v, i, 1);
        }
    }

    for (int i = 1; i <= p; i++) {
        int cnt, r;
        scanf("%d", &cnt);
        for (int j = 0; j < cnt; j++) {
            int v;
            scanf("%d", &v);
            link(n + m + i, n + v, 1);
            cov[v] = true;
        }
        scanf("%d", &r);
        link(s, n + m + i, r);
    }

    for (int i = 1; i <= m; i++)
        if (!cov[i]) link(s, n + i, 1);

    printf("%d\n", dinic());
    return 0;
}
