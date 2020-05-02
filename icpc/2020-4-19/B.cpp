#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef unsigned long long u64;

#define NMAX 1000000

int n;
u64 a[NMAX + 10];
u64 mi[NMAX + 10];

u64 solve(int l, int r) {
    if (l == r)
        return a[l];
    int m = (l + r) / 2;
    u64 ret = solve(l, m) ^ solve(m + 1, r);

    mi[m] = a[m];
    mi[m + 1] = a[m + 1];
    for (int i = m - 1; i >= l; i--)
        mi[i] = min(a[i], mi[i + 1]);
    for (int i = m + 2; i <= r; i++)
        mi[i] = min(a[i], mi[i - 1]);

    u64 sum = 0;
    u64 mx = a[m + 1];
    for (int i = m + 1, j = m, k = m; i <= r; i++) {
        mx = max(mx, a[i]);
        while (k >= l && a[k] <= mx)
            sum ^= mi[k--];
        while (j > k && mi[j] >= mi[i])
            sum ^= mi[j--];

        u64 s = sum ^ ((m - j) % 2 == 1 ? mi[i] : 0);
        ret ^= ((m - k) % 2 == 1 ? mx : 0) ^ s ^ (mx & s);
    }

    sum = 0;
    mx = a[m];
    for (int i = m, j = m + 1, k = m + 1; i >= l; i--) {
        mx = max(mx, a[i]);
        while (k <= r && a[k] <= mx)
            sum ^= mi[k++];
        while (j < k && mi[j] >= mi[i])
            sum ^= mi[j++];

        u64 s = sum ^ ((j - m - 1) % 2 == 1 ? mi[i] : 0);
        ret ^= ((k - m - 1) % 2 == 1 ? mx : 0) ^ s ^ (mx & s);
    }

    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%llu", a + i);
    printf("%llu\n", solve(1, n));
    return 0;
}