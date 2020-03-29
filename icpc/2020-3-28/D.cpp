#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define L 0
#define R 1

struct Circle {
    double x, y, r;
} c[NMAX + 10];
int ci[NMAX + 10];
int pa[NMAX + 10], ch[NMAX + 10][2];
int val[NMAX + 10], sum[NMAX + 10];

void update(int x) {
    // if (!x) return;
    sum[x] = val[x] + sum[ch[x][L]] + sum[ch[x][R]];
}

void rot(int x, int c) {
    int y = ch[x][c];
    assert(x);
    assert(y);
    ch[x][c] = ch[y][c^1];
    ch[y][c^1] = x;

    pa[ch[x][c]] = x;
    if (pa[x])
        ch[pa[x]][x == ch[pa[x]][R]] = y;
    pa[y] = pa[x];
    pa[x] = y;

    update(x);
    update(y);
}

void splay(int x, int t = 0) {
    if (!x) return;
    while (pa[x] != t) {
        int p = pa[x], g = pa[p];
        int cp = x == ch[p][R];
        int cg = p == ch[g][R];
        if (g && cp == cg)
            rot(g, cg);
        rot(p, cp);
    }
}

int n;

double key(int i, double x) {
    int j = i > n ? i - n : i;
    double dx = x - c[j].x;
    double dy = sqrt(c[j].r*c[j].r - dx*dx);
    return i > n ? c[j].y - dy : c[j].y + dy;
}

int bisect(int u, double x, double p) {
    int r = 0;
    while (u) {
        double y = key(u, x);
        if (y >= p) {
            r = u;
            u = ch[u][R];
        } else u = ch[u][L];
    }

    return r;
}

void initialize() {
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &c[i].x, &c[i].y, &c[i].r);

    for (int i = 1; i <= n; i++) {
        ci[i] = ci[n + i] = i;
        pa[i] = 0;
        pa[n + i] = i;
        ch[i][L] = ch[n + i][L] = ch[n + i][R] = 0;
        ch[i][R] = n + i;
        val[i] = sum[i] = 1;
        val[n + i] = sum[n + i] = -1;
    }
}

struct Event {
    double x;
    int i;
    int in;

    bool operator<(const Event &z) const {
        return x < z.x;
    }
};

Event ev[NMAX + 10];

int rms(int x) {
    while (ch[x][R])
        x = ch[x][R];
    return x;
}

void solve() {
    initialize();
    for (int i = 1, t = 0; i <= n; i++) {
        ev[t++] = {c[i].x - c[i].r, i, 1};
        ev[t++] = {c[i].x + c[i].r, i, 0};
    }
    sort(ev, ev + 2 * n);

    int tr = 0;
    int ans = 0;
    for (int j = 0; j < 2 * n; j++) {
        auto &e = ev[j];
        int i = e.i;
        if (e.in) {
            int u = bisect(tr, e.x, c[i].y);
            splay(u);
            int v = u ? ch[u][R] : tr;
            ch[u][R] = 0;
            ch[i][L] = u;
            ch[n + i][R] = v;
            pa[v] = n + i;
            pa[u] = i;
            update(u);
            update(n + i);
            update(i);
            ans = max(ans, sum[u] + 1);
            tr = i;
        } else {
            splay(i);
            splay(n + i, i);
            assert(ch[n + i][L] == 0);
            int u = rms(ch[i][L]);
            int v = ch[n + i][R];
            if (u) {
                splay(u, i);
                tr = u;
                ch[u][R] = v;
                pa[v] = u;
                pa[u] = 0;
                update(u);
            } else {
                tr = v;
                pa[v] = 0;
            }
        }
    }

    printf("%d\n", ans);
}

int main() {
    while (scanf("%d", &n) != EOF)
        solve();
    return 0;
}