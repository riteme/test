// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300
#define INFTY 0x3f3f3f3f

struct Edge {
    Edge(int _u, int _v, int _c, int _w)
        : u(_u), v(_v), c(_c), w(_w) {}

    int u, v, c, w;
    Edge *rev;
};

static int n, m, s, t;
static int M[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

inline void link(int u, int v, int l, int r, int w) {
    if (r > l) {
        Edge *e = new Edge(u, v, r - l, w);
        Edge *re = new Edge(v, u, 0, -w);
        e->rev = re;
        re->rev = e;
        G[u].push_back(e);
        G[v].push_back(re);
    }

    M[u] -= l;
    M[v] += l;
}

static int dist[NMAX + 10];
static Edge *edge[NMAX + 10];
static bool exist[NMAX + 10];

void spfa() {
    memset(dist, 0x3f, sizeof(dist));

    queue<int> q;
    q.push(s);
    exist[s] = true;
    dist[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (e->c == 0)
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

        int maxflow = INFTY;
        int x = t;
        while (x != s) {
            Edge *e = edge[x];
            maxflow = min(maxflow, e->c);
            x = e->u;
        }

        x = t;
        while (x != s) {
            Edge *e = edge[x];
            ret += maxflow * e->w;
            e->c -= maxflow;
            e->rev->c += maxflow;
            x = e->u;
        }
    }

    return ret;
}

void initialize() {
    scanf("%d%d", &n, &m);

    s = n * 2 + m + 1;
    t = s + 1;

    int w;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w);

        link(i, i + n, w, w, 0);
        link(i + n, t, 0, INFTY, 0);
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            scanf("%d", &w);

            if (w >= 0)
                link(i + n, j, 0, INFTY, w);
        }
    }

    for (int i = 1; i <= m; i++) {
        link(s, 2 * n + i, 0, 1, 0);

        for (int j = 1; j <= n; j++) {
            link(2 * n + i, j, 0, 1, 0);
        }
    }
}

int main() {
    initialize();

    link(t, s, 0, INFTY, 0);
    s += 2;
    t += 2;
    for (int i = 1; i < s; i++) {
        if (M[i] > 0)
            link(s, i, 0, M[i], 0);
        if (M[i] < 0)
            link(i, t, 0, -M[i], 0);
    }

    printf("%d\n", sap());

    return 0;
}
