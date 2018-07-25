#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MMAX 300000
#define KMAX 1000000000

typedef long long i64;

static int n, m;
static i64 K;
static vector<int> G[NMAX + 10];
static i64 f[NMAX + 10];

i64 dp(int u) {
    if (f[u])
        return f[u];

    f[u] = 1;
    for (int v : G[u]) {
        f[u] += dp(v);
        f[u] = min((i64) KMAX + 10, f[u]);
    }

    return f[u];
}

void initialize() {
    scanf("%d%d%lld", &n, &m, &K);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
    }

}

int dfs(int u, i64 cnt) {
    cnt--;
    if (!cnt)
        return u;

    for (int v : G[u]) {
        if (f[v] < cnt)
            cnt -= f[v];
        else
            return dfs(v, cnt);
    }

    return -1;
}

static int timestamp;
static int seq[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];

void scan(int u) {
    in[u] = ++timestamp;
    seq[timestamp] = u;

    for (int v : G[u]) {
        scan(v);
    }

    out[u] = timestamp;
}

int main() {
#ifdef NDEBUG
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif
    initialize();

    if (n <= 1000) {
        for (int u = 1; u <= n; u++) {
            if (!f[u])
                dp(u);
        }

        for (int u = 1; u <= n; u++) {
            printf("%d\n", dfs(u, K));
        }
    } else {
        for (int u = 1; u <= n; u++) {
            if (!in[u])
                scan(u);
        }

        for (int u = 1; u <= n; u++) {
            if (in[u] + K - 1 <= out[u])
                printf("%d\n", seq[in[u] + K - 1]);
            else
                puts("-1");
        }
    }

    return 0;
}
