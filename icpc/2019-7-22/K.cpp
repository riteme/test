#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define OPMAX 100000

struct Edge {
    int v, w;
};

static int n, deg[NMAX + 10];
static vector<Edge> G[NMAX + 10];
static int r, m, ok = 1;
static struct {
    int u, v, w;
} op[OPMAX + 10];

inline void add(int u, int v, int w) {
    op[m++] = {u, v, w};
}

int dfs(int x, int fa) {
    int p1 = 0, p2 = 0, t, sum = 0;
    for (auto &e : G[x]) if (e.v != fa) {
        sum += e.w;
        int p = dfs(e.v, x);
        if (!p1) p1 = p;
        else if (!p2) p2 = p;
    } else t = e.w;
    int d = t - sum;
    //fprintf(stderr, "x = %d, p1 = %d, p2 = %d, d = %d, t = %d\n", x, p1, p2, d, t);
    if (fa && p1 && d) {
        if (!p2 || (d & 1)) ok = 0;
        else {
            add(p1, r, d / 2);
            add(p2, r, d / 2);
            add(p1, p2, -d / 2);
        }
    }
    if (!p1) add(x, r, t);
    return p1 ? p1 : x;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
        deg[u]++;
        deg[v]++;
    }
    r = 1;
    while (deg[r] != 1) r++;
    fprintf(stderr, "r = %d\n", r);
    dfs(r, 0);
    if (ok) {
        printf("YES\n%d\n", m);
        for (int i = 0; i < m; i++)
            printf("%d %d %d\n", op[i].u, op[i].v, op[i].w);
    } else puts("NO");
    return 0;
}
