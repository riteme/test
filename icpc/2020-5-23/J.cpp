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

#define NMAX 100000

int n, m;
i64 w[NMAX + 10];

int nextp(int l) {
    int r = 1;
    while (r < l) {
        r <<= 1;
    }
    return r;
}

vi mul(int l, int r) {
    if (l == r)
        return {w[l], 1};

    int mi = (l + r) / 2;
    vi L = mul(l, mi);
    vi R = mul(mi + 1, r);
    int len = nextp(r - l + 2);
    L.resize(len);
    R.resize(len);
    ntt(L, 1);
    ntt(R, 1);
    for (int i = 0; i < len; i++) {
        L[i] = L[i] * R[i] % MOD;
    }
    ntt(L, -1);
    return L;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        scanf("%lld", w + i);
    }

    int len = nextp(2 * n + m + 3);
    vi p = mul(1, n);
    for (int i = 0, j = n; i < j; i++, j--) {
        swap(p[i], p[j]);
    }
    p.resize(len);

    vi q(len);
    q[0] = 1;
    for (int i = 1; i <= n + m; i++) {
        q[i] = (i * q[i - 1] + (i & 1 ? -1 : 1)) % MOD;
    }

    ntt(p, 1);
    ntt(q, 1);
    for (int i = 0; i < len; i++) {
        p[i] = p[i] * q[i] % MOD;
    }
    ntt(p, -1);

    for (int i = n; i < n + m; i++) {
        if (p[i] < 0)
            p[i] += MOD;
        printf("%lld\n", p[i]);
    }
}

int main() {
    for (int i = 1; true; i++) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0)
            break;

        printf("Case #%d:\n", i);
        solve();
    }
    return 0;
}