#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int INF = 0x3f3f3f3f;
constexpr int NMAX = 300;

int n, m;
int C[NMAX + 10][NMAX + 10];
int f[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i < n; i++) {
        f[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        C[u][v] = C[v][u] = w;
        f[u][v] = f[v][u] = w;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    int ans = INF;
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= n; b++) {
            if (!C[a][b])
                continue;

            int minc = INF;
            for (int c = 1; c <= n; c++) {
                if (c != a && c != b && C[a][c]) {
                    minc = min(minc, C[a][c] + f[c][b]);
                }
            }

            if (minc >= INF)
                continue;

            int cnt = 0;
            for (int c = 1; c <= n; c++) {
                if (c != a && c != b && C[a][c] && C[a][c] + f[c][b] == minc)
                    cnt++;
            }
            assert(cnt >= 1);

            int v = INF;
            for (int c = 1; c <= n; c++) {
                if (c != a && c != b && C[a][c]) {
                    if (cnt > 1 || C[a][c] + f[c][b] != minc)
                        v = min(v, C[a][c]);
                }
            }
            if (v < INF)
                ans = min(ans, minc + C[a][b] + v);
        }
    }

    printf("%d\n", ans < INF ? ans : -1);
    return 0;
}
