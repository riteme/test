#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n;
static int c[NMAX + 10];
static vector<int> G[NMAX + 10];
static int dist[NMAX + 10];

void dfs(int x, int f) {
    for (int v : G[x]) if (v != f) {
        dist[v] = dist[x] + (c[v] != c[x]);
        dfs(v, x);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", c + i);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dist[1] = 1;
    dfs(1, 0);
    int u = 0;
    for (int i = 1; i <= n; i++)
        if (dist[i] > dist[u]) u = i;
    dist[u] = 1;
    dfs(u, 0);
    int L = 0;
    for (int i = 1; i <= n; i++)
        L = max(L, dist[i]);
    printf("%d\n", L / 2);
    return 0;
}
