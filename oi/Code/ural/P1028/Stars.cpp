//
// Copyright 2015 riteme
//

#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 15000
#define XMAX 32000

static int n;
static int xmax;
static int c[XMAX + 10];
static int x[NMAX + 10];
static int cnt[XMAX + 10];

void initialize();
void quit();

inline int read() {
    int nx = 0;
    char ch = getchar();
    while (ch < '0' or ch > '9') ch = getchar();
    while ('0' <= ch and ch <= '9') nx = nx * 10 + ch - '0', ch = getchar();

    return nx;
}

inline int query(int r) {
    int result = 0;

    for (; r; r -= r & (-r)) result += c[r];

    return result;
}

inline void insert(int r) {
    for (; r <= xmax; r += r & (-r)) c[r] += 1;
}

int main() {
    initialize();

    for (int i = 1; i <= n; i++) {
        cnt[query(x[i])]++;
        insert(x[i]);
    }  // for

    quit();
    return 0;
}  // function main

void initialize() {
    // scanf("%d", &n);
    n = read();
    xmax = 0;

    for (int i = 1; i <= n; i++) {
        int x0, y0;
        // scanf("%d %d", &x0, &y0);
        x0 = read();
        y0 = read();

        x[i] = x0 + 1;

        if (xmax < x[i]) xmax = x[i];
    }  // for

    memset(c, 0, XMAX * sizeof(int));
    memset(cnt, 0, XMAX * sizeof(int));
}

void quit() {
    for (int i = 0; i < n; i++) { printf("%d\n", cnt[i]); }  // for
}
