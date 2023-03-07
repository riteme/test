#include <algorithm>
#include <cstdio>

using namespace std;

constexpr int INF = 0x3f3f3f3f;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int ans = INF;
    for (int d = 1; d <= k; d++) {
        if (k % d > 0)
            continue;
        int h = k / d;
        int b = (d - 1) * h;
        if (b + k >= n)
            ans = min(ans, (n - k + h - 1) / h + 1);
    }
    if (ans > n)
        puts("Poor E.S.!");
    else
        printf("%d\n", ans);
    return 0;
}
