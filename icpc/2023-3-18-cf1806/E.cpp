#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

int n, q;
i64 a[NMAX + 10];
int p[NMAX + 10];
vector<int> G[NMAX + 10];
i64 pre[NMAX + 10];
vector<int> no[NMAX + 10];
i64 ans[NMAX + 10];
vector<pair<int, int>> op[NMAX + 10];

i64 get(int u, int v, int d) {
    i64 &r = pre[v];
    if (!r) {
        r = get(p[u], p[v], d - 1) + a[u] * a[v];
        no[d].push_back(v);
    }
    return r;
}

void dfs(int u, int d) {
    pre[u] += a[u] * a[u];
    for (auto [v, i] : op[u]) {
        ans[i] = get(u, v, d);
    }

    for (int v : G[u]) {
        pre[v] = pre[u];
        dfs(v, d + 1);
    }

    pre[u] = 0;
    for (int v : no[d]) {
        pre[v] = 0;
    }
    no[d].clear();
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }
    for (int i = 2; i <= n; i++) {
        scanf("%d", p + i);
        G[p[i]].push_back(i);
    }
    for (int i = 1; i <= q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (u > v)
            swap(u, v);
        op[u].push_back({v, i});
    }

    dfs(1, 0);

    for (int i = 1; i <= q; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}
