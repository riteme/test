// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100000
#define MMAX 300000
#define KMAX 20

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, i64 _w) : u(_u), v(_v), w(_w) {}

    int u, v;
    i64 w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

bool cmp(const Edge *a, const Edge *b) {
    return a->w < b->w;
}

struct UnionFind {
    int set[NMAX + 10];

    void reset(int n) {
        memset(set, 0, sizeof(int) * (n + 1));
    }

    int find(int x) {
        return set[x] ? set[x] = find(set[x]) : x;
    }

    void link(int x, int y) {
        set[find(x)] = find(y);
    }

    void qlink(int x, int y) {
        set[x] = y;
    }
};  // struct UnionFind

static int n, m, k;
static Edge *edges[MMAX + 10];
static Edge *non[KMAX + 10];
static i64 c[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < m; i++) {
        int u, v;
        i64 w;
        scanf("%d%d%lld", &u, &v, &w);
        edges[i] = new Edge(u, v, w);
    }  // for
    sort(edges, edges + m, cmp);

    for (int i = 0; i < k; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        non[i] = new Edge(u, v, 0);
    }  // for

    for (int i = 1; i <= n; i++) {
        scanf("%lld", c + i);
    }  // for
}

static UnionFind uf;
static int id[NMAX + 10];
static i64 val[KMAX + 10];

void reduce() {
    uf.reset(n);
    for (int i = 0; i < k; i++) {
        uf.link(non[i]->u, non[i]->v);
    }  // for

    for (int i = 0; i < m; i++) {
        Edge *e = edges[i];
        int u = uf.find(e->u);
        int v = uf.find(e->v);

        if (u != v) {
            uf.qlink(u, v);
            e->w *= -1;
        }
    }  // for

    uf.reset(n);
    for (int i = 0; i < m; i++) {
        Edge *e = edges[i];
        if (e->w < 0)
            uf.link(e->u, e->v);
    }  // for

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int t = uf.find(i);

        if (!id[t])
            id[t] = ++cnt;
        val[id[t]] += c[i];
    }  // for
    n = cnt;

    for (int i = 0; i < m; i++) {
        Edge *e = edges[i];
        e->u = id[uf.find(e->u)];
        e->v = id[uf.find(e->v)];
    }  // for

    for (int i = 0; i < k; i++) {
        Edge *e = non[i];
        e->u = id[uf.find(e->u)];
        e->v = id[uf.find(e->v)];
    }  // for
}

void contract() {
    uf.reset(n);
    int pos = 0;
    for (int i = 0; i < m; i++) {
        Edge *e = edges[i];
        int u = uf.find(e->u);
        int v = uf.find(e->v);

        if (u != v) {
            uf.qlink(u, v);
            edges[pos++] = edges[i];
        }
    }  // for
    m = pos;
}

static vector<Edge *> G[KMAX + 10];

bool setup(int state) {
    uf.reset(n);
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }  // for

    for (int i = 0; i < k; i++) {
        if ((state >> i) & 1) {
            Edge *e = non[i];
            int u = uf.find(e->u);
            int v = uf.find(e->v);

            if (u == v)
                return false;

            uf.qlink(u, v);
            G[e->u].push_back(e);
            G[e->v].push_back(e);
        }
    }  // for

    for (int i = 0; i < m; i++) {
        Edge *e = edges[i];
        int u = uf.find(e->u);
        int v = uf.find(e->v);

        if (u != v) {
            uf.qlink(u, v);
            G[e->u].push_back(e);
            G[e->v].push_back(e);
        }
    }  // for

    return true;
}

static int father[KMAX + 10];
static int depth[KMAX + 10];
static i64 size[KMAX + 10];
static i64 dist[KMAX + 10];

void dfs(int x, int f) {
    size[x] = val[x];
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (v == f)
            continue;

        father[v] = x;
        depth[v] = depth[x] + 1;
        dist[v] = LLONG_MAX;

        dfs(v, x);

        size[x] += size[v];
    }  // for
}

i64 evaluate(int state) {
    if (!setup(state))
        return 0;
    depth[1] = 0;
    father[1] = 0;
    dfs(1, 0);

    for (int i = 0; i < m; i++) {
        Edge *e = edges[i];
        int u = e->u, v = e->v;

        if (depth[u] < depth[v])
            swap(u, v);

        while (depth[u] > depth[v]) {
            dist[u] = min(dist[u], e->w);
            u = father[u];
        }  // while

        while (u != v) {
            dist[u] = min(dist[u], e->w);
            dist[v] = min(dist[v], e->w);
            u = father[u];
            v = father[v];
        }  // while
    }      // for

    i64 ret = 0;
    for (int i = 0; i < k; i++) {
        if ((state >> i) & 1) {
            Edge *e = non[i];
            int down = depth[e->u] > depth[e->v] ? e->u : e->v;

            assert(dist[down] < LLONG_MAX);
            ret += size[down] * dist[down];
        }
    }  // for

    return ret;
}

int main() {
#ifdef USE_FILE_IO
    freopen("toll.in", "r", stdin);
    freopen("toll.out", "w", stdout);
#endif  // IFDEF USE_FILE_IO

    initialize();
    reduce();
    contract();

    i64 answer = 0;
    for (int s = 1; s < (1 << k); s++) {
        answer = max(answer, evaluate(s));
    }  // for
    printf("%lld\n", answer);

    return 0;
}  // function main
