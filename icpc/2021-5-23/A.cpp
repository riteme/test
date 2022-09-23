#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000000;
constexpr i64 MOD = 1000000007;

int n;

void modify(i64 *a, int x, i64 v) {
    for ( ; x <= n; x += x & -x) {
        a[x] += v;
    }
}

i64 query(i64 *a, int x) {
    i64 v = 0;
    for ( ; x; x -= x & -x) {
        v += a[x];
    }
    return v;
}

i64 a[NMAX + 10];
i64 b[NMAX + 10], c[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }

    i64 ans = 0;
    for (int i = n; i >= 1; i--) {
        i64 sum = query(b, a[i]);
        i64 cnt = query(c, a[i]);
        ans = (ans + cnt * a[i] - sum) % MOD;
        modify(b, a[i], a[i]);
        modify(c, a[i], 1);
    }

    printf("%lld\n", ans);
    return 0;
}