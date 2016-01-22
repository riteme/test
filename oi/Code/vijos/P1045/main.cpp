#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define VALID_OUTPUT "Need %.2f miles of cable"
#define INVALID_OUTPUT "Impossible"

struct Edge {
    int u, v;
    double w;

    int another(int x) {
        return x == u ? v : u;
    }

    bool operator<(const Edge b) const {
        return w < b.w;
    }
};  // struct Edge

static double s;
static int n;
static int m;
static double length;
static Edge edges[NMAX + 10];
static Edge *edgePtrs[NMAX + 10];
static int size;
static int set[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for

    size = n;
}

inline int find_set(int x) {
    if (x != set[x]) {
        set[x] = find_set(set[x]);
    }

    return set[x];
}

inline void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    if (x != y) {
        set[x] = y;
        size--;
    }
}

void initialize() {
    scanf("%lf %d", &s, &n);

    m = 1;
    int x, y;
    double w;

    make_set();
    while (scanf("%d %d %lf", &x, &y, &w) != EOF) {
        edges[m].u = x;
        edges[m].v = y;
        edges[m].w = w;
        edgePtrs[m] = &edges[m];

        // printf("Read edge: {u = %d, v = %d, w = %lf}\n", x, y, w);

        union_set(x, y);

        m++;
    }  // while
    m--;

    length = 0.0;
}

void quit() {
    if (length > s) {
        printf(INVALID_OUTPUT);

    } else {
        printf(VALID_OUTPUT, length);
    }
}

bool ptr_compare(const Edge *a, const Edge *b) {
    return *a < *b;
}

void kruskal() {
    make_set();

    sort(&edgePtrs[1], &edgePtrs[m] + 1, ptr_compare);

    int edgeCount = 0;
    int p = 1;
    while (edgeCount < n - 1 and p <= m) {
        int u = find_set(edgePtrs[p]->u);
        int v = find_set(edgePtrs[p]->v);

        if (u != v) {
            set[u] = v;
            length += edgePtrs[p]->w;
            edgeCount++;

            // printf("Add edge: {u = %d, v = %d, w = %lf}\n", u, v,
            // edgePtrs[p]->w);
        }

        p++;
    }  // while
}

int main() {
    initialize();

    if (size > 1) {
        printf(INVALID_OUTPUT);
        return 0;
    }

    kruskal();

    quit();
    return 0;
}  // function main
