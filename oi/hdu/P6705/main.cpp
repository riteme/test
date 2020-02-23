#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w) {}

    int u, v, id;
    i64 w;

    bool operator<(const Edge &z) const {
        return w < z.w;
    }
};

static int n, m, q, K;
static vector<Edge> G[NMAX + 10];
static int query[NMAX + 10];
static i64 ans[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        G[i].clear();

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(Edge(u, v, w));
    }

    for (int i = 1; i <= n; i++) {
        sort(G[i].begin(), G[i].end());
        for (int j = 0; j < G[i].size(); j++)
            G[i][j].id = j;
    }

    K = 0;
    for (int i = 1; i <= q; i++) {
        scanf("%d", query + i);
        K = max(K, query[i]);
    }
}

struct State {
    State(i64 _len, Edge *_e)
        : len(_len), e(_e) {}

    i64 len;
    Edge *e;

    bool operator<(const State &z) const {
        return len > z.len;
    }
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        initialize();

        priority_queue<State> Q;
        for (int i = 1; i <= n; i++) if (!G[i].empty()) {
            Edge &e = G[i][0];
            Q.push(State(e.w, &e));
        }

        for (int i = 1; i <= K; i++) {
            State s = Q.top();
            Q.pop();
            ans[i] = s.len;

            Edge *e = s.e;
            if (e->id + 1 < G[e->u].size()) {
                Edge *ne = &G[e->u][e->id + 1];
                Q.push(State(s.len - e->w + ne->w, ne));
            }

            if (!G[e->v].empty()) {
                Edge *ne = &G[e->v][0];
                Q.push(State(s.len + ne->w, ne));
            }
        }

        for (int i = 1; i <= q; i++)
            printf("%lld\n", ans[query[i]]);
    }

    return 0;
}
