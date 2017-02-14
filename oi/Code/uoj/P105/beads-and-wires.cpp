#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 200000

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n;
static vector<Edge *> G[NMAX + 10];
static int f[NMAX + 10][2];
static int d1[NMAX + 10], d2[NMAX + 10];
static int p1[NMAX + 10], p2[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        Edge *e = new Edge(u, v, c);
        G[u].push_back(e);
        G[v].push_back(e);
    }  // for
}

inline void update(int u, int v, int d) {
    if (d > d1[u]) {
        d2[u] = d1[u], p2[u] = p1[u];
        d1[u] = d, p1[u] = v;
    } else if (d > d2[u])
        d2[u] = d, p2[u] = v;
}

void dp(int x, int father = 0) {
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (v == father)
            continue;

        dp(v, x);

        int ret = max(e->w + f[v][1], f[v][0]);
        f[x][0] += ret;
        int d = e->w + f[v][0] - ret;
        update(x, v, d);
    }  // for

    f[x][1] = f[x][0] + d1[x];
}

static int answer;

void dfs(int x, int father) {
    answer = max(answer, f[x][0]);

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (v == father)
            continue;

        int x0 = f[x][0], x1 = f[x][1], v0 = f[v][0], v1 = f[v][1];
        int vd1 = d1[v], vp1 = p1[v], vd2 = d2[v], vp2 = p2[v];

        int val1 = max(e->w + f[v][1], f[v][0]);
        f[x][0] -= val1, f[x][1] -= val1;

        if (p1[x] == v) {
            if (p2[x])
                f[x][1] -= d1[x] - d2[x];
            else
                f[x][1] = INT_MIN;
        }

        int val2 = max(e->w + f[x][1], f[x][0]);
        int d = e->w + f[x][0] - val2;
        if (d > d1[v]) {
            if (p1[v])
                f[v][1] += d - d1[v];
            else
                f[v][1] = d;

            d2[v] = d1[v], p2[v] = p1[v];
            d1[v] = d, p1[v] = x;
        } else if (d > d2[v])
            d2[v] = d, p2[v] = x;

        f[v][0] += val2, f[v][1] += val2;

        dfs(v, x);

        f[x][0] = x0, f[x][1] = x1;
        f[v][0] = v0, f[v][1] = v1;
        d1[v] = vd1, p1[v] = vp1;
        d2[v] = vd2, p2[v] = vp2;
    }  // for
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        d1[i] = d2[i] = INT_MIN;
    }  // for

    dp(1);
    dfs(1, 0);
    printf("%d\n", answer);

    return 0;
}  // function main
