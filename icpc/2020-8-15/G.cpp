#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 2000
#define MOD 1000000007

typedef long long i64;

int n;
int A[NMAX + 10], B[NMAX + 10];
i64 cnt[NMAX + 10], pre[NMAX + 10], bit[NMAX + 10];

void modify(int x, int v) {
    for ( ; x <= n; x += x & -x) {
        bit[x] += v;
    }
}

i64 query(int x) {
    i64 r = 0;
    for ( ; x; x -= x & -x) {
        r += bit[x];
    }
    return r;
}

void _main() {
    scanf("%d", &n);
    memset(bit, 0, sizeof(i64) * (n + 10));
    for (int i = 1; i <= n; i++) {
        scanf("%d", B + i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
    }

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (B[i] >= A[i]);
    }

    i64 ans = 0, prod = 1;
    for (int i = n; i >= 1; i--) {
        i64 sum = 0;
        for (int j = i; j <= n; j++) {
            cnt[j] = query(B[j]);
            sum += cnt[j];
        }

        for (int j = i; j <= n; j++)
        if (B[j] > B[i]) {
            i64 prod2 = prod * (n - i) % MOD;
            ans = (ans + pre[i - 1] * prod2) % MOD;
            ans = (ans + (B[j] >= A[i]) * prod2) % MOD;
            ans = (ans + (sum - cnt[j]) * prod) % MOD;
        }

        if (i < n)
            prod = prod * (n - i) % MOD;
        modify(A[i], +1);
    }

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        _main();
    }
    return 0;
}
