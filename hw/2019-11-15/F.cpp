#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

struct Edge {
    Edge() : nxt(0) {}

    int v, nxt;
};

static int n;
static Edge e[2 * NMAX + 10];
static int T[NMAX + 10];
static int size[NMAX + 10], fa[NMAX + 10];
static int val[NMAX + 10], mi = INT_MAX;

void dfs(int x) {
    size[x] = 1;
    for (int i = T[x]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa[x]) continue;
        fa[v] = x;
        dfs(v);
        size[x] += size[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[2 * i].v = v;
        e[2 * i].nxt = T[u];
        T[u] = 2 * i;
        e[2 * i - 1].v = u;
        e[2 * i - 1].nxt = T[v];
        T[v] = 2 * i - 1;
    }
    dfs(1);
    for (int u = 1; u <= n; u++) {
        if (fa[u]) val[u] = n - size[u];
        for (int i = T[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (v == fa[u]) continue;
            val[u] = max(val[u], size[v]);
        }
        mi = min(mi, val[u]);
    }
    for (int u = 1; u <= n; u++)
        if (val[u] == mi) printf("%d ", u);
    puts("");
    return 0;
}
