/**
 * 转换为线性规划问题，然后观察约束等式
 * 消元后发现可以用某种数求解
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long i64;

static int n;
static i64 a[NMAX + 10], b[NMAX + 10], M;

void initialize() {
    M = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
        M += a[i];
    }
    M /= n;

    b[1] = 0;
    for (int i = 2; i <= n; i++) {
        b[i] = b[i - 1] + M - a[i];
    }
}

int main() {
    while (scanf("%d", &n) != EOF) {
        initialize();
        sort(b + 1, b + n + 1);
        i64 m = b[n / 2 + 1], ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += abs(m - b[i]);
        }
        printf("%lld\n", ans);
    }

    return 0;
}
