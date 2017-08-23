#include <cassert>
#include <cstring>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, q;
static int fa[NMAX];
static vector<int> ch[NMAX];

void initialize() {
    ios::sync_with_stdio(false);
    
    cin >> n >> q;
    for (int u = 2; u <= n; u++) {
        cin >> fa[u];
        ch[fa[u]].push_back(u);
    }
}

int lca(int u, int v) {
    static int mark[NMAX], cur;

    cur++;
    for (; u; u = fa[u]) {
        mark[u] = cur;
    }

    for (; v; v = fa[v]) {
        if (mark[v] == cur)
            return v;
    }

    assert(false);  // LCA always exist in connected tree
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
