#include <cassert>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, q;
static int fa[NMAX], dep[NMAX], size[NMAX];
static vector<int> ch[NMAX];
static int top[NMAX];

void dfs(int u) {
    size[u] = 1;
    for (int v : ch[u]) {
        dfs(v);
        size[u] += size[v];
    }
}

void decompose(int u) {
    int nxt = 0;
    for (int v : ch[u]) {
        if (size[v] > size[nxt])
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
    decompose(1);
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
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
