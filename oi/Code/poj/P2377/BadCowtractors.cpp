/**
 * Bas Cowtractors
 * tags: 最大生成树 Kruskal
 *     Kruskal算法，从最大的边开始处理
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 20000

struct Edge {
    int u;
    int v;
    int w;
};  // struct Edge

bool compare(const Edge &a, const Edge &b) {
    return a.w > b.w;
}

static int n, m;
static int total;
static int edge_count;
static Edge edges[MMAX + 10];
static int set[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

inline int find_set(int x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

void kruskal() {
    make_set();

    int index = 0;
    while (edge_count < n - 1 and index < m) {
        int u = find_set(edges[index].u);
        int v = find_set(edges[index].v);
        int w = edges[index].w;

        if (u != v) {
            edge_count++;
            set[u] = v;
            total += w;
        }

        index++;
    }  // while
}

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }  // for

    total = 0;
    edge_count = 0;
    sort(edges, edges + m, compare);
}

int main() {
    initialize();

    kruskal();

    if (edge_count != n - 1) {
        // printf("total: %d, edge_count: %d\n", total, edge_count);
        total = -1;
    }

    printf("%d", total);

    return 0;
}  // function main
