#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define TMAX 100000
#define MOD 1000000007

typedef long long i64;

i64 _inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * _inv(MOD % x) % MOD;
}

i64 inv(i64 x) {
    return _inv(x % MOD);
}

i64 qpow(i64 x, i64 k) {
    x %= MOD;
    i64 r = 1;
    for ( ; k; x = x * x % MOD, k >>= 1)
        if (k & 1) r = r * x % MOD;
    return r;
}

static bool _initialized;
static i64 _fi[TMAX + 100], _tmp[TMAX + 100];
struct Shit {
    static void init() {
        _fi[0] = 1;
        for (int i = 2; i <= TMAX + 50; i++)
            _fi[0] = _fi[0] * i % MOD;
        _fi[TMAX + 50] = inv(_fi[0]);
        for (int i = TMAX + 49; i >= 0; i--)
            _fi[i] = _fi[i + 1] * (i + 1) % MOD;
        _initialized = true;
    }
    int K;
    i64 *f;
    Shit(int _K, i64 t) : K(_K) {
        if (!_initialized) init();
        f = new i64[K + 2];
        f[0] = 0;
        for (int i = 1; i <= K + 1; i++) {
            f[i] = (f[i - 1] + (qpow(2 * i, t + 1) - (2LL * i % MOD * 2 * i % MOD))
                * inv(2 * i - 1) % MOD) % MOD;
        }
    }
    i64 eval(i64 n) {
        n %= MOD;
        _tmp[K + 2] = 1;
        for (int i = K + 1; i >= 1; i--)
            _tmp[i] = _tmp[i + 1] * (n - i) % MOD;
        i64 ret = 0, pre = 1;
        for (int i = 0, b = K & 1 ? 1 : -1; i <= K + 1; i++, b = -b) {
            ret = (ret + b * f[i] * pre % MOD * _tmp[i + 1] % MOD * _fi[i] % MOD * _fi[K + 1 - i]) % MOD;
            pre = pre * (n - i) % MOD;
        }
        return ret;
    }
};

static Shit *G;

i64 F(i64 t, i64 R) {
    if (R == 0) return 0;
    i64 r = R / 4 % MOD, m = R % 4, sum = 0;
    if (m >= 1) sum = (sum + t) % MOD;
    if (m >= 2) sum = (sum + (qpow(4 * r + 2, t + 1) - 1) * inv(4 * r  + 1)) % MOD;
    if (m >= 3) sum = (sum + t / 2) % MOD;
    sum = (sum + 4 * r * (r + 1)) % MOD;
    if (t > 1) {
        sum = (sum + r * (t - 1)) % MOD;
        sum = (sum + r * (t / 2)) % MOD;
        sum = (sum + G->eval(2 * r)) % MOD;
    }
    return sum;
}

int main() {
    i64 t, L, R;
    scanf("%lld%lld%lld", &t, &L, &R);
    G = new Shit(t + 20, t);
    i64 ans = (F(t, R) - F(t, L - 1)) % MOD;
    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);
    return 0;
}
