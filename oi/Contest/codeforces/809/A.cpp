#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000
#define MOD 1000000007

typedef long long i64;

static int n;
static i64 a[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }

    sort(a + 1, a + n + 1);
    i64 poly = 1, val = 0, ans = 0;
    for (int i = 2; i <= n; i++) {
        val = (val * 2 + poly * (a[i] - a[i - 1])) % MOD;
        ans = (ans + val) % MOD;
        poly = (poly * 2 + 1) % MOD;
    }
    
    printf("%lld\n", ans);

    return 0;
}
