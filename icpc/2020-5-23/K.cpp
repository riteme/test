#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000
#define MOD 1000000007

using i64 = long long;

i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    for ( ; k; a = a * a % MOD, k >>= 1) {
        if (k & 1)
            r = r * a % MOD;
    }
    return r;
}

i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

int n;
int c[NMAX + 10];
bool mark[NMAX + 10];
i64 f[NMAX + 10];
i64 fac[NMAX + 10], fi[NMAX + 10];

void solve() {
    memset(mark + 1, 0, n);
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i);
        for (int j = 0; j < c[i]; j++) {
            int u;
            scanf("%d", &u);
            ok &= !mark[u];
            mark[u] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        ok &= mark[i];
    }

    if (!ok) {
        puts("0");
        return;
    }

    memset(f, 0, sizeof(i64) * (n + 1));
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    for (int j = n - 1; j >= 0; j--) {
        f[j + 1] = (f[j + 1] + c[i] * f[j]) % MOD;
    }

    int k = 0;
    for (int i = 1; i <= n; i++) {
        if (c[i] == 0)
            k++;
    }

    i64 ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + (i & 1 ? -1 : 1) * f[i] * fac[n - i]) % MOD;
    }
    ans = ans * fi[k] % MOD;
    if (ans < 0)
        ans += MOD;

    printf("%lld\n", ans);
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fac[i] = i * fac[i - 1] % MOD;
    }
    fi[NMAX] = inv(fac[NMAX]);
    for (int i = NMAX - 1; i >= 0; i--) {
        fi[i] = (i + 1) * fi[i + 1] % MOD;
    }

    for (int i = 1; true; i++) {
        scanf("%d", &n);
        if (n == 0)
            break;

        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}