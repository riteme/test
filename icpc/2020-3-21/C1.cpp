#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2010
#define MMAX 20010
#define INF 0x3f3f3f3f

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, int _w, int _c)
        : u(_u), v(_v), w(_w), c(_c) {}

    int u, v;
    int w, c;
    Edge *nxt, *rev;
};

static int n;
static vector<Edge*> G[NMAX + 10];

void link(int u, int v, int w, int c) {
    auto e1 = new Edge(u, v, w, c);
    auto e2 = new Edge(v, u, -w, 0);
    e1->rev = e2;
    e2->rev = e1;

    G[u].push_back(e1);
    G[v].push_back(e2);
}

static int  d[NMAX + 10], h[NMAX + 10];
static Edge *ed[NMAX + 10];
static bool in[NMAX + 10];

void spfa(int s) {
    for (int i = 1; i <= n; i++)
        h[i] = INF;
    h[s] = 0;

    memset(in + 1, 0, n);

    queue<int> q;
    q.push(s);
    in[s] = true;
    do {
        int u = q.front();
        q.pop();

        for (auto e : G[u])
        if (e->c && h[e->v] > h[u] + e->w) {
            h[e->v] = h[u] + e->w;
            ed[e->v] = e;
            if (!in[e->v]) {
                q.push(e->v);
                in[e->v] = true;
            }
        }
    } while (!q.empty());
}

void dijkstra(int s) {
    struct State {
        int u;
        int t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    memset(in + 1, 0, n);
    for (int i = 1; i <= n; i++)
        d[i] = INF;
    d[s] = 0;

    priority_queue<State> q;
    q.push({s, 0});
    do {
        auto _ = q.top();
        q.pop();
        int u = _.u;
        if (in[u])
            continue;
        in[u] = true;

        for (auto e : G[u])
        if (e->c && d[e->v] > d[u] + e->w + h[u] - h[e->v]) {
            d[e->v] = d[u] + e->w + h[u] - h[e->v];
            ed[e->v] = e;
            q.push({e->v, d[e->v]});
        }
    } while (!q.empty());
}

void solve() {
    int _n, m;
    scanf("%d%d", &_n, &m);
    n = _n * 2 + 2;
    for (int i = 1; i <= n; i++) {
        for (auto e : G[i])
            delete e;
        G[i].clear();
    }

    while (m--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        link(u, v + _n, w, 1);
        link(v, u + _n, w, 1);
    }

    int s = n - 1, t = n;
    for (int i = 1; i <= _n; i++) {
        link(s, i, 0, 1);
        link(i + _n, t, 0, 1);
    }

    for (int i = 1; i <= n; i++)
        reverse(G[i].begin(), G[i].end());

    memset(d + 1, 0, sizeof(int) * n);
    spfa(s);
    int flow = 0, cost = 0;
    while (h[t] < INF) {
        for (int i = 1; i <= n; i++)
            h[i] += d[i];

        int mi = INF;
        for (int x = t; x != s; x = ed[x]->u)
            mi = min(mi, ed[x]->c);
        flow += mi;
        cost += mi * h[n];
        for (int x = t; x != s; x = ed[x]->u) {
            ed[x]->c -= mi;
            ed[x]->rev->c += mi;
        }

        dijkstra(s);
    }

    if (flow < _n) puts("NO");
    else printf("%d\n", cost);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        printf("Case %d: ", t);
        solve();
    }
    return 0;
}
