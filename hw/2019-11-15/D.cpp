#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, q;
static vector<int> G[NMAX + 10];
static int ans[NMAX + 10];
static int dist[NMAX + 10];

void dfs(int x, int f) {
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == f) continue;
        dist[v] = dist[x] + 1;
        dfs(v, x);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++)
            G[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        memset(dist + 1, 0, sizeof(int) * n);
        dfs(1, 0);
        int mx = 0, mp;
        for (int u = 1; u <= n; u++) if (dist[u] > mx) {
            mx = dist[u];
            mp = u;
        }
        memset(dist + 1, 0, sizeof(int) * n);
        dfs(mp, 0);
        int len = 0;
        for (int i = 1; i <= n; i++)
            len = max(len, dist[i]);
        for (int i = 1; i <= len + 1; i++)
            ans[i] = i - 1;
        for (int i = len + 2; i <= n; i++)
            ans[i] = ans[i - 1] + 2;
        while (q--) {
            int K;
            scanf("%d", &K);
            printf("%d\n", ans[K]);
        }
    }
    return 0;
}
