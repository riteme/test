#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2000
#define MMAX 15000
#define INF 0x3f3f3f3f

struct Edge {
    Edge(int _u, int _v, int _w, int _c)
        : u(_u), v(_v), w(_w), c(_c) {}

    int u, v, w, c;
    Edge *rev;
};

static vector<Edge *> G[NMAX + 10];

inline void link(int u, int v, int w, int c) {
    Edge *e = new Edge(u, v, w, c);
    Edge *re = new Edge(v, u, -w, 0);
    e->rev = re; re->rev = e;
    G[u].push_back(e);
    G[v].push_back(re);
}

static int dist[NMAX + 10];
static bool exist[NMAX + 10];
static Edge *fa[NMAX + 10];

void spfa(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(exist, 0, sizeof(exist));
    memset(fa, 0, sizeof(fa));

    queue<int> q;
    q.push(s);
    dist[s] = 0;
    exist[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;

        for (auto e : G[u]) {
            if (e->c == 0)
                continue;

            if (dist[e->v] > dist[u] + e->w) {
                dist[e->v] = dist[u] + e->w;
                fa[e->v] = e;
                if (!exist[e->v]) {
                    exist[e->v] = true;
                    q.push(e->v);
                }
            }
        }
    }
}

static int flow, cost, s, t;

void maxflow() {
    while (true) {
        spfa(s);

        if (dist[t] >= INF)
            break;

        int minc = INF, x = t;
        while (x != s) {
            minc = min(minc, fa[x]->c);
            x = fa[x]->u;
        }

        x = t;
        flow += minc;
        while (x != s) {
            fa[x]->c -= minc;
            fa[x]->rev->c += minc;
            cost += minc * fa[x]->w;
            x = fa[x]->u;
        }
    }
}

static int n, m, a, b, ans;

void initialize() {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    s = 2 * n + 1;
    t = s + 1;

    for (int i = 1; i <= n; i++) {
        int w;
        scanf("%d", &w);
        link(i, n + i, w, INF);
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        link(n + u, v, w, INF);
        link(n + v, u, w, INF);
    }

    for (int i = 1; i <= a; i++) {
        int w, u;
        scanf("%d%d", &w, &u);
        link(s, u, w, 1);
    }

    for (int i = 1; i <= b; i++) {
        int w, u;
        scanf("%d%d", &w, &u);
        ans += w;
        link(n + u, t, 0, 1);
    }
}

int main() {
    initialize();
    maxflow();

    if (flow == b) {
        puts("Yes");
        printf("%d\n", ans - cost);
    } else {
        puts("No");
        printf("%d\n", flow);
    }

    return 0;
}
