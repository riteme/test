//#pragma GCC optimize(3)

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

void shortest(i64 offest) {
    struct State {
        State(int _u, int _c, i64 _t) : u(_u), c(_c), t(_t) {}

        int u, c;
        i64 t;

        bool operator<(const State &z) const {
            return t > z.t ||
                  (t == z.t && c > z.c);
        }
    };

    for (int u = 1; u <= n; u++) {
        for (auto e : G[u])
            e->w = max(0LL, e->w - offest);
    }

    memset(cnt, 0x3f, sizeof(cnt));
    memset(dist, 0x3f, sizeof(dist));
    cnt[1] = dist[1] = 0;
    priority_queue<State> q;
    q.push(State(1, 0, 0));
    while (!q.empty()) {
        State u = q.top();
        q.pop();
        if (u.t > dist[u.u]) continue;
        for (auto e : G[u.u]) {
            State ns(e->v, u.c + 1, u.t + e->w);
            if (State(0, cnt[e->v], dist[e->v]) < ns) {
                cnt[e->v] = ns.c;
                dist[e->v] = ns.t;
                q.push(ns);
            }
        }
    }
}

int main() {
    initialize();
    sort(len, len + m);
    m = unique(len, len + m) - len;
    shortest(0);
    i64 ans = dist[n];
    for (int i = 0; i < m; i++) {
        shortest(len[i] - (i ? len[i - 1] : 0));
        ans = min(
            ans,
            dist[n] + len[i] * min(K, cnt[n])
        );
    }
    printf("%lld\n", ans);

    return 0;
}
