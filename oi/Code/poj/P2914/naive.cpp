/**
 * Stoer-Wagner algorithm
 * O(n^3) implementation with adjacency matrix.
 */

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500

static int n, m;
static int G[NMAX + 10][NMAX + 10];

void initialize() {
    memset(G, 0, sizeof(G));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        u++;
        v++;
        G[u][v] += w;
        G[v][u] += w;
    }  // for
}

static bool marked[NMAX + 10];
static bool visited[NMAX + 10];
static int weight[NMAX + 10];

int find_mincut(int cnt, int &s, int &t) {
    memcpy(visited, marked, sizeof(visited));
    memset(weight, 0, sizeof(weight));

    while (cnt--) {
        int u = 0;

        for (int i = 1; i <= n; i++) {
            if (!visited[i] && weight[i] >= weight[u])
                u = i;
        }  // for

        s = t;
        t = u;
        visited[u] = true;
        for (int i = 1; i <= n; i++) {
            weight[i] += G[u][i];
        }  // for
    }      // while

    return weight[t] - G[t][t];
}

int mincut(int cnt) {
    if (cnt < 2)
        return INT_MAX;

    int s, t;
    int ans = find_mincut(cnt, s, t);

    marked[t] = true;
    for (int i = 1; i <= n; i++) {
        int w = G[t][i];
        G[s][i] += w;
        G[i][s] += w;
    }  // for

    return min(ans, mincut(cnt - 1));
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();

        memset(marked, 0, sizeof(marked));
        printf("%d\n", mincut(n));
    }  // while

    return 0;
}  // function main
