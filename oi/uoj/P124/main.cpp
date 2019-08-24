// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define LMAX 1000000
#define MOD 1000000007

struct Matrix {
    Matrix()
        : m11(0), m12(0), m13(0),
          m21(0), m22(0), m23(0),
          m31(0), m32(0), m33(0) {}

    i64 m11, m12, m13, m21, m22, m23, m31, m32, m33;

    void identity() {
        m11 = m22 = m33 = 1;
    }

    Matrix &operator*=(const Matrix &b) {
        static Matrix a;
        a = *this;

        m11 = (a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31) % MOD;
        m12 = (a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32) % MOD;
        m13 = (a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33) % MOD;
        m21 = (a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31) % MOD;
        m22 = (a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32) % MOD;
        m23 = (a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33) % MOD;
        m31 = (a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31) % MOD;
        m32 = (a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32) % MOD;
        m33 = (a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33) % MOD;

        return *this;
    }
};

inline void quick_pow(Matrix &a, const char *s, Matrix &r) {
    r.identity();

    int len = strlen(s);
    Matrix b;
    for (int i = len - 1; i >= 0; i--) {
        b = a;
        
        for (char c = '1'; c < s[i]; c++) {
            b *= a;
        }

        if (s[i] != '0')
            r *= b;

        for (char c = max('1', s[i]); c <= '9'; c++) {
            b *= a;
        }

        a = b;
    }
}

void minus1(char *n) {
    int len = strlen(n);
    n[--len]--;
    while (n[len] < '0') {
        n[len] = '9';
        n[--len]--;
    }
}

static char n[LMAX + 10], m[LMAX + 10];
static i64 a, b, c, d;

int main() {
    scanf("%s%s%lld%lld%lld%lld", n, m, &a, &b, &c, &d);

    Matrix A, B, T1, T2;
    A.m11 = a;
    A.m12 = A.m22 = A.m33 = 1;
    B.m11 = c;
    B.m13 = B.m22 = B.m33 = 1;

    minus1(n);
    minus1(m);
    quick_pow(A, m, T1);
    B *= T1;
    quick_pow(B, n, T2);
    T1 *= T2;

    printf("%lld\n", (T1.m11 + T1.m12 * b + T1.m13 * d) % MOD);
    return 0;
}
