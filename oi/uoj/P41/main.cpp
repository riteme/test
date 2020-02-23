#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 200
#define MMAX 400

static int n, m;
static int c[NMAX + 10];
static int a[NMAX + 10][MMAX + 10];
static int t[NMAX + 10][NMAX + 10];
static int mc[2 * NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", a[i] + j);
            t[i][a[i][j]] = j;
        }

        queue<int> q;
        memset(mc, 0, sizeof(mc));
        for (int i = 1; i <= n; i++) {
            c[i] = 1;
            q.push(i);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int &i = c[u]; i <= m; i++) if (a[u][i]) {
                int v = n + a[u][i];
                if (!mc[v] || t[mc[v]][a[u][i]] < t[u][a[u][i]]) {
                    q.push(mc[v]);
                    mc[mc[v]] = 0;
                    mc[v] = u;
                    mc[u] = v;
                    break;
                }
            }
        }

        for (int i = 1; i <= n; i++)
            printf("%d ", mc[i] - n);
        puts("");
    }

    return 0;
}
