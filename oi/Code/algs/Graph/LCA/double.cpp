#include <cassert>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 20

static int n, q;
static int fa[NMAX], dep[NMAX];
static vector<int> ch[NMAX];
static int g[LOGN + 1][NMAX];

void initialize() {
    ios::sync_with_stdio(false);
    
    cin >> n >> q;
    for (int u = 2; u <= n; u++) {
        cin >> fa[u];
        ch[fa[u]].push_back(u);
    }

    dep[0] = -1;
    for (int i = 1; i <= n; i++) {
        g[0][i] = fa[i];
        dep[i] = dep[fa[i]] + 1;
    }

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            g[j][i] = g[j - 1][g[j - 1][i]];
        }
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);

    int x = dep[u] - dep[v];
    for (int i = 0; i <= LOGN; i++) {
        if ((x >> i) & 1)
            u = g[i][u];
    }

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (g[i][u] != g[i][v]) {
            u = g[i][u];
            v = g[i][v];
        }
    }

    return fa[u];
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
