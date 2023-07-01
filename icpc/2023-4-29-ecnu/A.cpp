#include <algorithm>
#include <cstdio>

using namespace std;

using i64 = long long;

int main() {
    i64 n, m;
    scanf("%lld%lld", &n, &m);
    i64 ans = 0;
    for (i64 d = 1; d * d <= n && d <= m; d++) {
        if (n % d != 0)
            continue;
        ans = max(ans, d);
        if (n / d <= m)
            ans = max(ans, n / d);
    }
    printf("%lld\n", n / ans);
    return 0;
}
