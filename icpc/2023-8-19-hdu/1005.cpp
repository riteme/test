#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 600;

int n, m;
bool c[NMAX + 10];
vector<int> G[NMAX + 10];
int pa[NMAX + 10];

int find(int x) {
    return pa[x] ? pa[x] = find(pa[x]) : x;
}

int dfn[NMAX + 10], cnt;
int g[NMAX + 10];

bool dfs(int u) {
    dfn[u] = ++cnt;
    for (int v : G[u]) {
        v = find(v);
        if (!c[v])
            continue;
        if (dfn[v] && dfn[v] < dfn[u]) {
            int x = v;
            do {
                pa[x] = u;
                x = g[x];
            } while (x != u);
            return true;
        }
        if (dfn[v])
            continue;
        g[u] = v;
        if (dfs(v))
            return true;
    }
    return false;
}

void solve() {
    scanf("%d%d", &n, &m);
    for (int u = 1; u <= n; u++) {
        c[u] = true;
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            int v;
            scanf("%d", &v);
            v += n + 1;
            G[u].push_back(v);
        }
    }
    for (int u = n + 1; u <= n + m; u++) {
        c[u] = false;
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            int v;
            scanf("%d", &v);
            v += 1;
            G[u].push_back(v);
        }
    }
    n += m;
    memset(pa + 1, 0, sizeof(int) * n);

    bool any;
    do {
        any = false;
        for (int u = 1; u <= n; u++) {
            if (pa[u] || c[u])
                continue;
            int p = 0;
            for (int v : G[u]) {
                v = find(v);
                if (p == 0)
                    p = v;
                else if (p > 0 && p != v)
                    p = -1;
            }
            if (p > 0) {
                pa[u] = p;
                any = true;
            }
        }

        for (int i = 1; i <= n; i++) {
            dfn[i] = 0;
        }
        for (int u = 1; u <= n; u++) {
            if (pa[u] || !c[u])
                continue;
            cnt = 0;
            if (dfs(u))
                any = true;
        }
    } while (any);

    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        if (!pa[u])
            cnt++;
    }

    puts(cnt == 1 ? "Yes" : "No");

    for (int u = 1; u <= n; u++) {
        G[u].clear();
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
