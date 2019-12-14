#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;

struct Edge {
    int u, v;
};

static int n, q;
static vector<Edge> buc[NMAX + 10];
static int fa[NMAX + 10];
static i64 ans[NMAX + 10];

int find(int x) {
    return fa[x] > 0 ? fa[x] = find(fa[x]) : x;
}

i64 cnt(i64 c) {
    return c * (c + 1) / 2;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        buc[w].push_back({u, v});
    }
    memset(fa, 0xff, sizeof(fa));
    for (int i = 1; i <= NMAX; i++) {
        ans[i] = ans[i - 1];
        for (auto &e : buc[i]) {
            int u = find(e.u), v = find(e.v);
            if (u == v) continue;
            ans[i] -= cnt(fa[v]);
            ans[i] -= cnt(fa[u]);
            fa[v] += fa[u];
            fa[u] = v;
            ans[i] += cnt(fa[v]);
        }
    }
    for (int i = 0; i < q; i++) {
        int K;
        scanf("%d", &K);
        printf("%lld ", ans[K]);
    }
    return 0;
}
