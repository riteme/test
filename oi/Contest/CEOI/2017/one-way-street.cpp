#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, m, q;
static struct Edge {
    int u, v;

    int either(int x) const {
        return u == x ? v : u;
    }
} edge[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static stack<int> stk;
static int dfn[NMAX + 10], low[NMAX + 10], cur;
static int id[NMAX + 10], cnt;
static vector<int> T[NMAX + 10];
static bool root[NMAX + 10];
static int father[NMAX + 10], top[NMAX + 10], depth[NMAX + 10];
static int down[NMAX + 10], up[NMAX + 10];

void bcc(int x, Edge *f) {
    dfn[x] = low[x] = ++cur;
    stk.push(x);

    for (auto e : G[x]) {
        if (e == f)
            continue;

        int v = e->either(x);
        if (!dfn[v])
            bcc(v, e);
        low[x] = min(low[x], low[v]);
    }

    if (dfn[x] == low[x]) {
        cnt++;
        while (true) {
            int u = stk.top();
            stk.pop();
            id[u] = cnt;
            if (u == x)
                break;
        }
    }
}

void dfs(int x, int f) {
    top[x] = 1;
    for (int v : T[x]) {
        if (v == f)
            continue;

        father[v] = x;
        depth[v] = depth[x] + 1;
        dfs(v, x);
        top[x] += top[v];
    }
}

void decompose(int x, int f) {
    int nxt = 0;
    for (int v : T[x]) {
        if (v != f && top[v] > top[nxt])
            nxt = v;
    }

    if (nxt) {
        top[nxt] = top[x];
        decompose(nxt, x);
    }

    for (int v : T[x]) {
        if (v != f && v != nxt) {
            top[v] = v;
            decompose(v, x);
        }
    }
}

inline int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]])
            u = father[top[u]];
        else
            v = father[top[v]];
    }

    return depth[u] < depth[v] ? u : v;
}

void sumup(int x, int f) {
    for (int v : T[x]) {
        if (v == f)
            continue;

        sumup(v, x);
        down[x] += down[v];
        up[x] += up[v];
    }
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        Edge &e = edge[i];
        scanf("%d%d", &e.u, &e.v);
        G[e.u].push_back(&e);
        G[e.v].push_back(&e);
    }
}

int main() {
    initialize();

    for (int u = 1; u <= n; u++) {
        bcc(u, nullptr);
    }

    for (int i = 1; i <= m; i++) {
        Edge &e = edge[i];

        int u = id[e.u], v = id[e.v];
        if (u != v) {
            T[u].push_back(v);
            T[v].push_back(u);
        }
    }

    for (int i = 1; i <= cnt; i++) {
        if (!top[i]) {
            root[i] = true;
            dfs(i, 0);
            top[i] = i;
            decompose(i, 0);
        }
    }

    // for (int i = 1; i <= cnt; i++) {
    //     printf("%d: ", i);
    //     for (int u = 1; u <= n; u++) {
    //         if (id[u] == i)
    //             printf("%d ", u);
    //     }
    //     printf("\n");
    // }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x = id[x];
        y = id[y];

        if (x == y)
            continue;

        int p = lca(x, y);
        up[x]++;
        up[p]--;
        down[y]++;
        down[p]--;
    }

    for (int i = 1; i <= n; i++) {
        if (root[i])
            sumup(i, 0);
    }

    for (int i = 1; i <= m; i++) {
        Edge &e = edge[i];
        int u = id[e.u], v = id[e.v];

        if ((father[u] == v && up[u]) || 
            (father[v] == u && down[v]))
            putchar('R');
        else if ((father[u] == v && down[u]) ||
                 (father[v] == u && up[v]))
            putchar('L');
        else
            putchar('B');
    }

    return 0;
}
