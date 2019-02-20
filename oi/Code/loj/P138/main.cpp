#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define REAL_KMAX 10
#define KMAX 16
#define DEPTHMAX 64
#define MOD 1000000007LL

typedef long long i64;

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

template <typename TInt>
inline void add(TInt &a, TInt b) {
    a += b;
    if (a >= MOD) a -= MOD;
    else if (a <= -MOD) a += MOD;
}

static i64 B[KMAX];
static i64 C[KMAX][KMAX], A[KMAX][KMAX];
static i64 val[DEPTHMAX][KMAX][KMAX];
static bool has[DEPTHMAX][KMAX][KMAX];

inline i64 S(i64 n, int p) {
    i64 r = 0;
    for (int i = 0, x = 1; i <= p + 1; i++, x = n * x % MOD)
        add(r, A[p][i] * x % MOD);
    return r;
}

inline i64 qpow(i64 a, int k) {
    i64 r = 1;
    for (; k; k >>= 1, a = a * a % MOD)
        if (k & 1) r = r * a % MOD;
    return r;
}

i64 F(i64 n, i64 a, i64 b, i64 c, int p, int q, int d = 0) {
    if (n < 0) return 0;
    if (has[d][p][q]) return val[d][p][q];
    has[d][p][q] = true;
    i64 &ret = val[d++][p][q] = 0;  // 后面的 d 均加 1
    if (!q) ret = S(n, p) + (!p);   // 注意 p = 0 的边界情况
    else if (!a) ret = qpow(b / c, q) * (S(n, p) + (!p)) % MOD;
    else if (a >= c) {
        i64 m = a / c, r = a % c, mp = 1;
        for (int j = 0; j <= q; j++, mp = mp * m % MOD)
            add(ret, C[q][j] * mp % MOD * F(n, r, b, c, p + j, q - j, d) % MOD);
    } else if (b >= c) {
        i64 m = b / c, r = b % c, mp = 1;
        for (int j = 0; j <= q; j++, mp = mp * m % MOD)
            add(ret, C[q][j] * mp % MOD * F(n, a, r, c, p, q - j, d) % MOD);
    } else {
        i64 m = (a * n + b) / c;
        for (int k = 0; k < q; k++) {
            i64 s = 0;
            for (int i = 1; i <= p + 1; i++)
                add(s, A[p][i] * F(m - 1, c, c - b - 1, a, k, i, d) % MOD);
            add(ret, C[q][k] * s % MOD);
        }
        ret = (qpow(m, q) * S(n, p) - ret) % MOD;
    } return ret;
}

void initialize() {
    for (int i = 0; i < KMAX; i++) C[i][0] = 1;
    for (int i = 1; i < KMAX; i++) for (int j = 1; j <= i; j++)
        C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    for (int i = 0; i < KMAX; i++) {
        for (int j = 0; j < i; j++)
            add(B[i], C[i][j] * B[j] % MOD * inv(i - j + 1) % MOD);
        B[i] = (1 - B[i]) % MOD;
        if (B[i] < 0) B[i] += MOD;
    }
    for (int i = 0; i < KMAX - 1; i++) for (int j = 1; j <= i + 1; j++)
        A[i][j] = C[i + 1][j] * B[i + 1 - j] % MOD * inv(i + 1) % MOD;
}

int main() {
    initialize();
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(has, 0, sizeof(has));
        i64 n, a, b, c;
        int p, q;
        scanf("%lld%lld%lld%lld%d%d", &n, &a, &b, &c, &p, &q);
        i64 ans = F(n, a, b, c, p, q);
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
