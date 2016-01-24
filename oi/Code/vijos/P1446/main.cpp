/**
 * 最短路上的统计
 * tags: Floyd
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 100
#define INFTY 10000000

static int n;
static int m;
static int G[NMAX + 10][NMAX + 10];
static int q;

void initialize() {
    scanf("%d%d", &n, &m);

    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            if (x == y) {
                G[x][y] = 0;
            } else {
                G[x][y] = INFTY;
            }
        }  // for
    }      // for

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }  // for

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }  // for
        }      // for
    }          // for
}

int query(int a, int b) {
    int result = 0;

    for (int i = 1; i <= n; i++) {
        if (G[a][i] + G[i][b] == G[a][b]) {
            result++;
        }
    }  // for

    return result;
}

int main() {
    initialize();

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        printf("%d\n", query(a, b));
    }  // for

    return 0;
}  // function main
