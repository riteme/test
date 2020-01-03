#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000
#define MMAX ((NMAX + 10) * (NMAX + 10))

typedef long long i64;

struct Edge {
    int u, v;
    i64 w;

    bool operator<(const Edge &z) const {
        return w < z.w;
    }
};

static int n, m, s;
static int fa[NMAX + 10];
static i64 X[NMAX + 10], Y[NMAX + 10];
static i64 C[NMAX + 10], K[NMAX + 10];
static Edge e[MMAX + 10];
static bool mark[MMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

void link(int u, int v, i64 w) {
    e[m++] = {u, v, w};
}

int main() {
    scanf("%d", &n);
    s = n + 1;
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", X + i, Y + i);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", C + i);
        link(s, i, C[i]);
    }
    for (int i = 1; i <= n; i++)
        scanf("%lld", K + i);
    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
        link(i, j, (K[i] + K[j]) * (abs(X[i] - X[j]) + abs(Y[i] - Y[j])));
    sort(e, e + m);

    i64 ans = 0, cnt = 0;
    for (int i = 0; i < m; i++) {
        int u = find(e[i].u);
        int v = find(e[i].v);
        if (u == v) continue;
        mark[i] = true;
        cnt += e[i].u == s || e[i].v == s;
        ans += e[i].w;
        fa[u] = v;
    }

    printf("%lld\n", ans);

    printf("%lld\n", cnt);
    for (int i = 0; i < m; i++)
    if (mark[i] && (e[i].u == s || e[i].v == s))
        printf("%d ", e[i].u == s ? e[i].v : e[i].u);

    printf("\n%lld\n", n - cnt);
    for (int i = 0; i < m; i++)
    if (mark[i] && e[i].u != s && e[i].v != s)
        printf("%d %d\n", e[i].u, e[i].v);

    return 0;
}
