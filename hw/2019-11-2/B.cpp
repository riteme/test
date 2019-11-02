#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n, K, m;
static int a[NMAX + 10], b[NMAX + 10];
static int bit[NMAX + 10];

void modify(int x) {
    for ( ; x; x -= x & -x)
        bit[x]++;
}

int query(int x) {
    int r = 0;
    for ( ; x <= m; x += x & -x)
        r += bit[x];
    return r;
}

int main() {
    while (scanf("%d%d", &n, &K) != EOF) {
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        memcpy(b + 1, a + 1, sizeof(int) * n);
        sort(b + 1, b + n + 1);
        m = unique(b + 1, b + n + 1) - b - 1;
        memset(bit + 1, 0, sizeof(int) * m);

        i64 ans = 0;
        for (int i = 1; i <= n; i++) {
            int j = lower_bound(b + 1, b + m + 1, a[i]) - b;
            ans += query(j + 1);
            modify(j);
        }

        ans = max(0LL, ans - K);
        printf("%lld\n", ans);
    }

    return 0;
}
