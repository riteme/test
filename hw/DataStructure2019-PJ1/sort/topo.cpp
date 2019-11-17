// FAKE
#include "protocol.h"

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

extern int n;
extern Pack s[500];
static int G[500][500];

void topo_sort(int *a, int n) {
    if (n <= 1) return;
    for (int i = 2; i <= n; i++) {
        int u = a[i - 1], v = a[i];
        if (s[u] < s[v]) {
            G[v][++G[v][0]] = u;
            //printf("[%d] %d → %d\n", n, v, u);
        } else {
            swap(a[i - 1], a[i]);
            G[u][++G[u][0]] = v;
            //printf("[%d] %d → %d\n", n, u, v);
        }
    }
    bool updated = true;
    bool used[500];
    int in[500];
    int a1[n + 10], n1 = 0;
    while (updated) {
        //printf("[%d] new stage\n", n);
        updated = false;
        memset(in, 0, sizeof(in));
        memset(used, 0, sizeof(used));
        for (int i = 1; i <= n; i++) {
            int u = a[i];
            for (int j = 1; j <= G[u][0]; j++) {
                int v = G[u][j];
                in[v]++;
            }
        }
        for (int c = 0; c < n; c += n1, n1 = 0) {
            for (int i = 1; i <= n; i++) {
                int u = a[i];
                if (!used[u] && in[u] == 0) {
                    a1[++n1] = u;
                    used[u] = true;
                }
            }
            for (int i = 1; i <= n1; i++) {
                int u = a1[i];
                for (int j = 1; j <= G[u][0]; j++) {
                    int v = G[u][j];
                    in[v]--;
                }
            }
            if (n1 > 1) {
                updated = true;
                //printf("[%d] recur: ", n);
                //for (int i = 1; i <= n1; i++)
                //    printf("%d ", a1[i]);
                //puts("");
                topo_sort(a1, n1);
                //printf("[%d] returned\n", n);
            } /*else printf("[%d] single: %d\n", n, a1[1]);*/
        }
    }
}

static bool mark[500];
void dfs(int x) {
    mark[x] = true;
    for (int i = 1; i <= G[x][0]; i++) {
        int v = G[x][i];
        if (!mark[v]) dfs(v);
    }
}

void sort() {
    int a[500];
    Pack ns[500];
    for (int i = 1; i <= n; i++)
        a[i] = i;
    topo_sort(a, n);
    for (int i = 1; i <= n; i++) {
        int u = a[i];
        memset(mark, 0, sizeof(mark));
        dfs(u);
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            cnt += mark[j];
        ns[cnt] = s[u];
    }
    memcpy(s, ns, sizeof(s));
}
