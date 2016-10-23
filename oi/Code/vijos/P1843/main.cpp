#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 10000
#define MMAX 50000
#define LOGN 15
// #define NMAX 100
// #define MMAX 100
// #define LOGN 8

struct Edge {
    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }

    bool operator<(const Edge &b) const {
        return w > b.w;
    }
};  // struct Edge

static int n, m, q;
static Edge edges[MMAX + 10];
static vector<Edge *> G[NMAX + 10];
static Edge *father_edge[NMAX + 10];
static int set[NMAX + 10];
static int depth[NMAX + 10];
static int f[NMAX + 10][LOGN + 1];
static int minv[NMAX + 10][LOGN + 1];
static bool marked[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

inline int find_set(int x) {
    return set[x] == x ? x : set[x] = find_set(set[x]);
}

static void kruskal() {
    make_set();
    sort(edges, edges + m);

    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int idu = find_set(u);
        int v = edges[i].v;
        int idv = find_set(v);

        if (idu == idv)
            continue;

        set[idu] = idv;
        G[u].push_back(edges + i);
        G[v].push_back(edges + i);
    }  // for
}

static void build(int x) {
    marked[x] = true;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i]->either(x);

        if (marked[v])
            continue;

        father_edge[v] = G[x][i];
        depth[v] = depth[x] + 1;
        build(v);
    }  // for
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }  // for

    kruskal();

    for (int i = 1; i <= n; i++) {
        if (!marked[i])
            build(find_set(i));
    }  // for

    for (int i = 1; i <= n; i++) {
        if (father_edge[i]) {
            f[i][0] = father_edge[i]->either(i);
            minv[i][0] = father_edge[i]->w;
        } else {
            f[i][0] = 0;
            minv[i][0] = INT_MAX;
        }
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
            minv[i][j] = min(minv[i][j - 1], minv[f[i][j - 1]][j - 1]);
        }  // for
    }      // for
}

static int solve(int x, int y) {
    if (depth[x] < depth[y])
        swap(x, y);

    int answer = INT_MAX;
    int dist = depth[x] - depth[y];
    for (int i = LOGN; i >= 0; i--) {
        if (dist & (1 << i)) {
            answer = min(answer, minv[x][i]);
            x = f[x][i];
        }
    }  // for

    if (x == y)
        return answer;

    for (int i = LOGN; i >= 0; i--) {
        if (f[x][i] != f[y][i]) {
            answer = min(answer, min(minv[x][i], minv[y][i]));
            x = f[x][i];
            y = f[y][i];
        }
    }  // for

    return min(answer, min(minv[x][0], minv[y][0]));
}

int main() {
    initialize();

    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);

        if (find_set(x) != find_set(y))
            puts("-1");
        else
            printf("%d\n", solve(x, y));
    }  // while

    return 0;
}  // function main
