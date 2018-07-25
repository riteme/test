#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 17
#define XMAX 101
#define SMAX (1 << 17)

static int n, S;
static double P, f[NMAX][SMAX], g[NMAX][SMAX], ans[NMAX][XMAX];
static int cnt[SMAX];

inline int mask(int n) {
    return (1 << n) - 1;
}

inline int push(int &s, int k, int &w) {
    if (s & mask(k)) {
        int c = cnt[s];
        s = 1 << k;
        w = 0;
        return c;
    }

    w = (s ^ (s + (1 << k))) - (1 << k);
    s += 1 << k;
    return 0;
}

double solve(int m, int x) {
    n = m;
    S = 1 << (n + 1);
    P = x / 100.0;
    for (int i = 0; i <= n; i++) for (int j = 0; j < S; j++)
        f[i][j] = g[i][j] = 0;
    g[0][0] = 1;

    double ret = 0;
    for (int i = 0; i <= n; i++) for (int s = 0; s < S; s++) {
        int used = i + cnt[s];
        if (used == n) ret += f[i][s];
        else if (used < n) {
            int ni = i, ns = s, w;
            ni += push(ns, 0, w);
            g[ni][ns] += g[i][s] * (1 - P);
            f[ni][ns] += (f[i][s] + w * g[i][s]) * (1 - P);
            ni = i; ns = s;
            ni += push(ns, 1, w);
            g[ni][ns] += g[i][s] * P;
            f[ni][ns] += (f[i][s] + w * g[i][s]) * P;
        }
    }

    return ret * 2;
}

int main() {
    for (int i = 1; i < SMAX; i++)
        cnt[i] = cnt[i >> 1] + (i & 1);
    for (int i = 1; i < NMAX; i++) for (int x = 0; x < XMAX; x++)
        ans[i][x] = solve(i, x);

    for (int i = 0; i < NMAX; i++) {
        printf("{");
        for (int j = 0; j < XMAX; j++) {
            if (j > 0) printf(",");
            printf("%.7lf", ans[i][j]);
        }
        printf("},");
    }

    return 0;
}
