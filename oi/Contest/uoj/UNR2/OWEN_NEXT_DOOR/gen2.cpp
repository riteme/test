#include <cstdio>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100000

static int n, m, _;
static vector<int> G[NMAX + 10];
static int f[NMAX + 10];

void initialize() {
    scanf("%d%d%d%d", &n, &m, &_, &_);

    char buf[4];
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
    }  // for

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }  // for
}

int dp(int u) {
    if (f[u])
        return f[u];

    f[u] = 1;

    for (int v : G[u]) {
        f[u] = max(f[u], dp(v) + 1);
    }  // foreach in G[u]

    return f[u];
}

int main() {
    initialize();

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp(i));
    }  // for

    printf("%d\n", ans);

    return 0;
}  // function main
