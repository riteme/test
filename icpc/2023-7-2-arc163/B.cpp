#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int n, m;
i64 a[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }
    sort(a + 3, a + n + 1);

    i64 ans = LLONG_MAX;
    for (int l = 3; l + m - 1 <= n; l++) {
        int r = l + m - 1;

        i64 v = 0;
        if (a[1] > a[l])
            v += a[1] - a[l];
        if (a[2] < a[r])
            v += a[r] - a[2];
        ans = min(ans, v);
    }

    printf("%lld\n", ans);
    return 0;
}
