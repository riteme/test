#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

int n;
int a[NMAX + 10];
i64 ans[NMAX + 10];

void recur(int l, int r) {
    if (l > r) return;
    int m = max_element(a + l, a + r + 1) - a;
    i64 mi = a[m];
    int j = m;
    for (int i = m; i >= l; i--) {
        mi = min(mi, i64(a[i]));
        while (j <= r && a[j] >= mi) j++;
        ans[j - i] = max(ans[j - i], mi * a[m]);
    }
    mi = a[m];
    j = m;
    for (int i = m; i <= r; i++) {
        mi = min(mi, i64(a[i]));
        while (j >= l && a[j] >= mi) j--;
        ans[i - j] = max(ans[i - j], mi * a[m]);
    }
    recur(l, m - 1);
    recur(m + 1, r);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    memset(ans + 1, 0, sizeof(i64) * n);
    recur(1, n);

    // for (int i = 2; i <= n; i++)
        // ans[i] = min(ans[i - 1], ans[i]);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        solve();
    }
    return 0;
}