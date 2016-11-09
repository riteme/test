#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 10000
#define LOGN 14
#define MMAX 50000

struct Edge {
    int u, v, w;

    int either(int x) const {
        return u == x ? v : u;
    }

    bool operator<(const Edge &b) const {
        return w > b.w;
    }
};

static int n, m;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int dist[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];
static int minv[NMAX + 10][LOGN + 1];
static bool marked[NMAX + 10];

static int set[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++)
        set[i] = i;
}

inline int find_set(int x) {
    return set[x] == x ? x : set[x] = find_set(set[x]);
}

static void kruskal() {
    sort(edges + 1, edges + m + 1);

    make_set();
    for (int i = 1; i <= m; i++) {
        Edge &e = edges[i];
        int u = find_set(e.u);
        int v = find_set(e.v);

        if (u != v) {
            set[u] = v;

            G[e.u].push_back(&e);
            G[e.v].push_back(&e);
        }
    }
}

static void dfs(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (marked[v])
            continue;

        f[v][0] = x;
        minv[v][0] = e->w;
        dist[v] = dist[x] + 1;
        dfs(v);
    }  // for
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);

    kruskal();

    for (int i = 1; i <= n; i++)
        if (!marked[i])
            dfs(i);

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
            minv[i][j] = min(minv[i][j - 1], minv[f[i][j - 1]][j - 1]);
        }  // for
    }      // for
}

inline int evaluate_lca(int u, int v) {
    if (dist[u] < dist[v])
        swap(u, v);

    int delta = dist[u] - dist[v];
    for (int i = LOGN; i >= 0; i--)
        if (delta & (1 << i))
            u = f[u][i];

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }  // for

    return f[u][0];
}

inline int query(int u, int p) {
    int delta = dist[u] - dist[p];
    int answer = INT_MAX;

    for (int i = LOGN; i >= 0; i--) {
        if (delta & (1 << i)) {
            answer = min(answer, minv[u][i]);
            u = f[u][i];
        }
    }  // for

    return answer;
}

int main() {
    initialize();

    int q;
    scanf("%d", &q);

    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (find_set(u) != find_set(v))
            puts("-1");
        else {
            int lca = evaluate_lca(u, v);
            printf("%d\n", min(query(u, lca), query(v, lca)));
        }
    }  // while

    return 0;
}  // function main
