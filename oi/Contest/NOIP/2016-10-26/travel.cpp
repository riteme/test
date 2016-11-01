#pragma GCC optimize(3)

#define NDEBUG

#include <cassert>
#include <cstring>
#include <cstdio>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

#define NMAX 100000
#define MMAX 200000

static int n, m, q;

static int p1[MMAX + 10];
static int p2[MMAX + 10];
static int w[MMAX + 10];
static int sorted_edges[MMAX + 10];

static int X[NMAX + 10];
static int S[NMAX + 10];
static int answer[NMAX + 10];
static int sorted_querys[NMAX + 10];

static int set[NMAX + 10];
static int size[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
        size[i] = 1;
    }
}

inline int find_set(int x) {
    return set[x] == x ? x : set[x] = find_set(set[x]);
}

inline void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    if (x != y) {
        set[x] = y;
        size[y] += size[x];
    }
}

static bool cmp_edges(const int a, const int b) {
    return w[a] < w[b];
}

static bool cmp_querys(const int a, const int b) {
    return S[a] < S[b];
}

static void initialize() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= m; i++) {
        sorted_edges[i] = i;
        scanf("%d%d%d", p1 + i, p2 + i, w + i);
    }

    for (int i = 1; i <= q; i++) {
        sorted_querys[i] = i;
        scanf("%d%d", X + i, S + i);
    }

    sort(sorted_edges + 1, sorted_edges + m + 1, cmp_edges);
    sort(sorted_querys + 1, sorted_querys + q + 1, cmp_querys);
    make_set();
}

int main() {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    initialize();

    int i = 1, j = 1;
    while (j <= q) {
        while (i <= m && w[sorted_edges[i]] <= S[sorted_querys[j]]) {
            union_set(p1[sorted_edges[i]], p2[sorted_edges[i]]);
            i++;
        }

        int p = sorted_querys[j];
        answer[p] = size[find_set(X[p])];
        j++;
    }

    for (int i = 1; i <= q; i++)
        printf("%d\n", answer[i]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
