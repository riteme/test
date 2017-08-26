#define USE_FILE_IO

#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w), c(0), mark(false) {}

    int u, v, w, c;
    bool mark;

    int either(int x) {
        return u == x ? v : u;
    }
};

typedef pair<int, int> IntPair;

static int n, m;
static set<IntPair> h;
static vector<Edge *> G[NMAX + 10], N[NMAX + 10];
static bool del[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
        h.insert(IntPair(u, v));
        h.insert(IntPair(v, u));
    }
}

Edge *walk(int u, int f) {
    Edge *ret = NULL;

    for (auto e : G[u]) {
        int v = e->either(u);

        if (v == f)
            continue;
        if (!del[v])
            return new Edge(0, v, e->w);

        ret = walk(v, u);
        ret->w += e->w;
        ret->u = u;
        ret->c++;
    }

    return ret;
}

static int ans = INT_MAX, start;
static bool marked[NMAX + 10];

void dfs(int u, int s, int len) {
    if (s >= ans)
        return;
    if (u == start && len == n) {
        ans = s;
        return;
    }
    if (marked[u])
        return;

    marked[u] = true;

    for (auto e : N[u]) {
        if (e->mark)
            continue;

        int v = e->either(u);
        e->mark = true;
        dfs(v, s + e->w, len + e->c + 1);
        e->mark = false;
    }

    marked[u] = false;
}

int main() {
#ifdef USE_FILE_IO
    freopen("run.in", "r", stdin);
    freopen("run.out", "w", stdout);
#endif
    initialize();

    for (int u = 1; u <= n; u++) {
        if (G[u].size() != 2)
            continue;
        del[u] = !h.count(
            IntPair(G[u][0]->either(u), G[u][1]->either(u))
        );
    }

    for (int u = 1; u <= n; u++) {
        if (del[u])
            continue;

        for (auto e : G[u]) {
            int v = e->either(u);

            if (del[v]) {
                Edge *ne = walk(v, u);
                
                if (u < ne->v)
                    continue;

                ne->u = u;
                ne->w += e->w;
                ne->c++;
                N[u].push_back(ne);
                N[ne->v].push_back(ne);
            } else
                N[u].push_back(e);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (N[i].empty())
            continue;

        start = i;
        dfs(start, 0, 0);
        break;
    }

    printf("%d\n", ans);

    return 0;
}

