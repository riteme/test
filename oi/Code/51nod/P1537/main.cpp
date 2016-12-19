#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MOD 1000000007

typedef long long int64;

struct SqrtNumber {
    SqrtNumber()
        : a(0), b(0) {}
    SqrtNumber(const int64 &_a, const int64 &_b)
        : a(_a), b(_b) {}

    int64 a;
    int64 b;

    void set_identity() {
        a = 1;
        b = 0;
    }

    SqrtNumber operator*(const SqrtNumber &lhs) const {
        return SqrtNumber(
                (a * lhs.a % MOD + 2 * b * lhs.b % MOD) % MOD,
                (a * lhs.b % MOD + b * lhs.a % MOD) % MOD
             );
    }
};

template <typename T>
inline T quick_pow(T a, int64 b) {
    T r;
    r.set_identity();

    while (b) {
        if (b & 1)
            r = r * a;
        a = a * a;
        b >>= 1;
    }

    return r;
}

inline bool equiv(const int64 &a, const int64 &b) {
    return (a + MOD) % MOD == (b + MOD) % MOD;
}

int main() {
    int64 n;
    scanf("%lld", &n);
    
    SqrtNumber x(1, 1);
    SqrtNumber xn = quick_pow(x, n);

    int64 a = xn.a * xn.a % MOD;
    int64 b = xn.b * xn.b * 2 % MOD;

    if (equiv(a - b, 1))
        printf("%lld\n", a);
    else if (equiv(b - a, 1))
        printf("%lld\n", b);
    else
        puts("no");

    return 0;
}
