#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 17

typedef long long int64;

static int testid, n;
static int m;
static int rad[NMAX + 10];
static int depth[NMAX + 10];
static int dist[NMAX + 10];
static int f[LOGN + 1][NMAX + 10];

inline int evaluate_lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int delta = depth[u] - depth[v];
    for (int i = LOGN; i >= 0; i--) {
        if ((delta >> i) & 1)
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

inline int distance(int u, int v) {
    return dist[u] + dist[v] - (dist[evaluate_lca(u, v)] << 1);
}

inline int64 evaluate() {
    int64 answer = 0;

    for (int i = 1; i <= m; i++) {
        for  (int j = i + 1; j <= m; j++) {
            if (rad[i] + rad[j] >= distance(i, j))
                answer++;
        }
    }

    return answer;
}

int main() {
    scanf("%d%d", &testid, &n);

    for (m = 1; m <= n; m++) {
        int fa, d, r;
        scanf("%d%d%d", &fa, &d, &r);

        f[0][m] = fa;
        dist[m] = dist[fa] + d;
        depth[m] = depth[fa] + 1;
        rad[m] = r;
        for (int j = 1; j <= LOGN; j++) {
            f[j][m] = f[j - 1][f[j - 1][m]];
        }

        printf("%lld\n", evaluate());
    }

    return 0;
}
