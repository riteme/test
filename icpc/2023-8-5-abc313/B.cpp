#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 50;

int n, m, cnt;
vector<int> G[NMAX + 10];
bool mark[NMAX + 10];

void dfs(int u) {
    cnt++;
    mark[u] = true;
    for (int v : G[u]) {
        if (!mark[v])
            dfs(v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }

    int ans = 0;
    for (int u = 1; u <= n; u++) {
        cnt = 0;
        memset(mark, 0, sizeof(mark));
        dfs(u);
        if (cnt == n) {
            if (ans == 0)
                ans = u;
            else if (ans > 0)
                ans = -1;
        }
    }

    if (ans == 0)
        ans = -1;
    printf("%d\n", ans);
    return 0;
}
