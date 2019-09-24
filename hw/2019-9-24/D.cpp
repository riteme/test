#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define MOD 1000000007

typedef long long i64;

static int n, a[NMAX + 10];
static i64 f[NMAX + 10], g[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    n = unique(a + 1, a + n + 1) - a - 1;
    f[1] = g[a[1]] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = (f[i - 1] + g[a[i]]) % MOD;
        g[a[i]] = (g[a[i]] + f[i - 1]) % MOD;
    }
    printf("%lld\n", f[n]);

    return 0;
}
