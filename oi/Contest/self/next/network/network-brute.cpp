#include <cstring>

#include "network.h"

#define NMAX 100000

static int n;
static int cnt;
static int set[NMAX + 10];
static int m, current;
static int U[NMAX + 10];
static int V[NMAX + 10];
static int T[NMAX + 10];

inline void make_set() {
    cnt = n;
    memset(set + 1, 0, sizeof(int) * n);
}

inline int find_set(int x) {
    return set[x] ? set[x] = find_set(set[x]) : x;
}

inline void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    if (x != y) {
        cnt--;
        set[x] = y;
    }
}

void initialize(int n, int q) {
    ::n = n;
}

void add_connection(int u, int v, int t) {
    m++;
    U[m] = u;
    V[m] = v;
    T[m] = t;
}

int query() {
    current++;
    make_set();

    for (int i = 1; i <= m; i++) {
        if (i + T[i] > current) {
            union_set(U[i], V[i]);
        }
    }

    return cnt;
}

void finalize() {}
