#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, m;
static bool mark[NMAX + 10];
static vector<int> G[NMAX + 10];
static double E[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
        }
        queue<int> q;
        q.push(1);
        memset(mark, 0, sizeof(mark));
        memset(E, 0, sizeof(E));
        mark[1] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int k = G[u].size();
            double val = k ? E[u] + 1.0 / k : 0;
            for (int v : G[u]) {
                if (!mark[v]) {
                    q.push(v);
                    mark[v] = true;
                }
                E[v] += val / k;
            }
        }
        printf("%.2lf\n", E[n]);
    }
    return 0;
}
