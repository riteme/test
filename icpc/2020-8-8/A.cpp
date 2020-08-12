#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n, m, x, y;
        scanf("%lld%lld%lld%lld", &n, &m, &x, &y);
        i64 ans = min(m, (n + (m - 1) * y) / x);
        printf("%lld\n", ans);
    }
    return 0;
}
