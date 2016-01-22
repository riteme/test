#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 10000

#define NO_ANSWER "No Answer"

struct Edge {
    int u;
    int v;
    int w;
};  // struct Edge

static int n;
static int m;
static int k;
static int total;
static int edge_count;
static Edge edges[MMAX + 10];
static Edge *edge_ptrs[MMAX + 10];
static int set[NMAX + 10];

bool compare(const Edge *a, const Edge *b) {
    return a->w < b->w;
}

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

inline int find_set(int x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

inline void union_set(int x, int y) {
    set[find_set(x)] = find_set(y);
}

void initialize() {
    scanf("%d %d %d", &n, &m, &k);

    int x, y, l;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &l);

        edges[i].u = x;
        edges[i].v = y;
        edges[i].w = l;
        edge_ptrs[i] = &edges[i];
    }  // for

    sort(edge_ptrs, edge_ptrs + m, compare);

    total = 0;
    edge_count = 0;
}

void krsukal() {
    make_set();

    int p = 0;
    while (edge_count < n - k and p < m) {
        int u = find_set(edge_ptrs[p]->u);
        int v = find_set(edge_ptrs[p]->v);

        if (u != v) {
            set[u] = v;
            total += edge_ptrs[p]->w;
            edge_count++;
        }

        p++;
    }  // while
}

int main() {
    initialize();

    krsukal();

    if (edge_count != n - k) {
        printf(NO_ANSWER);
    } else {
        printf("%d", total);
    }

    return 0;
}  // function main
