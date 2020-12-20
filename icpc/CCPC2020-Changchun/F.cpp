#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;
constexpr int AMAX = 1 << 20;
constexpr int LOGN = 20;

int j, n, a[NMAX + 10], sz[NMAX + 10];
int cur, seq[NMAX + 10], in[NMAX + 10], out[NMAX + 10];
vector<int> G[NMAX + 10];
i64 ans, cnt[AMAX][2];

void dfs(int x, int p) {
    in[x] = ++cur;
    seq[cur] = x;
    sz[x] = 1;
    for (int v : G[x]) if (v != p) {
        dfs(v, x);
        sz[x] += sz[v];
    }
    out[x] = cur;
}

void eval(int u, int e) {
    for (int i = in[u]; i <= out[u]; i++) {
        int x = seq[i];
        int b = (x >> j) & 1;
        ans += cnt[a[x] ^ e][b ^ 1] << j;
    }
}

void scan(int u, int d) {
    for (int i = in[u]; i <= out[u]; i++) {
        int x = seq[i];
        int b = (x >> j) & 1;
        cnt[a[x]][b] += d;
    }
}

void solve(int x, int p) {
    int u = 0;
    for (int v : G[x]) {
        if (v != p && sz[v] > sz[u])
            u = v;
    }

    for (int v : G[x]) if (v != p && v != u) {
        solve(v, x);
        scan(v, -1);
    }

    if (u)
        solve(u, x);

    int b = (x >> j) & 1;
    ans += cnt[0][b ^ 1] << j;
    cnt[a[x]][b]++;

    for (int v : G[x]) if (v != p && v != u) {
        eval(v, a[x]);
        scan(v, +1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);

    for (j = 0; j < LOGN; j++) {
        memset(cnt, 0, sizeof(cnt));
        solve(1, 0);
    }

    printf("%lld\n", ans);
    return 0;
}
