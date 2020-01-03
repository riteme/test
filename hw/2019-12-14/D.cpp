#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long i64;

static int n, m;
static i64 a[NMAX + 10];
static struct Edge {
    int u, v;
    i64 w;

    bool operator<(const Edge &z) const {
        return w < z.w;
    }
} e[NMAX + 10];

static int fa[NMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

int main() {
    scanf("%d%d", &n, &m);
    int u = 0;
    a[0] = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
        if (a[i] < a[u]) u = i;
    }
    for (int i = 0; i < m; i++)
        scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
    for (int v = 1; v <= n; v++)
        if (v != u) e[m++] = {u, v, a[u] + a[v]};
    sort(e, e + m);
    i64 ans = 0;
    for (int i = 0; i < m; i++) {
        int u = find(e[i].u);
        int v = find(e[i].v);
        if (u == v) continue;
        ans += e[i].w;
        fa[u] = v;
    }
    printf("%lld\n", ans);
    return 0;
}
