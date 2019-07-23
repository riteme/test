#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2000

struct Edge {
    Edge(int _v, int _w) : v(_v), w(_w) {}

    int v, w;
};

struct State {
    State(int _u, int _s) : u(_u), s(_s) {}

    int u, s;

    bool operator<(const State &z) const {
        return s > z.s;
    }
};

static int n, m, W, H;
static int X[NMAX + 10], Y[NMAX + 10];
static int dist[NMAX + 10];
static vector<Edge> G[NMAX + 10];

inline void link(int u, int v, int w) {
    G[u].push_back(Edge(v, w));
}

int main() {
    scanf("%d%d%d%d", &n, &m, &W, &H);
    for (int i = 1; i <= n; i++) scanf("%d%d", X + i, Y + i);
    for (int i = 0; i < m; i++) {
        int p, t, L, R, D, U;
        scanf("%d%d%d%d%d%d", &p, &t, &L, &R, &D, &U);
        for (int j = 1; j <= n; j++)
            if (L <= X[j] && X[j] <= R && D <= Y[j] && Y[j] <= U)
                link(p, j, t);
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    priority_queue<State> q;
    q.push(State(1, 0));
    while (!q.empty()) {
        State s = q.top();
        q.pop();
        if (dist[s.u] != s.s) continue;
        int u = s.u;
        for (int i = 0; i < G[u].size(); i++) {
            Edge &e = G[u][i];
            int v = e.v;
            if (dist[v] > dist[u] + e.w) {
                dist[v] = dist[u] + e.w;
                q.push(State(v, dist[v]));
            }
        }
    }
    for (int i = 2; i <= n; i++) printf("%d\n", dist[i]);
    return 0;
}
