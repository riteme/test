#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define WMAX 500
#define NMAX 250000
#define INFTY 0x3f3f3f3f

struct Edge {
    Edge(int _v, int _w)
        : v(_v), w(_w) {}

    int v, w;
};

static int n;
static int left[WMAX + 10][WMAX + 10];
static int right[WMAX + 10][WMAX + 10];
static int up[WMAX + 10][WMAX + 10];
static int down[WMAX + 10][WMAX + 10];
static int s, t;
static vector<Edge *> G[NMAX + 10];

inline int id(int i, int j) {
    return (i - 1) * (n - 1) + j;
}

void initialize() {
    scanf("%d", &n);
    n++;

    memset(left, 0x3f, sizeof(left));
    memset(right, 0x3f, sizeof(right));
    memset(up, 0x3f, sizeof(up));
    memset(down, 0x3f, sizeof(down));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            scanf("%d", &right[i][j]);
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &down[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            scanf("%d", &left[i][j]);
        }
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &up[i][j]);
        }
    }
}

inline void link(int u, int v, int w) {
    G[u].push_back(new Edge(v, w));
}

void make_dual_graph() {
    s = id(n - 1, n - 1) + 1;
    t = s + 1;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            int p = id(i, j);

            if (i + 1 < n)
                link(p, id(i + 1, j), left[i + 1][j + 1]);
            if (i - 1 > 0)
                link(p, id(i - 1, j), right[i][j]);
            if (j + 1 < n)
                link(p, id(i, j + 1), down[i][j + 1]);
            if (j - 1 > 0)
                link(p, id(i, j - 1), up[i + 1][j]);
        }
    }

    for (int i = 1; i < n; i++) {
        link(s, id(i, 1), down[i][1]);
    }

    for (int i = 1; i < n; i++) {
        link(s, id(n - 1, i), right[n][i]);
    }

    for (int i = 1; i < n; i++) {
        link(id(1, i), t, right[1][i]);
    }

    for (int i = 1; i < n; i++) {
        link(id(i, n - 1), t, down[i][n]);
    }

    n = t;
}

void print() {
    for (int u = 1; u <= n; u++) {
        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            printf("%d %d %d\n", u, e->v, e->w);
        }
    }
}

static bool exist[NMAX + 10];
static int dist[NMAX + 10];

void spfa() {
    memset(dist, 0x3f, sizeof(dist));

    queue<int> q;
    dist[s] = 0;
    exist[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (dist[u] + e->w < dist[v]) {
                dist[v] = dist[u] + e->w;

                if (!exist[v]) {
                    exist[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    freopen("altitude.in", "r", stdin);
    freopen("altitude.out", "w", stdout);
    initialize();
    make_dual_graph();
    // print();
    spfa();
    printf("%d\n", dist[t]);

    return 0;
}
