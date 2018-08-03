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
static int cnt[NMAX + 10];
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

i64 shortest(i64 offest) {
    struct State {
        State(int _u, i64 _t) : u(_u), t(_t) {}

        int u;
        i64 t;

        bool operator<(const State &z) const {
            return t > z.t;
        }
    };

    memset(cnt, 0, sizeof(cnt));
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    priority_queue<State> q;
    q.push(State(1, 0));
    while (!q.empty()) {
        State u = q.top();
        q.pop();
        if (u.t > dist[u.u]) continue;
        for (auto e : G[u.u]) {
            i64 nd = u.t + max(0LL, e->w - offest);
            if (dist[e->v] > nd) {
                dist[e->v] = nd;
                cnt[e->v] = cnt[u.u] + 1;
                q.push(State(e->v, nd));
            }
        }
    }

    return dist[n];
}

int main() {
    initialize();
    i64 ans = INF;
    for (int i = 0; i < m; i++)
        ans = min(ans, shortest(len[i]) + len[i] * min(K, cnt[n]));
    printf("%lld\n", ans);

    return 0;
}
