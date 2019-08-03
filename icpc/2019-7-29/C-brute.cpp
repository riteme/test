#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000

int n, K;
char d[NMAX + 10];
vector<int> G[NMAX + 10];

int dfs(int x, int fa, int sum) {
    sum = (sum * 10 + d[x]) % K;
    int ret = sum == 0;
    for (int v : G[x]) if (v != fa)
        ret += dfs(v, x, sum);
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%s", &n, &K, d + 1);
        for (int i = 1; i <= n; i++) {
            d[i] -= '0';
            G[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) ans += dfs(i, 0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
