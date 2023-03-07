#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

int n;
i64 a[NMAX + 10], s[NMAX + 10], ps[NMAX + 10];
i64 c[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }
    memcpy(s, a, sizeof(s));
    sort(s + 1, s + n + 1);
    memcpy(ps, s, sizeof(ps));
    partial_sum(ps, ps + n + 1, ps);
    int lastj = 0;
    for (int i = n; i >= 1; i--) {
        int j = upper_bound(s + 1, s + n + 1, a[i]) - s - 1;
        if (j <= lastj)
            continue;
        i64 d = s[j] - s[lastj];
        c[i] = ps[j] - ps[lastj] - (j - lastj) * s[lastj] + d * (n - j);
        lastj = j;
    }
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        // printf("c[%d]=%lld\n", i, c[i]);
        ans += i * c[i];
    }
    printf("%lld\n", ans);
    return 0;
}
