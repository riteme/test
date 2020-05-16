#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 1000
#define INF 1'000'000'000'000

struct Edge {
    int u, v;
    i64 c, w;
    Edge *rev;
};

bool mark[NMAX + 10];
vector<Edge*> G[NMAX + 10];

void link(int u, int v, i64 c, i64 w) {
    auto e1 = new Edge{u, v, c, w};
    auto e2 = new Edge{v, u, 0, -w};
    e1->rev = e2;
    e2->rev = e1;
    G[u].push_back(e1);
    G[v].push_back(e2);
}

int N;
i64 dist[NMAX + 10];
Edge *back[NMAX + 10];

void spfa(int s) {
    for (int i = 1; i <= N; i++)
        dist[i] = INF;
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    do {
        int u = q.front();
        q.pop();

        for (auto e : G[u]) {
            int v = e->v;
            if (!mark[v] && e->c > 0 && dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;
                back[v] = e;
                q.push(v);
            }
        }
    } while (!q.empty());
}

i64 mincost = 0;
int maxflow(int s, int t) {
    i64 ret = 0;
    while (true) {
        spfa(s);
        if (dist[t] >= INF)
            break;

        i64 minf = INF;
        for (int x = t; x != s; x = back[x]->u)
            minf = back[x]->c;
        ret += minf;
        for (int x = t; x != s; x = back[x]->u) {
            auto e = back[x];
            e->c -= minf;
            e->rev->c += minf;
            mincost += minf * e->w;
        }
    }

    return ret;
}

int n, m, s, t, ss, tt;

int main() {
    scanf("%d%d",&n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        link(u, n + v, 1, w);
    }

    s = 2 * n + 1;
    t = s + 1;
    ss = t + 1;
    tt = ss + 1;
    N = tt;
    link(t, s, INF, 0);
    link(s, tt, n, 0);
    link(ss, t, n, 0);
    for (int i = 1; i <= n; i++) {
        link(s, i, INF, 0);
        link(n + i, t, INF, 0);
        link(ss, i, 1, 0);
        link(n + i, tt, 1, 0);
    }

    i64 flow = maxflow(ss, tt);
    if (flow == 2 * n)
        printf("%lld\n", mincost);
    else
        puts("NIE");

    return 0;
}