#pragma GCC optimize(3)

#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define NMAX 100
#define TMAX 100

struct UnionFind {
    int fa[NMAX + 10];

    int find(int x) {
        return fa[x] ? fa[x] = find(fa[x]) : x;
    }

    int &operator[](const size_t i) {
        return fa[i];
    }
};

static int n, m, deg[NMAX + 10];
static UnionFind con, bak;
static bool G[NMAX + 10][NMAX + 10];
static struct Edge {
    int u, v;
} e[NMAX * NMAX + 10];
static bool used[NMAX * NMAX + 10];

static bool mark[NMAX + 10];
static bool T[NMAX + 10][NMAX + 10];
bool dfs(int x) {
    mark[x] = true;
    bool r = deg[x];
    for (int v = 1; v <= n; v++) if (!G[x][v] && !mark[v]) {
        if (dfs(v)) {
            T[x][v] = T[v][x] = 1;
            r ^= 1;
        }
    }
    return r;
}

int main() {
    scanf("%d%d", &n, &m);
    int c = n;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
        deg[u] ^= 1;
        deg[v] ^= 1;
        u = con.find(u);
        v = con.find(v);
        if (u != v) {
            con[u] = v;
            c--;
        }
    }
    bak = con;
    m = 0;
    for (int x = 1; x <= n; x++) for (int y = x + 1; y <= n; y++)
        if (!G[x][y]) e[m++] = {x, y};
    srand(time(NULL));
    bool ok = false;
    for (int t = 0; !ok && t < TMAX; t++) {
        random_shuffle(e, e + m);
        con = bak;
        for (int i = 0, d = 0; c > d + 1; i++) {
            int u = con.find(e[i].u), v = con.find(e[i].v);
            if (u != v) {
                con[u] = v;
                used[i] = true;
                G[e[i].u][e[i].v] = G[e[i].v][e[i].u] = 1;
                deg[e[i].u] ^= 1;
                deg[e[i].v] ^= 1;
                d++;
            }
        }
        ok = true;
        memset(mark, 0, sizeof(mark));
        for (int i = 1; i <= n && ok; i++)
            if (!mark[i]) ok &= !dfs(i);
        if (!ok) {
            for (int i = 0; i < m; i++) if (used[i]) {
                used[i] = false;
                G[e[i].u][e[i].v] = G[e[i].v][e[i].u] = 0;
                deg[e[i].u] ^= 1;
                deg[e[i].v] ^= 1;
            }
            for (int x = 1; x <= n; x++) for (int y = x + 1; y <= n; y++) if (T[x][y])
                T[x][y] = T[y][x] = 0;
        }
    }
    if (ok) {
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            if (used[i] || T[e[i].u][e[i].v]) {
                cnt++;
                used[i] = true;
            }
        }
        printf("%d\n", cnt);
        for (int i = 0; i < m; i++)
            if (used[i]) printf("%d %d\n", e[i].u, e[i].v);
    } else puts("-1");
    return 0;
}
