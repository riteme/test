#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>

using namespace std;

using i64 = long long;
using vi = vector<i64>;

constexpr i64 G = 3;
constexpr i64 MOD = 998244353;

i64 qpow(i64 a, i64 n) {
    i64 r = 1;
    while (n) {
        if (n & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return r;
}

i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

void ntt(vi &a, int op = 1) {
    int n = a.size();
    for (int i = 1, j = 0; i < n - 1; ++i) {
        for (int s = n; j ^= s >>= 1, ~j & s;) {}
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int i = 1; i < n; i *= 2) {
        i64 u = qpow(G, (MOD - 1) / (i * 2));
        if (op == -1)
            u = inv(u);
        for (int j = 0; j < n; j += i * 2) {
            i64 w = 1;
            for (int k = 0; k < i; ++k, w = w * u % MOD) {
                int x = a[j + k], y = w * a[j + k + i] % MOD;
#define modto(x)                                                                                   \
    ({                                                                                             \
        if ((x) >= MOD)                                                                            \
            (x) -= MOD;                                                                            \
    })
                a[j + k] = x + y;
                modto(a[j + k]);
                a[j + k + i] = x - y + MOD;
                modto(a[j + k + i]);
#undef modto
            }
        }
    }
    if (op == -1) {
        i64 in = inv(n);
        for (int i = 0; i < n; ++i)
            a[i] = a[i] * in % MOD;
    }
}

constexpr int NMAX = 1048576;

int n;
int A[NMAX + 10], B[NMAX + 10];
i64 s[NMAX + 10];
vi a, b;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", A + i);
        A[i] = ~A[i];
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", B + i);
        B[i] = ~B[i];
    }
    reverse(B, B + n);

    int N = 1;
    while (N < 2 * n) {
        N <<= 1;
    }

    a.resize(N);
    b.resize(N);
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < N; i++) {
            a[i] = (A[i % n] >> k) & 1;
        }
        for (int i = 0; i < n; i++) {
            b[i] = (B[i] >> k) & 1;
        }
        for (int i = n; i < N; i++) {
            b[i] = 0;
        }
        ntt(a);
        ntt(b);
        for (int i = 0; i < N; i++) {
            a[i] = a[i] * b[i] % MOD;
        }
        ntt(a, -1);
        for (int i = 0; i < n; i++) {
            s[i] += a[n - 1 + i] << k;
        }
    }

    i64 ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        ans = min(ans, s[i]);
    }
    ans = 31 * n - ans;
    printf("%lld\n", ans);

    return 0;
}
