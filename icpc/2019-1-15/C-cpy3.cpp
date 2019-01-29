#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 250000
#define BOUND 1e13L
#define INF 1e14L
#define EPS 1e-9L
#define TMAX 150

typedef long long i64;
typedef long double f8;

struct Edge { int v, w, nxt; };

static int n, K, m = 1, T[NMAX + 10];
static Edge e[NMAX * 2 + 10];
static f8 f[NMAX + 10][3], mi;
static int g[NMAX + 10][3];

inline void chkmax(int &a, int b) {
    if (b > a) a = b;
}

inline void update(int x, int p, f8 v, int c) {
    //if (fabs(v - f[x][p]) < EPS) g[x][p] = max(g[x][p], c);
    /*else*/ if (v > f[x][p]) {
        f[x][p] = v;
        g[x][p] = c;
    }
}

void cnt(int x, int fa) {
    for (int i = T[x]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        cnt(v, x);
        chkmax(g[x][1], g[v][2] + g[x][1]);
        chkmax(g[x][1], g[v][0] + 1 + g[x][0]);
        chkmax(g[x][0], g[v][2] + g[x][0]);
    }
    g[x][2] = max(g[x][0], g[x][1]);
}

void _eval(int x, int fa) {
    f[x][1] = -INF;
    for (int i = T[x]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        _eval(v, x);
        update(x, 1, f[v][2] + f[x][1], g[v][2] + g[x][1]);
        update(x, 1, f[v][0] + e[i].w - mi + f[x][0], g[v][0] + 1 + g[x][0]);
        update(x, 0, f[v][2] + f[x][0], g[v][2] + g[x][0]);
    }
    update(x, 2, f[x][0], g[x][0]);
    update(x, 2, f[x][1], g[x][1]);
}

void eval(int x) {
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    _eval(x, 0);
}

inline i64 near(f8 x) {
    i64 r = x + 0.5L;
    if (fabs(r + 1 - x) < fabs(r - x)) r = r + 1;
    else if (fabs(r - 1 - x) < fabs(r - x)) r = r - 1;
    return r;
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[m] = {v, w, T[u]};
        e[m + 1] = {u, w, T[v]};
        T[u] = m;
        T[v] = m + 1;
        m += 2;
    }

    cnt(1, 0);
    if (g[1][2] < K) {
        puts("Impossible");
        return 0;
    }

    f8 l = -BOUND, r = BOUND;
    for (int i = 0; i < TMAX; i++) {
        mi = (l + r) * 0.5L;
        eval(1);
        if (g[1][2] > K) l = mi;
        else r = mi;
    }
    mi = (l + r) * 0.5L;
    eval(1);
    printf("%lld\n", near(f[1][2] + K * mi));
    return 0;
}
