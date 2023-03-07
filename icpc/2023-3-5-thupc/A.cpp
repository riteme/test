#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int n;
i64 w[NMAX + 10];
int h[NMAX + 10], s[NMAX + 10];
vector<int> G[NMAX + 10];
i64 a[NMAX + 10];

void dfs(int u, int d) {
    h[u] = d;
    for (int v : G[u]) {
        dfs(v, d + 1);
        s[u] += 1 + s[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", w + i);
    }
    for (int v = 2; v <= n; v++) {
        int u;
        scanf("%d", &u);
        G[u].push_back(v);
    }
    dfs(1, 0);
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += -w[i] + 2 * (s[i] - h[i]);
        a[i] = 2 * (w[i] - s[i] + h[i]);
    }
    sort(a + 1, a + n + 1);
    // for (int i = n; i >= 1; i -= 2) {
    //     ans -= a[i];
    // }
    // for (int i = n - 1; i >= 1; i -= 2) {
    for (int i = 2; i <= n; i += 2) {
        ans += a[i];
    }
    for (int i = 1; i <= n; i++) {
        ans -= w[i];
    }
    printf("%lld\n", ans / 2);
    return 0;
}
