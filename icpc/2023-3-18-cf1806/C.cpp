#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

using i64 = long long;

constexpr int NMAX = 400000;

int n;
i64 a[NMAX + 10];

void solve() {
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(a[i]);
    }

    if (n == 2) {
        ans = min(ans, abs(a[0] - a[1]));
    }

    if (n == 4) {
        ans = min(ans, abs(a[0] - 2) + abs(a[1] - 2) + abs(a[2] - 2) + abs(a[3] - 2));
    }

    i64 m = n / 2;
    if (n >= 4 && m % 2 == 0) {
        i64 d = -1;
        i64 sum = 0;
        for (int i = 0; i < n; i++) {
            sum += abs(a[i] - d);
        }
        for (int i = 0; i < n; i++) {
            i64 v = sum - abs(a[i] - d) + abs(a[i] - m);
            ans = min(ans, v);
        }
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        n *= 2;
        for (int i = 0; i < n; i++) {
            scanf("%lld", a + i);
        }
        solve();
    }
    return 0;
}
