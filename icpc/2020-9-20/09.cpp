#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define KMAX 500000

int K;
i64 MOD;
i64 _fi[KMAX + 10], _tmp[KMAX + 10];

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x);
}

i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    for ( ; k; k >>= 1) {
        if (k & 1)
            r = r * a % MOD;
        a = a * a % MOD;
    }
    return r;
}

i64 f[KMAX + 10];

void init() {
    _fi[0] = 1;
    for (int i = 2; i <= K + 1; i++) {
        _fi[0] = _fi[0] * i % MOD;
    }
    _fi[KMAX + 1] = inv(_fi[0]);
    for (int i = K; i >= 0; i--) {
        _fi[i] = _fi[i + 1] * (i + 1) % MOD;
    }
}

i64 _tmp[KMAX + 10];
void eval(i64 n) {
    n %= MOD;
    _tmp[K + 2] = 1;
    for (int i = K + 1; i >= 1; i--) {
        _tmp[i] = _tmp[i + 1] * (n - i) % MOD;
    }
    i64 ret = 0, pre = 1;
    for (int i = 0, b = K & 1 ? 1 : -1; i <= K + 1; i++, b = -b) {
        ret = (ret + b * f[i] * pre % MOD * _tmp[i + 1] % MOD * _fi[i] % MOD * _fi[K + 1 - i]) % MOD;
        pre = pre * (n - 1) % MOD;
    }

    if (ret < 0)
        ret += MOD;
    return ret;
}

void solve() {
    scanf("%d%lld", &K, &MOD);
    for (int i = 0; i <= K; i++) {
        scanf("%lld", f + i);
    }

}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d:\n", i);
        solve();
    }
    return 0;
}
