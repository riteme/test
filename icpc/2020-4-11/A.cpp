#include <cstdio>
#include <cstring>

#define NMAX 500000
#define QMAX 200000

typedef long long i64;

int n, q;
i64 ans;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        ans += (i & 1 ? -1 : 1) * v;
    }
    if (n % 2 == 0)
        ans *= -1;

    scanf("%d", &q);
    while (q--) {
        int l, r, v;
        scanf("%d%d%d", &l, &r, &v);
        int L = r - l + 1;
        if (L % 2 != 0)
            ans += ((n - l) & 1 ? -1 : 1) * v;
        printf("%lld\n", ans);
    }
    return 0;
}