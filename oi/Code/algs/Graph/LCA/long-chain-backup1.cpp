#include <cassert>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, q;
static int fa[NMAX], dep[NMAX], rnk[NMAX];
static vector<int> ch[NMAX], L[NMAX];
static int top[NMAX], in[NMAX], out[NMAX];

void dfs(int u) {
    static int cur;

    in[u] = ++cur;

    for (int v : ch[u]) {
        dfs(v);
        rnk[u] = max(rnk[u], rnk[v] + 1);
    }

    out[u] = cur;
}

void decompose(int u) {
    int nxt = 0;
    for (int v : ch[u]) {
        if (rnk[v] > rnk[nxt])
            nxt = v;
    }

    if (nxt) {
        top[nxt] = top[u];
        decompose(nxt);
    }

    for (int v : ch[u]) {
        if (v != nxt) {
            top[v] = v;
            decompose(v);
        }
    }

    L[top[u]].push_back(u);

    if (u == top[u]) {
        int l = L[u].size(), x = fa[u];
        while (x && l--) {
            L[u].push_back(x);
            x = fa[x];
        }
    }
}

void initialize() {
    ios::sync_with_stdio(false);
    
    cin >> n >> q;
    dep[1] = 0;
    for (int u = 2; u <= n; u++) {
        cin >> fa[u];
        ch[fa[u]].push_back(u);
        dep[u] = dep[fa[u]] + 1;
    }

    dfs(1);
    top[1] = 1;
    rnk[0] = -1;
    decompose(1);
}

inline bool is_ancestor(int p, int u) {
    return in[p] <= in[u] && in[u] <= out[p];
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        
        int t = L[top[u]].back();
        if (is_ancestor(t, v)) {
            int l = dep[L[top[u]][0]] - dep[top[u]];
            int r = L[top[u]].size() - 1;
            while (l < r) {
                int m = (l + r) / 2 + 1;
                int p = L[top[u]][m];

                if (is_ancestor(p, v))
                    r = m - 1;
                else
                    l = m;
            }

            return L[top[u]][l + 1];
        } else
            u = t;
    }

    return dep[u] < dep[v] ? u : v;
}

int main() {
    initialize();

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }

    return 0;
}
