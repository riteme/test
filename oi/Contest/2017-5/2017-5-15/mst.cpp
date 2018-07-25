// #define NDEBUG

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 20
#define EPSILON 1e-8

static int n;
static int X[NMAX + 10], Y[NMAX + 10];
static double dist[NMAX + 10][NMAX + 10];
static double ans;

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", X + i);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", Y + i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dist[i][j] = dist[j][i] = hypot(X[i] - X[j], Y[i] - Y[j]);
        }
    }
}

struct Edge {
    int u, v;
    double w;

    bool operator<(const Edge &b) const {
        return w < b.w;
    }
};

static int father[NMAX + 10];
static int m;
static Edge edge[NMAX * NMAX + 10];

inline int find(int u) {
    return father[u] ? father[u] = find(father[u]) : u;
}

inline void link(int u, int v) {
    u = find(u);
    v = find(v);

    if (u != v)
        father[u] = v;
}

void update(double v) {
    m = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            edge[++m] = {i, j, pow(dist[i][j] - v, 2)};
        }
    }

    memset(father, 0, sizeof(father));
    sort(edge + 1, edge + m + 1);
    double sumx = 0.0, sumx2 = 0.0;
    for (int i = 1; i <= m; i++) {
        Edge &e = edge[i];

        if (find(e.u) != find(e.v)) {
            double d = dist[e.u][e.v];
            sumx += d;
            sumx2 += d * d;
            link(e.u, e.v);
        }
    }

    ans = min(ans, sqrt((sumx2 - sumx * sumx / (n - 1)) / (n - 1)));
}

int main() {
#ifdef USE_FILE_IO
    freopen("mst.in", "r", stdin);
    freopen("mst.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);

    while (T--) {
        initialize();

        ans = 1e100;
        for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
        for (int c = a + 1; c <= n; c++) {
        for (int d = c + 1; d <= n; d++) {
            update((dist[a][b] + dist[c][d]) / 2 + EPSILON);
        }}}}

        update(0);
        printf("%.12lf\n", ans);
    }

    return 0;
}
