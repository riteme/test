#include <cstdio>
#include <cstring>

#include <algorithm>
#include <functional>

using namespace std;

typedef long long i64;

#define NMAX 1000000

int n, m;
i64 row[NMAX + 10], col[NMAX + 10];
i64 cnt[NMAX + 10];

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", row + i);
    for (int i = 1; i <= m; i++)
        scanf("%lld", col + i);

    sort(row + 1, row + n + 1);
    for (int i = 1, j = 1; i <= m; i++) {
        while (j <= n && row[j] < i)
            j++;
        cnt[i] = n - j + 1;
    }

    sort(col + 1, col + m + 1, greater<i64>());
    i64 ans = 0, sum = 0;
    for (int i = 1; i <= m; i++) {
        i64 used = min(col[i], cnt[i] + sum);
        ans += used;
        sum += cnt[i] - used;
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}