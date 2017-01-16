#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 30000
#define MMAX 50000

static int n, m, k;
static vector<int> G[NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }
}

static bool marked[NMAX + 10];

static bool dfs(int x) {
    if (x == n)
        return n == k || marked[k];

    marked[x] = true;
    bool flag = false;
    for (int v : G[x]) {
        if (!marked[v]) {
            if (dfs(v)) {
                flag = true;
                break;
            }
        }
    }

    marked[x] = false;
    return flag;
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        memset(marked, 0, sizeof(marked));
        puts(dfs(1) ? "YES" : "NO");
    }

    return 0;
}
