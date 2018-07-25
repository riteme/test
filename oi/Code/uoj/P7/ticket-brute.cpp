// #define NDEBUG

#include <cassert>

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long int64;

static int n, _;
static vector<int> G[NMAX + 10];
static int64 dist[NMAX + 10];
static int father[NMAX + 10];
static int64 W[NMAX + 10];
static int64 P[NMAX + 10];
static int64 Q[NMAX + 10];
static int64 L[NMAX + 10];
static int64 f[NMAX + 10];

static void build_tree(int x) {
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        dist[v] = dist[x] + W[v];
        build_tree(v);
    }
}

static void initialize() {
    scanf("%d%d", &n, &_);

    for (int i = 2; i <= n; i++) {
        scanf("%d%lld%lld%lld%lld", father + i, W + i, P + i, Q + i, L + i);

        G[father[i]].push_back(i);
    }

    build_tree(1);
}

static void dfs(int x) {
    if (x != 1) {
        f[x] = LLONG_MAX;
        int p = father[x];
        while (p && dist[x] - dist[p] <= L[x]) {
            f[x] = min(f[x], f[p] + P[x] * (dist[x] - dist[p]) + Q[x]);
            p = father[p];
        }
    }

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        dfs(v);
    }
}

int main() {
    // freopen("ex_ticket2.in", "r", stdin);
    initialize();

    dfs(1);

    for (int i = 2; i <= n; i++) {
        printf("%lld\n", f[i]);
    }

    return 0;
}
