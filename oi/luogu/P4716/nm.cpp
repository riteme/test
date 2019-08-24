#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 10000

#define ACM_BEGIN
static int n, m, G[NMAX + 10], nxt[MMAX + 10];
static struct Edge { int u, v, w; } E[MMAX + 10], *in[NMAX + 10];
static int id[NMAX + 10], mark[NMAX + 10];
int find(int x) { return id[x] ? id[x] = find(id[x]) : x; }
int dfs(int x) {
    mark[x] = 1; int ret = 1;
    for (int i = G[x]; i; i = nxt[i])
        if (!mark[E[i].v]) ret += dfs(E[i].v);
    return ret;
}
inline int detect(int x) {
    mark[x] = x;
    for (int y = in[x]->u; in[y]; y = in[y]->u)
        if (mark[y]) return mark[y] == x ? y : 0;
        else mark[y] = x;
    return 0;
}
int mdst(int r) {
    if (dfs(r) < n) return -1;
    int ret = 0;
    while (true) {
        memset(in, 0, sizeof(in));
        memset(mark, 0, sizeof(mark));
        for (auto *e = E + 1; e <= E + m; e++)
            if (e->u != e->v && e->v != r && (!in[e->v] || e->w < in[e->v]->w))
                in[e->v] = e;
        int p = 0, t = 0;
        for (int x = 1; x <= n; x++, t |= p) if (!mark[x] && in[x]) {
            if (!(p = detect(x))) continue;
            ret += in[p]->w;
            for (int x = in[p]->u; x != p; x = in[x]->u)
                id[find(x)] = p, ret += in[x]->w;
            for (auto *e = E + 1; e <= E + m; e++) {
                int u = find(e->u), v = find(e->v);
                if (u != p && v == p) e->w -= in[e->v]->w;
                e->u = u; e->v = v;
        }}
        if (!t) break;
    }
    for (int x = 1; x <= n; x++) if (in[x]) ret += in[x]->w;
    return ret;
}
#define ACM_END

int main() {
    int r;
    scanf("%d%d%d", &n, &m, &r);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
        nxt[i] = G[E[i].u];
        G[E[i].u] = i;
    }
    printf("%d\n", mdst(r));
    return 0;
}
