#include <cstdio>
#include <cstring>

#include <algorithm>
#include <functional>

using namespace std;

#define NMAX 100000
#define INF 1000000000000000000

typedef long long i64;

int n;
i64 a[NMAX + 10], b[NMAX + 10];

void solve() {
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    for (int i = 1; i <= n; i++)
        scanf("%lld", b + i);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);

    int m = 0;
    for ( ; m <= n && a[m + 1] < 0; m++) ;

    i64 l = -INF, r = INF;
    while (l < r) {
        i64 K = l + r;
        K = K < 0 ? (K - 1) / 2 : K / 2;

        bool ok = true;
        if (K < 0) {
            for (int i = m + 1, j = 1; ok && i <= n; i++) {
                while (j <= n && a[i] * b[j] <= K) j++;
                ok &= i - m <= j - 1;
            }
            for (int i = m, j = n; ok && i >= 1; i--) {
                while (j >= 1 && a[i] * b[j] <= K) j--;
                ok &= m - i + 1 <= n - j;
            }
        } else {
            for (int i = n, j = 1; ok && i > m; i--) {
                while (j <= n && a[i] * b[j] <= K) j++;
                ok &= n - i + 1 <= j - 1;
            }
            for (int i = 1, j = n; ok && i <= m; i++) {
                while (j >= 1 && a[i] * b[j] <= K) j--;
                ok &= i <= n - j;
            }
        }

        if (ok) r = K;
        else l = K + 1;
    }

    printf("%lld\n", l);
}

int main() {
    while (scanf("%d", &n) != EOF)
        solve();

    return 0;
}