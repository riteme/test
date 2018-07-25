#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static double a[NMAX + 10], b[NMAX + 10];

bool cmp(double x, double y) {
    return x > y;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", a + i, b + i);
    }

    sort(a + 1, a + n + 1, cmp);
    sort(b + 1, b + n + 1, cmp);

    double ans = 0, sum, cur;
    int i, j;
    for (i = 1, j = 0, sum = 0, cur = 0; i <= n; i++) {
        sum += a[i];
        cur += a[i];
        for (; j < n && sum > 0; sum -= b[++j]);

        if (sum < 0)
            ans = max(ans, cur - i - j);
    }

    for (i = 1, j = 0, sum = 0, cur = 0; i <= n; i++) {
        sum += b[i];
        cur += b[i];
        for (; j < n && sum > 0; sum -= a[++j]);

        if (sum < 0)
            ans = max(ans, cur - i - j);
    }

    printf("%.4lf\n", ans);

    return 0;
}
