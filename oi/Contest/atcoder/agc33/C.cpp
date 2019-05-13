#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, dist[NMAX + 10];
static vector<int> G[NMAX + 10];
static bool f[NMAX + 10];

void dfs(int x, int fa) {
    for (int v : G[x]) if (v != fa) {
        dist[v] = dist[x] + 1;
        dfs(v, x);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dist[1] = 1;
    dfs(1, 0);
    int u = 0;
    for (int i = 1; i <= n; i++) if (dist[i] > dist[u]) u = i;
    dist[u] = 1;
    dfs(u, 0);
    int v = 0;
    for (int i = 1; i <= n; i++) if (dist[i] > dist[v]) v = i;
    f[1] = true;
    for (int i = 3; i <= n; i++) f[i] = !f[i - 1] || !f[i - 2];
    puts(f[dist[v]] ? "First" : "Second");
    return 0;
}
