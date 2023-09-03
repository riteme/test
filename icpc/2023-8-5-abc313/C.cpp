#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

int n;
i64 a[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }
    sort(a + 1, a + n + 1);

    i64 s1 = 0;
    for (int i = 1; i <= n; i++) {
        s1 += a[i];
    }
    i64 t = s1 / n;

    s1 = 0;
    i64 s0 = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] < t)
            s0 += t - a[i];
        if (a[i] > t + 1)
            s1 += a[i] - t - 1;
    }
    i64 d = abs(s0 - s1);
    i64 ans = min(s0, s1) + d;
    printf("%lld\n", ans);
    return 0;
}
