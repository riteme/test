// #define NDEBUG

#define NAME "c"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000

static int n, P;
static vector<int> G[NMAX + 10];
static int val[NMAX + 10];
static i64 answer;

void initialize() {
    scanf("%d%d", &n, &P);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", val + i);
    }
}

void dfs(int u, int f, int vsum, int vmax) {
    vsum += val[u];
    vsum %= P;
    vmax = max(vmax, val[u]);
    if (f && vsum == vmax % P)
        answer++;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == f)
            continue;

        dfs(v, u, vsum, vmax);
    }
}

int main() {
#ifdef NDEBUG
    freopen(NAME ".in", "r", stdin);
    freopen(NAME ".out", "w", stdout);
#endif
    initialize();

    for (int u = 1; u <= n; u++) {
        dfs(u, 0, 0, 0);
    }

    printf("%lld\n", answer / 2 + n);

    return 0;
}
