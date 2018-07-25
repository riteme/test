// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 200000
#define LOGN 18
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

struct Edge {
    Edge() {}
    Edge(int _u, int _v, i64 _w)
        : u(_u), v(_v), w(_w) {}

    int u, v;
    i64 w;

    int either(int x) {
        return u == x ? v : u;
    }

    bool operator<(const Edge &b) const {
        return w < b.w;
    }
};

static int n, m, q;
static char mark[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

void initialize() {
    scanf("%d%d%s", &n, &m, mark + 1);

    int u, v;
    i64 w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%lld", &u, &v, &w);
        
        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }
}

struct State {
    int u;
    i64 d;

    bool operator<(const State &b) const {
        return d > b.d;
    }
};

static int src[NMAX + 10];
static i64 dist[NMAX + 10];

void spfa_multisource() {
    memset(dist, 0x3f, sizeof(dist));

    priority_queue<State> q;
    for (int i = 1; i <= n; i++) {
        if (mark[i] == '1') {
            q.push({i, 0});
            src[i] = i;
            dist[i] = 0;
        }
    }

    while (!q.empty()) {
        State s = q.top();
        q.pop();

        if (s.d != dist[s.u])
            continue;
        
        int u = s.u;
        for (auto e : G[u]) {
            int v = e->either(u);

            if (dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;
                src[v] = src[u];
                q.push({v, dist[v]});
            }
        }
    }
}

static Edge edge[MMAX + 10];
static int father[NMAX + 10];
static vector<Edge *> T[NMAX + 10];
static int depth[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];
static i64 maxv[LOGN + 1][NMAX + 10];

inline int find(int x) {
    return father[x] ? father[x] = find(father[x]) : x;
}

inline void link(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y)
        father[x] = y;
}

void dfs(int u, int fa) {
    for (auto e : T[u]) {
        int v = e->either(u);

        if (v == fa)
            continue;

        f[0][v] = u;
        maxv[0][v] = e->w;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

void generate_spanning_tree() {
    spfa_multisource();

    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        for (auto e : G[u]) {
            int v = e->either(u);

            if (u < v)
                continue;

            cnt++;
            edge[cnt] = {src[u], src[v], dist[u] + dist[v] + e->w};
        }
    }

    sort(edge + 1, edge + cnt + 1);

    for (int i = 1; i <= cnt; i++) {
        Edge &e = edge[i];
        
        if (find(e.u) != find(e.v)) {
            T[e.u].push_back(&e);
            T[e.v].push_back(&e);
            link(e.u, e.v);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (mark[i] == '1') {
            dfs(i, 0);
            break;
        }
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
            maxv[j][i] = max(maxv[j - 1][i], maxv[j - 1][f[j - 1][i]]);
        }
    }
}

i64 query(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    i64 ret = 0;
    int delta = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1) {
            ret = max(ret, maxv[i][u]);
            u = f[i][u];
        }
    }

    if (u == v)
        return ret;

    for (int i = LOGN; i >= 0; i--) {
        if (f[i][u] != f[i][v]) {
            ret = max(ret, max(maxv[i][u], maxv[i][v]));
            u = f[i][u];
            v = f[i][v];
        }
    }

    return max(ret, max(maxv[0][u], maxv[0][v]));
}

int main() {
#ifdef USE_FILE_IO
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
#endif
    initialize();
    generate_spanning_tree();

    scanf("%d", &q);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%lld\n", query(u, v));
    }

    return 0;
}
