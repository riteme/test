// LCA
// TLE 7/10

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define NMAX 100000

typedef int ntype;

void initialize();
void quit();

static ntype n, m;
static ntype root;
static ntype last;
static vector<ntype> T[NMAX + 1];
static map<pair<ntype, ntype>, ntype> LCA;
static ntype data[NMAX + 1];
static ntype ancestor[NMAX + 1];
static bool marked[NMAX + 1];

inline ntype read() {
    ntype x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }  // while

    return x;
}

inline void make_set(const ntype size) {
    for (ntype i = 1; i <= size; i++) data[i] = i;
}

inline ntype find_set(const ntype a) {
    if (a != data[a]) data[a] = find_set(data[a]);

    return data[a];
}

inline void union_set(const ntype a, const ntype b) {
    data[find_set(a)] = find_set(b);
}

void lca(const ntype u);

int main() {
    initialize();

    for (int cnt = 0; cnt < m; cnt++) {
        ntype x = read(), y = read();

        if (x == y)
            last ^= x;
        else {
            ntype rx = x ^ last;
            ntype ry = y ^ last;

            last = LCA[make_pair(min(rx, ry), max(rx, ry))];
        }

        printf("%d\n", last);
    }  // for

    quit();
    return 0;
}  // function main

void lca(const ntype u) {
    ancestor[find_set(u)] = u;

    for (int i = 0; i < T[u].size(); i++) {
        ntype v = T[u][i];

        lca(v);
        union_set(u, v);
        ancestor[find_set(u)] = u;
    }

    marked[u] = true;

    for (int v = 1; v <= n; v++) {
        if (marked[v])
            LCA[make_pair(min(u, v), max(u, v))] = ancestor[find_set(v)];
    }  // for
}

void initialize() {
    n = read();
    for (int i = 1; i <= n; i++) {
        ntype p = read();

        if (p == 0)
            root = i;
        else
            T[p].push_back(i);
    }  // for

    memset(ancestor, 0, sizeof(ancestor));
    memset(marked, false, sizeof(marked));

    make_set(n);
    lca(root);

    m = read();
    last = 0;
}

void quit() {}
