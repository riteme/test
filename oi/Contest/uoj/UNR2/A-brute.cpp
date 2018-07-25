#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 400
#define MOD 998244353

typedef long long i64;

static int n, k;
static i64 w[NMAX + 10], ans;
static int seq[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", w + i);
    }
}

void dfs(int p) {
    if (p > n) {
        i64 ret = 1;
        for (int i = 1; i <= n - k + 1; i++) {
            int maxw = 0;
            for (int j = i; j <= i + k - 1; j++) {
                maxw = max(maxw, seq[j]);
            }

            ret = ret * w[maxw] % MOD;
        }

        ans = (ans + ret) % MOD;
    } else {
        for (int i = 1; i <= n; i++) {
            seq[p] = i;
            dfs(p + 1);
        }
    }
}

int main() {
    initialize();
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}
