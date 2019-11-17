#include <cstdio>
#include <cstring>
#include <climits>

#include <functional>
#include <algorithm>

using namespace std;

#define NMAX 500000

typedef long long i64;

static int n;
static i64 d[NMAX + 10], s[NMAX + 10];
static i64 a[NMAX + 10], b[NMAX + 10];
static i64 mx[NMAX + 10], mi[NMAX + 10];
static bool ok[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", d + i);
    sort(d + 1, d + n + 1, greater<i64>());
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + d[i];
    for (i64 m = n, j = n + 1, k = n + 1; m >= 0; m--) {
        while (j - 1 > m && d[j - 1] <= m) j--;
        while (j <= n && d[j] > m) j++;
        while (k - 1 > m && d[k - 1] <= m + 1) k--;
        while (k <= n && d[k] > m + 1) k++;
        a[m] = -(m * (m - 1) + (j - m - 1) * m + s[n] - s[j - 1] - s[m]);
        b[m] = m * (m + 1) + (k - m - 1) * (m + 1) + s[n] - s[k - 1] - s[m];
    }
    int mp = n + 1;
    for (int i = 1; i <= n; i++) {
        mx[i] = max(mx[i - 1], a[i]);
        if (a[i] > i) mp = min(mp, i);
    }
    mp--;
    mi[n + 1] = LLONG_MAX;
    for (int i = n; i >= 0; i--)
        mi[i] = min(mi[i + 1], b[i]);

    d[0] = n;
    d[n + 1] = 0;
    for (int m = mp; m >= 0; m--) {
        int L = max(mx[m], d[m + 1]);
        int R = min(mi[m], d[m]);
        for (int i = L; i <= R; i++)
            ok[i] = true;
    }

    int cnt = 0;
    for (int i = 0; i <= n; i++)
    if (ok[i] && (s[n] + i) % 2 == 0) {
        cnt++;
        printf("%d ", i);
    }
    if (!cnt) puts("-1");

    return 0;
}
