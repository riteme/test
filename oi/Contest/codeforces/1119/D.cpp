#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n, q;
static i64 s[NMAX + 10], d[NMAX + 10], sum[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", s + i);
    sort(s + 1, s + n + 1);
    s[n + 1] = 3000000000000000000;
    for (int i = 1; i <= n; i++) d[i] = s[i + 1] - s[i];
    sort(d + 1, d + n + 1);
    for (int i = 1; i <= n; i++) sum[i] = d[i] + sum[i - 1];
    scanf("%d", &q);
    while (q--) {
        i64 l, r;
        scanf("%lld%lld", &l, &r);
        i64 L = r - l;
        int i = upper_bound(d + 1, d + n + 1, L) - d;
        i64 ans = sum[i - 1] + (n - i + 1) * (L + 1);
        printf("%lld ", ans);
    }
    return 0;
}
