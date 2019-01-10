#include <cmath>
#include <cstdio>
#include <cstring>
 
#include <algorithm>
 
using namespace std;

typedef __int128_t i8;
 
#define NMAX 100
#define INF shit(1, 120)
#define TMAX 100
#define EPS 1e-10
 
static int n, m, K;
static i8 G[NMAX + 10][NMAX + 10];
static int acc[NMAX + 10];
static i8 _dp1[NMAX + 10], _dp2[NMAX + 10];

inline i8 shit(i8 a, int b) {
    while (b--) a *= 2;
    return a;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &K);
        memset(G, 0x3f, sizeof(G));
        for (int i = 0; i < m; i++) {
            int u, v, _w;
            scanf("%d%d%d", &u, &v, &_w);
            i8 w = _w;
            w = shit(w, TMAX);
            if (u == v) continue;
            G[u][v] = G[v][u] = min(G[u][v], w);
        }
        for (int i = 1; i <= n; i++) G[i][i] = 0;
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
            G[i][j] = min(G[i][k] + G[k][j], G[i][j]);
        int anst = 0;
        for (int i = 1; i <= K; i++) {
            scanf("%d", acc + i);
            if (acc[i] == 1) anst = 1;
        }
        i8 v = anst + 1;
        i8 ans = G[1][n] / v;
        i8 *dp1 = _dp1, *dp2 = _dp2;
        for (int i = 1; i <= K; i++) {
            if (acc[i] == n) continue;
            if (acc[i] == 1) dp1[i] = INF;
            else dp1[i] = G[1][acc[i]] / v;
        }
        v *= 2;
        swap(dp1, dp2);
        for (int i = anst + 1; i <= TMAX + 1; i++) {
            for (int j = 1; j <= K; j++) dp1[j] = INF;
            for (int j = 1; j <= K; j++) {
                if (acc[j] == n) continue;
                i8 t = G[acc[j]][n] / v + dp2[j];
                if (t < ans) {
                    ans = t;
                    anst = i;
                } else if (t == ans) anst = i;
                for (int k = 1; k <= K; k++) {
                    if (j == k || acc[k] == n) continue;
                    dp1[k] = min(dp1[k], dp2[j] + G[acc[j]][acc[k]] / v);
                }
            }
            v *= 2;
            swap(dp1, dp2);
        }
 
        for (int i = 1; i <= K; i++) if (acc[i] == n) {
            anst++;
            break;
        }
        printf("%.12lf ", (double) ans / shit(1, TMAX));
        if (anst > TMAX) puts("Burst!");
        else printf("%d\n", anst);
    }
    return 0;
}
