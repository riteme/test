#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define KMAX 100
#define INF 0x3f3f3f3f

struct Edge {
    int v, w;
};

struct State {
    int u, t;

    bool operator<(const State &z) const {
        return t > z.t;
    }
};

static int n, m, K;
static vector<Edge> G[NMAX + 10], R[NMAX + 10];
static int h[NMAX + 10], cnt[NMAX + 10];
static int ans[KMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (u < v)
            swap(u, v);
        G[u].push_back({v, w});
        R[v].push_back({u, w});
    }

    memset(h, 0x3f, sizeof(h));
    memset(ans, 0x3f, sizeof(ans));
    h[1] = 0;
    for (int u = 1; u <= n; u++)
    for (auto &e : R[u])
        h[e.v] = min(h[e.v], h[u] + e.w);

    priority_queue<State> q;
    q.push({n, h[n]});
    while (!q.empty()) {
        auto _ = q.top();
        q.pop();
        int u = _.u;
        cnt[u]++;
        if (u == 1 && cnt[u] <= K)  // caution: cnt[u] (= the number of candidates) may exceed K
            ans[cnt[u]] = _.t;
        if (cnt[u] >= K)
            continue;
        for (auto &e : G[u]) {
            int v = e.v;
            if (cnt[v] < K)
                q.push({v, _.t - h[u] + h[v] + e.w});
        }
    }

    for (int i = 1; i <= K; i++)
        printf("%d\n", ans[i] < INF ? ans[i] : -1);
    return 0;
}
