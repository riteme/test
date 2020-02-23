#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 400
#define MMAX 15000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, i64 _w, i64 _c)
        : u(_u), v(_v), w(_w), c(_c) {}

    int u, v;
    i64 w, c;
    Edge *rev;
};

static int n, m;
static vector<Edge*> G[NMAX + 10];

void link(int u, int v, i64 w, i64 c) {
    auto e1 = new Edge(u, v, w, c);
    auto e2 = new Edge(v, u, -w, 0);
    e1->rev = e2;
    e2->rev = e1;

    G[u].push_back(e1);
    G[v].push_back(e2);
}

static i64  d[NMAX + 10], h[NMAX + 10];
static Edge *ed[NMAX + 10];
static bool in[NMAX + 10];

void spfa(int s) {
    for (int i = 1; i <= n; i++)
        h[i] = INF;
    h[s] = 0;

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
        i64 t;

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

int main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        int u, v;
        i64 w, c;
        scanf("%d%d%lld%lld", &u, &v, &c, &w);
        link(u, v, w, c);
    }

    int s = 1, t = n;
    spfa(s);
    i64 flow = 0, cost = 0;
    while (h[t] < INF) {
        for (int i = 1; i <= n; i++)
            h[i] += d[i];

        i64 mi = INF;
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

    printf("%lld %lld\n", flow, cost);
    return 0;
}
