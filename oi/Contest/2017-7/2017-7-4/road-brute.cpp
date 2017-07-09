#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};

struct Pair {
    Pair(int _x, i64 _dis)
        : x(_x), dis(_dis) {}

    int x;
    i64 dis;

    bool operator<(const Pair &b) const {
        return dis > b.dis;
    }
};

static int n, m, q, s, t, lastans;
static int col[NMAX + 10];
static i64 dist[NMAX + 10];
static int fa[NMAX + 10], depth[NMAX + 10];
static int in[NMAX + 10], out[NMAX + 10], cur;
static vector<Edge *> G[NMAX + 10];
static vector<int> D[NMAX + 10], up[NMAX + 10];

void dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    priority_queue<Pair> q;
    q.push(Pair(s, 0));
    while (!q.empty()) {
        Pair u = q.top();
        q.pop();

        if (dist[u.x] != u.dis)
            continue;

        for (size_t i = 0; i < G[u.x].size(); i++) {
            Edge *e = G[u.x][i];
            int v = e->either(u.x);

            if (dist[v] > dist[u.x] + e->w) {
                dist[v] = dist[u.x] + e->w;
                q.push(Pair(v, dist[v]));
            }
        }
    }
}

bool cmp(int a, int b) {
    return col[a] < col[b];
}

void dfs(int u) {
    in[u] = ++cur;

    for (size_t i = 0; i < D[u].size(); i++) {
        int v = D[u][i];

        if (!in[v]) {
            depth[v] = depth[u] + 1;
            fa[v] = u;
            dfs(v);
        } else
            up[v].push_back(u);
    }
            
    out[u] = cur;
}

void build() {
    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->either(u);

            if (dist[u] + e->w == dist[v])
                D[u].push_back(v);
        }

        sort(D[u].begin(), D[u].end(), cmp);
    }

    dfs(s);
}

void initialize() {
    scanf("%d%d%d%d", &n, &m, &s, &t);

    for (int i = 1; i <= n; i++) {
        scanf("%d", col + i);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        if (u == v)
            continue;

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }
}

int main() {
    initialize();
    dijkstra();
    build();
    
    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (t) {
            u ^= lastans;
            v ^= lastans;
        }

        if (in[v] <= in[u] || out[u] < in[v])
            continue;

        int p = v;
        while (fa[p] != u)
            p = fa[p];
        while (v != u) {
            bool ok = false;
            for (size_t i = 0; i < up[v].size() && !ok; i++) {
                int q = up[v][i];

                if (in[q] < in[p] || out[p] < in[q])
                    ok = true;
            }

            if (ok)
                break;

            v = fa[v];
        }

        lastans = depth[v] - depth[u];
        printf("%d\n", lastans);
    }

    return 0;
}
