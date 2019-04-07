#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300000

typedef long long i64;

static int n;
static i64 a[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    i64 ans = 0;
    for (int i = 1, j = 2; i <= n; i++) {
        if (i == j) j++;
        while (j <= n && a[j] < 2) j++;
        ans += a[i] / 3;
        a[i] %= 3;
        if (a[i] && j <= n) {
            ans++;
            a[i]--;
            a[j] -= 2;
            while (j <= n && a[j] < 2) j++;
        }
        if (a[i] && j <= n) {
            ans++;
            a[i]--;
            a[j] -= 2;
            while (j <= n && a[j] < 2) j++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
