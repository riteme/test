#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>

using namespace std;

typedef double d64;

#define SMAX (1 << 12)
#define BMAX (1 << 6)

#define take(S, i) (((S) >> (i)) & 1)

int n, m;

int encode(int a[6]) {
    int s = 0;
    for (int i = 0; i < m; i++)
        s |= a[i] << (2 * i);
    return s;
}

void decode(int s, int a[6]) {
    for (int i = 0; i < m; i++, s >>= 2)
        a[i] = s & 0x3;
}

int nS, nB;
bool ok[SMAX];
int to[SMAX][BMAX];
int pa[16];
d64 p[6][6];

int find(int x) {
    return pa[x] ? pa[x] = find(pa[x]) : x;
}

void link(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y)
        pa[x] = y;
}

void linkup(int S, int B, int a[6]) {
    int lp[4] = {0};
    for (int i = 0; i < m; i++) if (a[i]) {
        if (lp[a[i]])
            link(lp[a[i]], i + 1);
        lp[a[i]] = i + 1;
    }

    for (int i = 0; i < m; i++)
    if (a[i] && !take(B, i))
        link(i + 1, m + i + 1);

    for (int i = 1; i < m; i++)
    if (!take(B, i - 1) && !take(B, i))
        link(m + i, m + i + 1);
}

void relabel(int B, int a[6]) {
    int id[16] = {0}, cnt = 1;

    for (int i = 0; i < m; i++)
    if (a[i] == 1) {
        int x = find(i + 1);
        id[x] = 1;
        break;
    }

    for (int i = 0; i < m; i++)
    if (take(B, i))
        a[i] = 0;
    else {
        int x = find(m + i + 1);
        if (!id[x])
            id[x] = ++cnt;
        a[i] = id[x];
    }
}

bool valid(int a[6]) {
    bool has = false;
    for (int i = 0; i < m; i++) {
        has |= a[i] == 1;
        if (a[i] < 0 || a[i] > 3)
            return false;
    }
    return has;
}

void initialize() {
    for (int S = 0; S < nS; S++) {
        int a[6], b[6];
        decode(S, b);
        if (!valid(b))
            continue;

        for (int B = 0; B < nB; B++) {
            memcpy(a, b, sizeof(a));
            memset(pa, 0, sizeof(pa));
            linkup(S, B, a);
            relabel(B, a);
            int neo = encode(a);
            if (valid(a)) {
                to[S][B] = neo;
                ok[neo] = true;
            }
        }
    }
}

d64 f[SMAX], g[SMAX];
d64 row[BMAX];

d64 eval() {
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    g[1] = 1;

    for (int i = 0; i < n; i++) {
        for (int B = 0; B < nB; B++) {
            row[B] = 1;
            for (int j = 0; j < m; j++)
            if (take(B, j))
                row[B] *= p[i][j];
            else
                row[B] *= 1 - p[i][j];
        }

        for (int S = 0; S < nS; S++) if (ok[S])
        for (int B = 0; B < nB; B++)
            f[to[S][B]] += g[S] * row[B];
        memcpy(g, f, sizeof(g));
        memset(f, 0, sizeof(f));
    }

    d64 ans = 0;
    for (int S = 0; S < nS; S++)
    if (ok[S] && (S >> (2 * m - 2)) == 1)
        ans += g[S];
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    nB = 1 << m;
    nS = 1 << (2 * m);
    for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        scanf("%lf", &p[i][j]);

    initialize();

    d64 std = eval();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            d64 prior = p[i][j];
            p[i][j] = 1;
            d64 likelihood = eval();
            d64 posterior = likelihood * prior / std;
            printf("%.6lf ", posterior);
            p[i][j] = prior;
        }
        puts("");
    }

    return 0;
}