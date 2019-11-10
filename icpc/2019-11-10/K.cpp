#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 18
#define SMAX (1 << NMAX)

static int n, m;
static int a[NMAX + 10], id[NMAX + 10];
static int sum[SMAX];
static int f[SMAX], g[SMAX];

void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        a[u] -= w;
        a[v] += w;
    }
    int n0 = 0;
    for (int i = 0; i < n; i++) if (a[i]) {
        id[n0] = i;
        a[n0++] = a[i];
    }
    n = n0;
}

struct Record {
    int u, v, w;
};

static int cnt;
static Record r[NMAX + 10];

void emit(int s) {
    //printf("s = %d\n", s);
    static int pos[NMAX + 10], neg[NMAX + 10], pc, nc;

    if (g[s]) {
        emit(s ^ g[s]);
        emit(g[s]);
    } else {
        pc = nc = 0;
        for (int i = 0; i < n; i++) if ((s >> i) & 1) {
            if (a[i] > 0) pos[pc++] = i;
            else neg[nc++] = i;
        }

        for (int i = 0, j = 0; i < pc && j < nc; ) {
            int x = pos[i], y = neg[j];
            assert(a[x]);
            assert(a[y]);
            if (a[x] >= -a[y]) {
                r[cnt++] = {id[x], id[y], -a[y]};
                a[x] += a[y];
                j++;
            } else {
                r[cnt++] = {id[x], id[y], a[x]};
                a[y] += a[x];
                i++;
            }
        }
    }
}

int main() {
    initialize();

    for (int i = 0; i < n; i++)
        sum[1 << i] = a[i];
    for (int s = 1; s < (1 << n); s++) {
        int i = s & -s;
        sum[s] = sum[s ^ i] + sum[i];
    }

    for (int s = 1; s < (1 << n); s++) if (sum[s] == 0) {
        f[s] = 1;
        for (int t = (s - 1) & s; t; t = (t - 1) & s) if (sum[t] == 0) {
            int c = f[s ^ t] + f[t];
            if (c > f[s]) {
                f[s] = c;
                g[s] = t;
            }
        }
    }

    emit((1 << n) - 1);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++)
        printf("%d %d %d\n", r[i].u, r[i].v, r[i].w);

    return 0;
}
