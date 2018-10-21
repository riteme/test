#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define MOD 1000000007

struct Edge {
    int v, w;
};

static int n, m, L;
static vector<Edge *> G[NMAX + 10];

int dfs(int x, int f, int d) {
    if (d > L) return 0;
    int r = 1;
    for (auto e : G[x])
        if (e->v != f) r += dfs(e->v, x, d + e->w);
    return r;
}

int main() {
    scanf("%d%d%d", &n, &m, &L);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(new Edge{v, w});
        G[v].push_back(new Edge{u, w});
    }

    for (int i = 1; i <= n; i++) printf("%d\n", dfs(i, 0, 0));

    return 0;
}
