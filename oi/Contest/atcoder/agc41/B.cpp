#include <cstdio>
#include <cstring>

#include <algorithm>
#include <functional>

using namespace std;

typedef long long i64;

#define NMAX 100000

static int n, M, V, P;
static int a[NMAX + 10];

int main() {
    scanf("%d%d%d%d", &n, &M, &V, &P);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + n + 1, greater<int>());

    int ans = P;
    i64 sum = 0;
    for (int i = P + 1; i <= n; i++) {
        i64 k = i - P;
        ans += a[P] + (max(0LL, sum) + k - 1) / k <= a[i] + M;
        sum -= a[P] - a[i];
        if (P + n - i <= V)
            sum += M;
    }

    printf("%d\n", ans);
    return 0;
}
