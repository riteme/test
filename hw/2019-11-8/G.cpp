#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000

static int n;
static i64 a[NMAX + 10];
static i64 ans[NMAX + 10];

void solve(int l, int r) {
    if (l > r) return;
    int m = max_element(a + l, a + r + 1) - a;
    i64 mi = LLONG_MAX, mx = a[m];
    for (int i = m, j = m + 1; i >= l; i--) {
        mi = min(mi, a[i]);
        while (j <= r && a[j] >= mi) j++;
        i64 v = mx * mi;
        ans[j - i] = max(ans[j - i], v);
    }
    mi = LLONG_MAX;
    for (int i = m, j = m - 1; i <= r; i++) {
        mi = min(mi, a[i]);
        while (j >= l && a[j] >= mi) j--;
        i64 v = mx * mi;
        ans[i - j] = max(ans[i - j], v);
    }
    solve(l, m - 1);
    solve(m + 1, r);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%lld", a + i);
            ans[i] = 0;
        }
        solve(1, n);
        for (int i = n - 1; i >= 1; i--)
            ans[i] = max(ans[i], ans[i + 1]);
        for (int i = 1; i <= n; i++) {
            printf("%lld\n", ans[i]);
        }
    }

    return 0;
}
