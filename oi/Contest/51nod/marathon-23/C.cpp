#pragma comment(linker, "/STACK:10240000,10240000")

#include <cstdio>
#include <cstring>

#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 400000

static int n, m, q, s;
static int a[NMAX + 10];
static vector<int> G[NMAX + 10];
static vector<int> T[NMAX + 10];
static int deg[NMAX + 10];

static stack<int> stk;
static int timestamp, cnt;
static bool marked[NMAX + 10];
static int dfn[NMAX + 10];
static int low[NMAX + 10];
static int id[NMAX + 10];
static int maxv[NMAX + 10][2];

void update(int u, int val) {
    if (val == maxv[u][0] || val == maxv[u][1])
        return;
    if (val > maxv[u][0]) {
        maxv[u][1] = maxv[u][0];
        maxv[u][0] = val;
    } else if (val > maxv[u][1])
        maxv[u][1] = val;
}

void scc(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk.push(u);

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (marked[v])
            continue;
        else if (!dfn[v]) {
            scc(v);
            low[u] = min(low[u], low[v]);
        } else
            low[u] = min(low[u], dfn[v]);
    }

    if (dfn[u] == low[u]) {
        cnt++;
        while (stk.top() != u) {
            int x = stk.top();
            stk.pop();
            id[x] = cnt;
            marked[x] = true;
            update(cnt, a[x]);
        }

        stk.pop();
        id[u] = cnt;
        marked[u] = true;
        update(cnt, a[u]);
    }
}

static int topo[NMAX + 10];

void dfs(int u) {
    marked[u] = true;

    for (size_t i = 0; i < T[u].size(); i++) {
        int v = T[u][i];

        if (!marked[v])
            dfs(v);
    }
}

void topological_sort() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (deg[u] == 0)
            q.push(u);
    }

    int pos = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo[pos++] = u;

        for (size_t i = 0; i < T[u].size(); i++) {
            int v = T[u][i];

            deg[v]--;
            
            if (deg[v] == 0)
                q.push(v);
        }
    }
}

void initialize() {
    scanf("%d%d%d%d", &n, &m, &q, &s);

    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }

    for (int u = 1; u <= n; u++) {
        if (!dfn[u])
            scc(u);
    }

    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            
            if (id[u] == id[v])
                continue;

            T[id[u]].push_back(id[v]);
            deg[id[v]]++;
        }
    }

    n = cnt;
    topological_sort();
}

int main() {
    initialize();

    for (int p = 1; p <= n; p++) {
        int u = topo[p];
        for (size_t i = 0; i < T[u].size(); i++) {
            int v = T[u][i];
            update(v, maxv[u][0]);
            update(v, maxv[u][1]);
        }
    }

    memset(marked, 0, sizeof(marked));
    dfs(id[s]);

    while (q--) {
        int u;
        scanf("%d", &u);
        u = id[u];
        printf("%d ", marked[u] && maxv[u][1] ? maxv[u][1] : -1);
    }

    printf("\n");

    return 0;
}
