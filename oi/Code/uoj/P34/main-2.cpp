/**
 * Iterative FFT
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <vector>
// #include <complex>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 10086
static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }
    return _buffer[_pos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();
    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }
    return x;
}

#define NMAX 300000

// typedef complex<double> Complex;

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

static int n, m;
static int ra;
static Complex x1[NMAX + 10];
static Complex X1[NMAX + 10];
static Complex x2[NMAX + 10];
static Complex X2[NMAX + 10];
static Complex x3[NMAX + 10];

inline int next_pow(int x) {
    int k = 1;
    while (k < x)
        k <<= 1;
    return k;
}

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = read<int>();
    m = read<int>();

    for (int i = 0; i <= n; i++)
        // scanf("%lf", &x1[i].real);
        x1[i].real = read<double>();
    for (int i = 0; i <= m; i++)
        // scanf("%lf", &x2[i].real);
        x2[i].real = read<double>();

    ra = next_pow(n + m + 2);
}

static void fft(int left, int right, Complex *input, Complex *output,
                bool reverse = false) {
    int n = right - left + 1;
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

const int BufferSize = 1180000;

char _BUFFER[BufferSize];
char *out_tail = _BUFFER;

inline void putint(int x) {
    if (!x)
        *out_tail++ = '0';
    else {
        char s_pool[6], *s_tail = s_pool;
        while (x != 0)
            *s_tail++ = x % 10 + '0', x /= 10;
        while (s_tail-- != s_pool)
            *out_tail++ = *s_tail;
    }
    *out_tail++ = ' ';
}

int main() {
    initialize();

    fft(0, ra - 1, x1, X1);
    fft(0, ra - 1, x2, X2);
    for (int i = 0; i < ra; i++)
        X2[i] *= X1[i];
    fft(0, ra - 1, X2, x3, true);
    for (int i = 0; i < ra; i++)
        x3[i] /= static_cast<double>(ra);

    for (int i = 0; i <= n + m; i++)
        // printf("%d ", int(x3[i].real + 0.5));
        putint(int(x3[i].real + 0.5));

    fwrite(_BUFFER, 1, out_tail - _BUFFER, stdout);
    return 0;
}  // function main
