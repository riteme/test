#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define INF 0x3f3f3f3f3f3f3f3f

struct Edge {
    int v, w;
};

int n, K;
vector<Edge> G[NMAX + 10];
bool mark[NMAX + 10];
i64 f[NMAX + 10][2];

void dp(int x, int fa) {
    if (mark[x]) {
        f[x][0] = INF;
        f[x][1] = 0;
        for (int i = 0; i < G[x].size(); i++) {
            Edge &e = G[x][i];
            if (e.v == fa) continue;
            dp(e.v, x);
            f[x][1] += min(f[e.v][0], e.w + f[e.v][1]);
        }
    } else {
        f[x][0] = 0;
        f[x][1] = INF;
        for (int i = 0; i < G[x].size(); i++) {
            Edge &e = G[x][i];
            if (e.v == fa) continue;
            dp(e.v, x);
            i64 cost = min(f[e.v][0], e.w + f[e.v][1]);
            f[x][1] = min(f[x][1] + cost, f[x][0] + f[e.v][1]);
            f[x][0] += cost;
        }
    }
}

void solve() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++)
        G[i].clear();
    memset(mark + 1, 0, n);

    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u++; v++;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    int r = 0;
    for (int i = 0; i < K; i++) {
        int u;
        scanf("%d", &u);
        u++;
        mark[u] = true;
        if (!r) r = u;
    }

    dp(r, 0);
    printf("%lld\n", f[r][1]);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}