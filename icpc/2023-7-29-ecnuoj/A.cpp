#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

using i64 = long long;

constexpr i64 MOD = 998244353;

i64 qpow(i64 a, i64 k) {
    i64 v = 1;
    for (; k; k >>= 1) {
        if (k & 1)
            v = v * a % MOD;
        a = a * a % MOD;
    }
    return v;
}

i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

i64 a(i64 n) {
    if (n == 2)
        return 1;
    return (qpow(n - 1, n) - n + 1) % MOD;
}

struct mat {
    i64 a00, a01, a10, a11;

    mat operator*(mat b) {
        mat c;
        c.a00 = (a00 * b.a00 + a01 * b.a10) % MOD;
        c.a01 = (a00 * b.a01 + a01 * b.a11) % MOD;
        c.a10 = (a10 * b.a00 + a11 * b.a10) % MOD;
        c.a11 = (a10 * b.a01 + a11 * b.a11) % MOD;
        return c;
    }
};

mat mqpow(mat a, i64 k) {
    mat v = {1, 0, 0, 1};
    for (; k; k >>= 1) {
        if (k & 1)
            v = v * a;
        a = a * a;
    }
    return v;
}

// i64 f(i64 n) {
//     mat T = {n * inv(n - 1) % MOD, 1, 0, 1};
//     T = mqpow(T, n);
//     i64 A = a(n);
//     return (A * T.a00 + T.a01) % MOD;
// }

i64 f(i64 n) {
    if (n == 2)
        return 7;
    return (qpow(n % MOD, n) - n % MOD + 1 + MOD) % MOD;
}

int main() {
    i64 n;
    scanf("%lld", &n);
    printf("%lld\n", f(n));
    return 0;
}
