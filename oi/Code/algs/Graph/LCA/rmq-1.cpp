#include <cassert>
#include <cstring>
#include <climits>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 20

static int n, q;
static int fa[NMAX];
static vector<int> ch[NMAX];
static int dep[NMAX], in[NMAX];
static int cur, hb[NMAX * 2];
static int st[LOGN + 1][NMAX * 2];

void dfs(int u) {
    st[0][++cur] = u;
    in[u] = cur;

    for (int v : ch[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
        st[0][++cur] = u;
    }  // foreach in ch[u]
}

bool cmp(const int x, const int y) {
    return dep[x] < dep[y];
}

void initialize_st() {
    dep[0] = INT_MAX;
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= cur; i++) {
            st[j][i] = min(
                st[j - 1][i],
                i + (1 << (j - 1)) <= cur ? st[j - 1][i + (1 << (j - 1))] : 0,
                cmp);
        }  // for
    }      // for
}

void initialize() {
    ios::sync_with_stdio(false);

    cin >> n >> q;
    for (int u = 2; u <= n; u++) {
        cin >> fa[u];
        ch[fa[u]].push_back(u);
    }

    dfs(1);
    initialize_st();

    hb[1] = 0;
    for (int i = 2; i <= n * 2; i++) {
        hb[i] = hb[i >> 1] + 1;
    }  // for
}

int lca(int u, int v) {
    if (in[u] > in[v])
        swap(u, v);
    int l = in[u], r = in[v], k = hb[r - l + 1];
    return min(st[k][l], st[k][r - (1 << k) + 1], cmp);
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
