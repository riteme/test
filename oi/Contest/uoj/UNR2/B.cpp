#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100
#define MOD 998244353

typedef long long i64;

static int m, b, c;
static int up[NMAX + 10];
static i64 n, ans;

void dfs(int p, i64 s) {
    if (p > m) {
        if (s < n)
            ans++;
    } else {
        for (int i = 0; i <= up[p] - c; i++) {
            dfs(p + 1, s + i);
        }
    }
}

int main() {
    scanf("%d%d%d%lld", &m, &b, &c, &n);

    up[0] = 1;
    for (int i = 1; i <= m; i++) {
        up[i] = up[i - 1] * b;
    }

    dfs(1, 0);
    printf("%lld\n", ans % MOD);

    return 0;
}
