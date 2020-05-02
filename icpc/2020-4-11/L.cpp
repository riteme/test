#include <cstdio>

#include <functional>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000

int n;
i64 a[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    sort(a + 1, a + n + 1, std::greater<i64>());

    i64 ans = 0, sum = 0, cost = 0;
    for (i64 i = 1; i <= n; i++) {
        cost += i;
        sum += a[i];
        ans = max(ans, sum - cost);
    }

    printf("%lld\n", ans);
    return 0;
}