#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

int n;
vector<i64> wt[NMAX + 10];

void _main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        wt[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        wt[u].push_back(w);
        wt[v].push_back(w);
    }

    i64 ans = 0;
    for (int u = 1; u <= n; u++) {
        sort(wt[u].begin(), wt[u].end());
        for (int j = 1; j < wt[u].size(); j++) {
            ans += wt[u][0] + wt[u][j];
        }
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}