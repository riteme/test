#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long i64;

#define NMAX 500
#define MMAX 300000
#define INF 0x3f3f3f3f3f3f3f3f

struct Edge {
    int v;
    i64 w;
};

int n, m, s, t;
i64 cl[NMAX + 10][NMAX + 10], cr[NMAX + 10][NMAX + 10];
vector<Edge> G[MMAX + 10];

inline int id(int i, int j) {
    return n * i + j;
}

inline void link(int u, int v, i64 w) {
    G[u].push_back({v, w});
    G[v].push_back({u, w});
}

void initialize() {
    scanf("%d%d", &n, &m);
    memset(cl, 0x3f, sizeof(cl));
    memset(cr, 0x3f, sizeof(cr));
    for (int i = 0; i < m; i++) {
        int l, r, c;
        char buf[16];
        scanf("%d%d%s%d", &l, &r, buf, &c);
        if (buf[0] == 'L') cr[l][r] = c;
        else cl[l][r] = c;
    }
    s = id(n, n) + 233;
    t = s + 1;

    for (int l = 1; l <= n; l++)
    for (int r = l + 1; r <= n; r++) {
        int x = id(l, r);
        link(x, (1 < l ? id(l - 1, r) : s), cl[l][r]);
        link(x, (r < n ? id(l, r + 1) : t), cr[l][r]);
        if (l + 1 < r) {
            link(x, id(l, r - 1), cr[l][r - 1]);
            link(x, id(l + 1, r), cl[l + 1][r]);
        }
    }
}

i64 dist[MMAX + 10];

int main() {
    initialize();

    typedef pair<i64, int> pii;
    priority_queue<pii, vector<pii>, greater<pii>> q;

    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    q.push(pii(0, s));
    do {
        auto _ = q.top();
        q.pop();
        if (_.first > dist[_.second])
            continue;

        int u = _.second;
        for (auto &e : G[u])
        if (dist[e.v] > dist[u] + e.w) {
            dist[e.v] = dist[u] + e.w;
            q.push(pii(dist[e.v], e.v));
        }
    } while (!q.empty());

    if (dist[t] >= INF) puts("-1");
    else printf("%lld\n", dist[t]);

    return 0;
}