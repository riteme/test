// #define NDEBUG

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

static int n, m, K;
static vector<int> G[NMAX + 10];

void initialize() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
    }
}

int dfs(int u, int &cnt) {
    cnt--;
    if (!cnt)
        return u;

    for (int v : G[u]) {
        int ret = dfs(v, cnt);

        if (ret > 0)
            return ret;
    }

    return -1;
}

int main() {
#ifdef NDEBUG
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif
    initialize();

    for (int u = 1; u <= n; u++) {
        int cnt = K;
        printf("%d\n", dfs(u, cnt));
    }

    return 0;
}
