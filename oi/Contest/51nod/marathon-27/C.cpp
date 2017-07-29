#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define INF 0x3f3f3f3f3f3f3f3fLL

i64 isqrt(i64 n) {
    i64 l = 0, r = 1e9 + 10;
    while (l < r) {
        i64 m = (l + r) / 2 + 1;

        if (m * m > n)
            r = m - 1;
        else
            l = m;
    }

    return l;
}

i64 dfs(i64 n, int k) {
    if (n <= 0)
        return n ? INF : 0;

    i64 s = isqrt(n);
    assert(s * s <= n);
    // printf("%lld %lld\n", n, s);
    if (n - 2 * k > 25)
        return dfs(25, k) + (s - 5) * 2 + (s * s == n ? 0 : 1);

    s *= s;
    if (s < n)
        return min(dfs(n - k, k), dfs(s, k)) + 1;
    return dfs(n - k, k) + 1;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        i64 n;
        int k;
        scanf("%lld%d", &n, &k);

        i64 ans = dfs(n, k);
        printf("%lld\n", ans < INF ? ans : -1);
    }

    return 0;
}
