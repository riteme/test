#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define RMAX 100
#define NMAX 60000
#define INF 0x3f3f3f3f

#define SW 0
#define LT 1
#define RT 2
#define UP 3
#define DW 4

struct Edge {
    int v, w;
};

static int R, C, r1, c1, r2, c2;
static vector<Edge> G[NMAX + 10];
static int dist[NMAX + 10];

int id(int i, int j, int k) {
    return i * R * C + (j - 1) * C + k;
}

void link(int u, int v, int w) {
    G[u].push_back({v, w});
    G[v].push_back({u, w});
}

void dlink(int u, int v, int w) {
    G[u].push_back({v, w});
}

struct State {
    int u, t;

    bool operator<(const State &z) const {
        return t > z.t;
    }
};

int main() {
    for (int _ = 1; true; _++) {
        scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2);
        if (!R && !C) break;

        int n = id(4, R, C);
        for (int i = 1; i <= n; i++)
            G[i].clear();
        memset(dist + 1, 0x3f, sizeof(int) * n);

        for (int i = 1; i <= R; i++) {
            for (int j = 1; j < C; j++) {
                int w;
                scanf("%d", &w);
                if (w) {
                    link(id(SW, i, j), id(SW, i, j + 1), w * 2);
                    dlink(id(RT, i, j), id(RT, i, j + 1), w);
                    dlink(id(LT, i, j + 1), id(LT, i, j), w);
                    dlink(id(SW, i, j), id(RT, i, j + 1), 2 * w);
                    dlink(id(RT, i, j), id(SW, i, j + 1), 2 * w);
                    dlink(id(SW, i, j + 1), id(LT, i, j), 2 * w);
                    dlink(id(LT, i, j + 1), id(SW, i, j), 2 * w);
                }
            }

            if (i < R)
            for (int j = 1; j <= C; j++) {
                int w;
                scanf("%d", &w);
                if (w) {
                    link(id(SW, i, j), id(SW, i + 1, j), 2 * w);
                    dlink(id(DW, i, j), id(DW, i + 1, j), w);
                    dlink(id(UP, i + 1, j), id(UP, i, j), w);
                    dlink(id(SW, i, j), id(DW, i + 1, j), 2 * w);
                    dlink(id(DW, i, j), id(SW, i + 1, j), 2 * w);
                    dlink(id(SW, i + 1, j), id(UP, i, j), 2 * w);
                    dlink(id(UP, i + 1, j), id(SW, i, j), 2 * w);
                }
            }
        }

        int s = id(SW, r1, c1);
        int t = id(SW, r2, c2);
        dist[s] = 0;
        priority_queue<State> q;
        q.push({s, 0});
        while (!q.empty()) {
            auto _ = q.top();
            q.pop();
            if (_.t > dist[_.u])
                continue;
            int u = _.u;
            for (auto &e : G[u]) {
                if (dist[e.v] > dist[u] + e.w) {
                    dist[e.v] = dist[u] + e.w;
                    q.push({e.v, dist[e.v]});
                }
            }
        }

        if (dist[t] < INF)
            printf("Case %d: %d\n", _, dist[t]);
        else
            printf("Case %d: Impossible\n", _);
    }
    return 0;
}
