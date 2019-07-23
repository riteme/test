#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 200000

typedef long long i64;

struct Edge {
    Edge(int _v, int _w) : v(_v), w(_w) {}

    int v, w;  // w int?
};

struct State {
    State(int _u, i64 _s) : u(_u), s(_s) {}

    int u;
    i64 s;

    bool operator<(const State &z) const {
        return s > z.s;
    }
};

static int n, m, s, t;
static i64 A, B, C, dist[MMAX * 2 + 10];
static i64 tm[MMAX * 2 + 10];
static vector<Edge> G[MMAX * 2 + 10];
static vector<int> ps[NMAX + 10];

inline void link(int u, int v, int w) {  // w int?
    G[u].push_back(Edge(v, w));
    //fprintf(stderr, "%d → %d [%d]\n", u, v, w);
}

bool cmp(int x, int y) {
    return tm[x] < tm[y];
}

int main() {
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);
    scanf("%d%d%lld%lld%lld", &n, &m, &A, &B, &C);
    s = 2 * m + 1;
    t = s + 1;
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d%lld%lld", &u, &v, tm + i, tm + m + i);
        link(i, m + i, C + tm[m + i] - tm[i]);
        ps[u].push_back(i);
        ps[v].push_back(m + i);
    }
    for (int i = 1; i <= n; i++) {
        sort(ps[i].begin(), ps[i].end(), cmp);
        for (int j = 0; j < (int)ps[i].size() - 1; j++) {
            int u = ps[i][j], v = ps[i][j + 1];
            link(u, v, (B + 1) * (tm[v] - tm[u]));
        }
    }
    link(s, ps[1][0], (B + 1) * tm[ps[1][0]]);
    for (int i = 0; i < ps[n].size(); i++) {
        int u = ps[n][i];
        link(u, t, 0);
    }

    memset(dist, 0x3f, sizeof(dist));
    priority_queue<State> q;
    dist[s] = 0;
    q.push(State(s, 0));
    while (!q.empty()) {
        State z = q.top();
        q.pop();
        if (z.s != dist[z.u]) continue;
        int u = z.u;
        for (int i = 0; i < G[u].size(); i++) {
            Edge &e = G[u][i];
            int v = e.v;
            if (dist[v] > dist[u] + e.w) {
                dist[v] = dist[u] + e.w;
                q.push(State(v, dist[v]));
            }
        }
    }
    printf("%lld\n", dist[t]);

    return 0;
}
