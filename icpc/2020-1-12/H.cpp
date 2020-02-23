#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define RMAX 200
#define NMAX (RMAX * RMAX)
#define BASE 19260817

typedef long long i64;
typedef unsigned long long u64;

int r, c;
char _m[RMAX + 10][RMAX + 10];
int m[RMAX + 10][RMAX + 10];
int mt[RMAX + 10][RMAX + 10];

void up() {
    for (int y = 1; y <= c; y++) {
        int p = 1;
        for ( ; p <= r && !mt[p][y]; p++) ;
        if (p > r)
            continue;
        for (int x = 1; p <= r; x++, p++) {
            mt[x][y] = mt[p][y];
            mt[p][y] = 0;
        }
    }
}

void dw() {
    for (int y = 1; y <= c; y++) {
        int p = r;
        for ( ; p && !mt[p][y]; p--) ;
        if (!p)
            continue;
        for (int x = r; p; x--, p--) {
            mt[x][y] = mt[p][y];
            mt[p][y] = 0;
        }
    }
}

void lt() {
    for (int x = 1; x <= r; x++) {
        int p = 1;
        for ( ; p <= c && !mt[x][p]; p++) ;
        if (p > c)
            continue;
        for (int y = 1; p <= c; y++, p++) {
            mt[x][y] = mt[x][p];
            mt[x][p] = 0;
        }
    }
} void rt() { for (int x = 1; x <= r; x++) { lt();

memcpy(mt, m, sizeof(m));
rt(); up(); lt(); dw();        int p = c;
        for ( ; p && !mt[x][p]; p--) ;
        if (!p)
            continue;
        for (int y = c; p; y--, p--) {
            mt[x][y] = mt[x][p];
            mt[x][p] = 0;
        }
    }
}

int n;
int p1[NMAX + 10], p2[NMAX + 10];

i64 solve() {
    scanf("%d%d", &r, &c);
    for (int i = 1; i <= r; i++)
        scanf("%s", _m[i] + 1);
    for (int x = 1; x <= r; x++)
    for (int y = 1; y <= c; y++)
    if (_m[x][y] == '#')
        m[x][y] = ++n;


    memcpy(mt, m, sizeof(m));
    up(); rt(); dw(); lt();
    for (int x = 1; x <= r; x++)
    for (int y = 1; y <= c; y++)
    if (m[x][y]) p1[m[x][y]] = mt[x][y];

    memcpy(mt, m, sizeof(m));
    rt(); up(); lt(); dw();
    for (int x = 1; x <= r; x++)
    for (int y = 1; y <= c; y++)
    if (m[x][y]) p2[m[x][y]] = mt[x][y];
}

int main() {
    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++)
        printf("Case %d: %lld\n", solve());
    return 0;
}