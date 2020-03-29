#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 0x3f3f3f3f
#define NMAX 5000
#define KMAX 50

struct Edge {
    int v, w;
};

int n, m, s, t, K;
vector<Edge> G[NMAX + 10];
int dist[KMAX + 10][NMAX + 10];

void initialize() {
    for (int i = 1; i <= n; i++)
        G[i].clear();
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    scanf("%d%d%d", &s, &t, &K);
    K = (K + 9) / 10;
}

struct State {
    int k, u, t;

    bool operator<(const State &z) const {
        return t > z.t;
    }
};

void solve() {
    for (int i = 0; i <= K; i++)
        memset(dist[i], 0x3f, sizeof(dist[i]));
    dist[0][s] = 0;
    priority_queue<State> q;
    q.push({0, s, 0});

    do {
        State _ = q.top();
        q.pop();
        if (_.t > dist[_.k][_.u])
            continue;
        int k = _.k, u = _.u;
        for (int i = 0; i < G[u].size(); i++) {
            Edge &e = G[u][i];
            int v = e.v, nk = min(K, k + 1);
            if (dist[nk][v] > _.t + e.w) {
                dist[nk][v] = _.t + e.w;
                q.push({nk, v, dist[nk][v]});
            }
        }
    } while (!q.empty());

    if (dist[K][t] < INF)
        printf("%d\n", dist[K][t]);
    else puts("-1");
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();
        solve();
    }
    return 0;
}