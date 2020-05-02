#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000

int n, T;
i64 x[NMAX + 10];

int main() {
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; i++)
        scanf("%lld", x + i);

    int ans = 0;
    for (int i = 1, j = 1; i <= n; i++) {
        if (j < i) j = i;
        i64 r = x[i] < 0 ? T + x[i] : T;
        while (j <= n && x[j] - min(0LL, x[i]) <= r)
            j++;
        ans = max(ans, j - i);
    }
    for (int i = n, j = n; i >= 1; i--) {
        if (j > i) j = i;
        i64 r = x[i] > 0 ? T - x[i] : T;
        while (j && max(0LL, x[i]) - x[j] <= r)
            j--;
        ans = max(ans, i - j);
    }

    printf("%d\n", ans);
    return 0;
}