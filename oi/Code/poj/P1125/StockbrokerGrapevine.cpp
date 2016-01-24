/**
 * StockbroketGrapevine
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 100
#define INFTY 100000000
#define BROKEN_GRAPH "disjoint"

static int n;
static int G[NMAX + 10][NMAX + 10];
static int dist[NMAX + 10][NMAX + 10];

void initialize() {
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            dist[x][y] = G[x][y] = INFTY;
        }  // for
    }      // for

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);

        while (x > 0) {
            int v, w;
            scanf("%d%d", &v, &w);

            dist[i][v] = G[i][v] = min(G[i][v], w);

            x--;
        }  // while
    }      // for

    for (int i = 1; i <= n; i++) {
        dist[i][i] = G[i][i] = 0;
    }  // for
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }  // for j
        }      // for i
    }          // for k
}  // function floyd

int main() {
    while (scanf("%d", &n) != EOF) {
        if (n == 0) {
            break;
        }

        initialize();

        floyd();

        int which = 0;
        int answer = INFTY;
        for (int i = 1; i <= n; i++) {
            int temporary = -INFTY;

            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    temporary = max(temporary, G[i][j]);
                }
            }  // for

            if (temporary < answer) {
                answer = temporary;
                which = i;
            }
        }  // for

        if (answer >= INFTY) {
            printf(BROKEN_GRAPH "\n");
        } else {
            printf("%d %d\n", which, answer);
        }
    }  // while

    return 0;
}  // function main
