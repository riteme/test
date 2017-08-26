#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define LOGN 18

typedef long long i64;

static int n, q;
static bool color[NMAX + 10];
static vector<int> G[NMAX + 10];
static int depth[NMAX + 10], in[NMAX + 10], out[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];

void dfs(int u, int fa) {
    static int cur;
    in[u] = ++cur;

    for (int v : G[u]) {
        if (v == fa)
            continue;

        f[0][v] = u;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }

    out[u] = cur;
}

inline int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int d = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if ((d >> i) & 1)
            u = f[i][u];
    }

    if (u == v)
        return u;

    for (int i = LOGN; i >= 0; i--) {
        if (f[i][u] != f[i][v]) {
            u = f[i][u];
            v = f[i][v];
        }
    }

    return f[0][u];
}

void initialize() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);
        color[i] = c;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);
    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            f[j][i] = f[j - 1][f[j - 1][i]];
        }
    }
}

int main() {
    initialize();

    while (q--) {
        int opt, x;
        scanf("%d%d", &opt, &x);

        if (opt == 1) {
            for (int i = 1; i <= n; i++) {
                if (in[x] <= in[i] && in[i] <= out[x] &&
                    ((depth[i] - depth[x]) & 1))
                    color[i] ^= 1;
            }
        } else if (opt == 2) {
            color[x] ^= 1;
        } else {
            i64 ans = 0;
            for (int i = 1; i <= n; i++) {
                if (color[i])
                    ans += lca(i, x);
            }

            printf("%lld\n", ans);
        }
    }

    return 0;
}
