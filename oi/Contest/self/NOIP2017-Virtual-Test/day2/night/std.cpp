// #define NDEBUG
// #define USE_FILE_IO

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1500000
#define MMAX 2000000
#define QMAX 1000000

static int n, m, q, cnt;
static vector<int> G[NMAX + 10], T[NMAX + 10];
static struct Pair {
    int u, v, p;
} query[QMAX + 10];

static int id[NMAX + 10];
static int in[NMAX + 10], out[NMAX + 10];
static int fa[NMAX + 10];
static vector<Pair *> queue[NMAX + 10];

inline int find(int u) {
    return fa[u] ? fa[u] = find(fa[u]) : u;
}

inline void link(int u, int v) {
    u = find(u);
    v = find(v);

    if (u != v)
        fa[u] = v;
}

#define IS_BLOCK(x) (x + cnt > n)

void bcc(int u, int f = 0) {
    static stack<Pair> stk;
    static bool marked[NMAX + 10];
    static int dfn[NMAX + 10], low[NMAX + 10], cur;
    dfn[u] = low[u] = ++cur;

    for (int v : G[u]) {
        if (v == f)
            continue;

        if (dfn[u] && !marked[u])
            low[u] = min(low[u], dfn[v]);
        else {
            stk.push({u, v});
            bcc(v, u);
            low[u] = min(low[u], low[v]);

            if (low[u] > dfn[u]) {
                T[u].push_back(v);
                T[v].push_back(u);
            }
        }
    }

    if (low[u] != dfn[u])
        return;

    cnt++;
    for (; !stk.empty() && low[stk.top().u] == dfn[u]; stk.pop()) {
        Pair p = stk.top();
        id[p.u] = id[p.v] = cnt;
    }
}

void lca(int u) {
}

void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);

        if (u == v)
            continue;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= q; i++) {
        Query &instance = query[i];
        scanf("%d%d", &instance.u, &instance.v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            bcc(1);
    }

    for (int u = 1; u <= n; u++) {
        if (id[u]) {
            int v = n + id[u];
            T[u].push_back(v);
            T[v].push_back(u);
        }
    }

    n += cnt;
}

int main() {
#ifdef USE_FILE_IO
    freopen("night.in", "r", stdin);
    freopen("night.out", "w", stdout);
#endif
    initialize();

    return 0;
}
