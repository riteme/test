#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;
using vi = vector<i64>;

#define MOD 998244353
#define G 3

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

void ntt(vi &a, int op = 1) {
    int n = a.size();
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s; ) {}
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int i = 1; i < n; i <<= 1) {
        i64 u = qpow(G, (MOD - 1) / (i * 2));
        if (op == -1)
            u = inv(u);
        for (int j = 0; j < n; j += i * 2) {
            i64 w = 1;
            for (int k = 0; k < i; k++, w = w * u % MOD) {
                i64 x = a[j + k], y = w * a[j + k + i] % MOD;
                #define mt(x) ({if ((x) >= MOD) (x) -= MOD;})
                a[j + k] = x + y; mt(a[j + k]);
                a[j + k + i] = x - y + MOD; mt(a[j + k + i]);
                #undef mt
            }
        }
    }

    if (op == -1) {
        i64 v = inv(n);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * v % MOD;
        }
    }
}

int nextp(int l) {
    int r = 1;
    while (r < l) {
        r <<= 1;
    }
    return r;
}

#define NMAX 100000

int n;
int c[32];
i64 fac[NMAX + 10];
i64 fi[NMAX + 10];

i64 C(int a, int b) {
    if (a < b)
        return 0;
    return fac[a] * fi[b] % MOD * fi[a - b] % MOD;
}

void solve() {
    memset(c, 0, sizeof(c));
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        if (v == 0)
            continue;

        int k = __builtin_ctz(v);
        if (k > 11 || v != (1 << k))
            continue;
        c[k]++;
    }

    vi f = {1};
    vi g;
    int sum = 0, order = 0;
    for (int i = 0; i < 11; i++) {
        sum += c[i];

        int len = nextp(c[i] + order + 1);
        f.resize(len);

        g.clear();
        g.resize(len);
        for (int j = 0; j <= c[i]; j++) {
            g[j] = C(c[i], j);
        }

        ntt(f, 1);
        ntt(g, 1);
        for (int j = 0; j < len; j++) {
            f[j] = f[j] * g[j] % MOD;
        }
        ntt(f, -1);

        for (int j = 0; 2 * j < len; j++) {
            f[j] = f[2 * j];
            if (2 * j + 1 < len)
                f[j] = (f[j] + f[2 * j + 1]) % MOD;
        }
        order = (c[i] + order) / 2;
        for (int j = order + 1; j < len; j++) {
            f[j] = 0;
        }
    }

    i64 ans = (qpow(2, c[11]) - 1) * qpow(2, sum) % MOD;
    for (int i = 1; i < f.size(); i++) {
        ans = (ans + f[i]) % MOD;
    }
    sum += c[11];
    ans = ans * qpow(2, n - sum) % MOD;
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