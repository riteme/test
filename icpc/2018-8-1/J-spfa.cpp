#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 3000
#define INF 0x3f3f3f3f3f3f3f3f

struct Edge {
    Edge(int _v, i64 _w) : v(_v), w(_w) {}

    int v;
    i64 w;
};

static int n, m, K;
static vector<Edge *> G[NMAX + 10];
static i64 dist[NMAX + 10], len[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        len[i] = w;
        G[u].push_back(new Edge(v, w));
        G[v].push_back(new Edge(u, w));
    }
}

void shortest(i64 offest, bool first = false) {
    static bool exist[NMAX + 10];
    queue<int> q;
    if (!first) {
        for (int u = 1; u <= n; u++) {
            bool need = false;
            for (auto e : G[u]) {
                if (e->w && offest) need = true;
                e->w = max(0LL, e->w - offest);
            }
            if (!exist[u] && need) {
                q.push(u);
                exist[u] = true;
            }
        }
    } else q.push(1);

    // memset(dist, 0x3f, sizeof(dist));
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;
        for (auto e : G[u]) {
            i64 nd = dist[u] + e->w;
            int v = e->v;
            if (dist[v] > nd) {
                dist[v] = nd;
                if (!exist[v]) {
                    exist[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    initialize();
    sort(len, len + m);
    m = unique(len, len + m) - len;
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    shortest(0, true);
    i64 ans = dist[n];
    for (int i = 0; i < m; i++) {
        shortest(len[i] - (i ? len[i - 1] : 0));
        ans = min(ans, dist[n] + len[i] * K);
    }
    printf("%lld\n", ans);

    return 0;
}
