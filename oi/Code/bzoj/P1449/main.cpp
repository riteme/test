#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define MMAX 1000
#define NODEMAX (NMAX + MMAX)
#define INFTY 0x3f3f3f3f

inline int squ(int x) {
    return x * x;
}

struct Edge {
    Edge(int _u, int _v, int _capacity, int _w)
        : u(_u), v(_v), capacity(_capacity), w(_w) {}

    int u, v, capacity, w;
    Edge *reverse_edge;
};

static int n, m, s, t;
static int win[NMAX + 10];
static int lose[NMAX + 10];
static int C[NMAX + 10], D[NMAX + 10];
static int cnt[NMAX + 10];
static vector<Edge *> G[NODEMAX + 10];

inline void link(int u, int v, int capacity, int w) {
    Edge *e = new Edge(u, v, capacity, w);
    Edge *re = new Edge(v, u, 0, -w);
    e->reverse_edge = re;
    re->reverse_edge = e;
    G[u].push_back(e);
    G[v].push_back(re);
}

void initialize() {
    scanf("%d%d", &n, &m);
    s = n + m + 1;
    t = s + 1;

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", win + i, lose + i, C + i, D + i);
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        cnt[u]++;
        cnt[v]++;
        link(s, n + i, 1, 0);
        link(n + i, u, 1, 0);
        link(n + i, v, 1, 0);
    }
}

static bool exist[NODEMAX + 10];
static int dist[NODEMAX + 10];
static Edge *edge[NODEMAX + 10];

void spfa() {
    memset(dist, 0x3f, sizeof(dist));

    queue<int> q;
    dist[s] = 0;
    exist[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        exist[u] = false;
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (e->capacity == 0)
                continue;

            if (dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;
                edge[v] = e;

                if (!exist[v]) {
                    exist[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int sap() {
    int ret = 0;

    while (true) {
        spfa();

        if (dist[t] == INFTY)
            break;

        int w = INFTY;
        int x = t;
        while (x != s) {
            w = min(w, edge[x]->capacity);
            x = edge[x]->u;
        }

        x = t;
        while (x != s) {
            ret += w * edge[x]->w;
            edge[x]->capacity -= w;
            edge[x]->reverse_edge->capacity += w;
            x = edge[x]->u;
        }
    }

    return ret;
}

int main() {
    initialize();

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        answer += C[i] * squ(win[i]);
        answer += D[i] * squ(lose[i] + cnt[i]);
    }

    for (int i = 1; i <= n; i++) {
        lose[i] += cnt[i];

        for (int j = 1; j <= cnt[i]; j++) {
            link(i, t, 1,
                 2 * C[i] * win[i] - 2 * D[i] * lose[i] +
                 C[i] + D[i]);
            win[i]++;
            lose[i]--;
        }
    }

    // for (int u = 1; u <= t; u++) {
    //     for (size_t i = 0; i < G[u].size(); i++) {
    //         Edge *e = G[u][i];

    //         if (e->capacity)
    //             printf("%d -> %d : %d / %d\n",
    //                    e->u, e->v, e->capacity, e->w);
    //     }
    // }

    answer += sap();
    printf("%d\n", answer);

    return 0;
}
