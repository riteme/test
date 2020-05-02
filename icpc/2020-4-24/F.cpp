#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 2000
#define INF 0x3f3f3f3f

struct Edge {
    int v, c;
    Edge *rev;
};

int s = NMAX + 1, t = NMAX + 2;
static vector<Edge*> G[NMAX + 10];

void link(int u, int v, int c) {
    auto e1 = new Edge{v, c};
    auto e2 = new Edge{u, 0};
    e1->rev = e2;
    e2->rev = e1;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

int lev[NMAX + 10];

void bfs() {
    memset(lev + 1, 0, sizeof(int) * t);
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

int pos[NMAX + 10];

int dfs(int x, int maxf) {
    if (x == t)
        return maxf;

    int cur = 0;
    for (int &i = pos[x]; i < G[x].size(); i++) {
        auto e = G[x][i];
        int v = e->v;
        if (lev[x] + 1 != lev[v])
            continue;

        int flow = min(e->c, maxf - cur);
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
        memset(pos + 1, 0, sizeof(int) * t);
        ret += dfs(s, INF);
    }

    return ret;
}

int n;
i64 a[NMAX + 10];
int f[NMAX + 10];

void solve() {
    // scanf("%d", &n);[
    s = 2 * n + 1;
    t = 2 * n + 2;
    for (int i = 1; i <= t; i++)
        G[i].clear();

    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    for (int i = 1; i <= n; i++) {
        f[i] = 1;

        for (int j = 1; j < i; j++) {
            if (a[j] < a[i])
                f[i] = max(f[i], f[j] + 1);
        }
    }

    int maxlen = 0;
    for (int i = 1; i <= n; i++) {
        maxlen = max(maxlen, f[i]);

        link(i, n + i, 1);
        if (f[i] == 1)
            link(s, i, 1);
        for (int j = 1; j < i; j++)
        if (f[j] + 1 == f[i])
            link(n + j, i, 1);
    }

    for (int i = 1; i <= n; i++)
    if (f[i] == maxlen)
        link(n + i, t, 1);

    int ans = dinic();
    printf("%d\n%d\n", maxlen, ans);
}

int main() {
    while (scanf("%d", &n) != EOF)
        solve();
    return 0;
}