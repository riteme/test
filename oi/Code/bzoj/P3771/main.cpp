/**
 * 计算指定大小的子集和的方案数，对每一种答案分别统计
 * 这种需要计算一堆东西的计数问题可以考虑生成函数
 * 设$x$为选出一个的生成函数，即$\sum_{i=1}^n x^{a_i}$
 * 设$y$为选出两个**相同**的生成函数，即$\sum_{i=1}^n x^{a_i^2}$
 * 同理设$z = \sum_{i=1}^n x^{a_i^3}$
 * 那么选出一个的答案就是$x$
 * 选出两个的答案就是$(x^2 - y) / 2$，使用容斥减去多次选同一个的
 * 选出三个的答案是$(x^3 -3xy + 2z) /
 * 6$。之所以加上$2z$是因为$-3xy$时重复减去了。
 * 注意不能使用NTT，题目中没要求取模，答案会超出一般的NTT的模数。
 */

#define NDEBUG

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;

struct Complex {
    Complex() : real(0.0), imag(0.0) {}
    Complex(const double &_real) : real(_real), imag(0.0) {}
    Complex(const double &_real, const double &_imag)
            : real(_real), imag(_imag) {}

    double real, imag;

    friend Complex operator+(const Complex &a, const Complex &b);
    friend Complex operator-(const Complex &a, const Complex &b);
    friend Complex operator*(const Complex &a, const Complex &b);
    friend Complex operator/(const Complex &a, const double &b);

    Complex &operator*=(const Complex &b) {
        double re = real;
        double im = imag;
        real = (re * b.real - im * b.imag);
        imag = (re * b.imag + im * b.real);

        return *this;
    }
    Complex &operator/=(const double &b) {
        real /= b;
        imag /= b;

        return *this;
    }
};  // struct Complex

Complex operator+(const Complex &a, const Complex &b) {
    Complex c = Complex(a.real + b.real, a.imag + b.imag);

    return c;
}

Complex operator-(const Complex &a, const Complex &b) {
    Complex c = Complex(a.real - b.real, a.imag - b.imag);

    return c;
}

Complex operator*(const Complex &a, const Complex &b) {
    Complex c = Complex(a.real * b.real - a.imag * b.imag,
                        a.real * b.imag + a.imag * b.real);

    return c;
}

Complex operator/(const Complex &a, const double &b) {
    Complex c = Complex(a.real / b, a.imag / b);

    return c;
}

Complex my_exp(const double &x) {
    return Complex(cos(x), sin(x));
}

#define NMAX 262144
// #define NMAX 100

typedef long long int64;

inline int next_pow(int x) {
    int k = 1;
    while (k < x) {
        k <<= 1;
    }  // while
    return k;
}

static void _fft(int n, Complex *input, Complex *output, bool reverse = false) {
    output[0] = input[0];
    int rev = 0;
    for (int i = 1; i < n; i++) {
        int k = n >> 1;
        while (k <= rev) {
            rev -= k;
            k >>= 1;
        }
        rev += k;
        output[rev] = input[i];
    }  // for

    for (int s = 2; s <= n; s <<= 1) {
        // Caution please: slow floating operations
        Complex wn = my_exp((reverse ? -1.0 : 1.0) * 2.0 * M_PI / s);
        for (int i = 0; i < n; i += s) {
            int mid = i + (s >> 1);
            Complex w = Complex(1);
            for (int k = 0; k < s / 2; k++) {
                Complex t = output[mid + k] * w;
                output[mid + k] = output[i + k] - t;
                output[i + k] = output[i + k] + t;
                w *= wn;
            }  // for
        }      // for
    }          // for
}

static void fft(int n, Complex *input, Complex *output) {
    _fft(n, input, output);
}

static void reverse_fft(int n, Complex *input, Complex *output) {
    _fft(n, input, output, true);

    for (int i = 0; i < n; i++) {
        output[i] /= (double)n;
    }  // for
}

static int length;
static Complex x[NMAX];
static Complex y[NMAX];
static Complex z[NMAX];
static Complex seq1[NMAX];
static Complex seq2[NMAX];
static Complex seq3[NMAX];
static Complex seq4[NMAX];
static Complex g[NMAX];
static int64 cnt[NMAX];

static void initialize() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);

        x[a].real = 1.0;
        y[a * 2].real = 1.0;
        z[a * 3].real = 1.0;
        length = max(length, a);
    }  // for
    length++;
}

int main() {
    initialize();

    length = next_pow(length * 3 + 3);
    fft(length, x, seq1);
    fft(length, y, seq2);
    fft(length, z, seq3);

    // g1
    for (int i = 0; i < length; i++) {
        cnt[i] += int64(x[i].real + 0.5);
    }  // for

    // g2
    for (int i = 0; i < length; i++) {
        seq4[i] = seq1[i] * seq1[i] - seq2[i];
    }  // for

    reverse_fft(length, seq4, g);

    for (int i = 0; i < length; i++) {
        cnt[i] += int64(g[i].real / 2 + 0.5);
    }  // for

    // g3
    for (int i = 0; i < length; i++) {
        seq4[i] =
            seq1[i] * seq1[i] * seq1[i] - 3 * seq1[i] * seq2[i] + 2 * seq3[i];
    }  // for

    reverse_fft(length, seq4, g);

    for (int i = 0; i < length; i++) {
        cnt[i] += int64(g[i].real / 6 + 0.5);
    }  // for

    for (int i = 0; i < length; i++) {
        if (cnt[i] > 0) {
            printf("%d %lld\n", i, cnt[i]);
        }
    }  // for

    return 0;
}  // function main
