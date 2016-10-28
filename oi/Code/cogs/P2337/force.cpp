#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include <algorithm>

using namespace std;

#define INPUT_BUFFERSIZE 100000
static size_t _ipos = INPUT_BUFFERSIZE;
static char _ibuffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (_ipos == INPUT_BUFFERSIZE) {
        _ipos = 0;
        fread(_ibuffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return _ibuffer[_ipos++];
}

inline size_t read_size_t() {
    size_t x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

inline double read_double() {
    char buffer[128];
    char c = _getchar();
    size_t pos = 0;

    while (c != '-' && c != '.' && !isdigit(c))
        c = _getchar();
    while (c == '-' || c == '.' || isdigit(c)) {
        buffer[pos++] = c;
        c = _getchar();
    }

    buffer[pos] = '\0';
    return atof(buffer);
}

#define OUTPUT_BUFFERSIZE 40000000
static size_t _opos = 0;
static char _obuffer[OUTPUT_BUFFERSIZE];

inline void write_double(const double d) {
    _opos += sprintf(_obuffer + _opos, "%.3lf\n", d); 
}

inline void flush_output() {
    fwrite(_obuffer, 1, _opos, stdout);
}

struct Complex {
    Complex() : real(0.0), imag(0.0) {}
    Complex(const double _real) : real(_real), imag(0.0) {}
    Complex(const double _real, const double _imag)
        : real(_real), imag(_imag) {}

    double real, imag;

    Complex operator+(const Complex &b) const {
        return Complex(real + b.real, imag + b.imag);
    }

    Complex operator-(const Complex &b) const {
        return Complex(real - b.real, imag - b.imag);
    }

    Complex operator*(const double &b) const {
        return Complex(real * b, imag * b);
    }

    Complex operator*(const Complex &b) const {
        return Complex(
            real * b.real - imag * b.imag,
            real * b.imag + imag * b.real
        );
    }

    Complex &operator+=(const Complex &b) {
        real += b.real;
        imag += b.imag;

        return *this;
    }

    Complex &operator-=(const Complex &b) {
        real -= b.real;
        imag -= b.imag;

        return *this;
    }

    Complex &operator*=(const double &b) {
        real *= b;
        imag *= b;

        return *this;
    }

    Complex &operator*=(const Complex &b) {
        *this = *this * b;
        return *this;
    }
};

inline Complex my_exp(const double &a) {
    return Complex(
        cos(a),
        sin(a)
    );
}

static void rader(Complex *input, Complex *output, size_t n) {
    size_t rev = 0;
    size_t pos = 0;
    while (pos < n) {
        output[pos++] = input[rev];

        size_t k =  n >> 1;
        while (rev & k) {
            rev ^= k;
            k >>= 1;
        }

        rev |= k;
    }
}

static void fft(
    Complex *input, Complex *output,
    size_t n, bool reversed = false
) {
    rader(input, output, n);

    for (size_t s = 2; s <= n; s <<= 1) {
        Complex w_n = my_exp(
            (reversed ? -2.0 : 2.0) * M_PI / s
        );

        for (size_t i = 0; i < n; i += s) {
            Complex w = Complex(1);

            size_t len = s >> 1;
            for (size_t j = 0; j < len; j++) {
                size_t pos = i + j;
                Complex t = w * output[pos + len];
                output[pos + len] = output[pos] - t;
                output[pos] += t;
                w *= w_n;
            }
        }
    }

    if (reversed)
        for (size_t i = 0; i < n; i++)
            output[i] *= 1.0 / n;
}

#define NMAX 100000

static size_t n;
static double q[NMAX + 10];
static double L[NMAX + 10];
static double R[NMAX + 10];

static Complex x1[NMAX * 3 + 100];
static Complex X1[NMAX * 3 + 100];
static Complex x2[NMAX * 3 + 100];
static Complex X2[NMAX * 3 + 100];

inline size_t next_pow(size_t x) {
    size_t k = 1;
    while (k < x)
        k <<= 1;

    return k;
}

static void initialize() {
    // scanf("%d", &n);
    n = read_size_t();

    for (size_t i = 1; i <= n; i++)
        // scanf("%lf", q + i);
        q[i] = read_double();
}

int main() {
    freopen("force.in", "r", stdin);
    freopen("force.out", "w", stdout);
    initialize();

    size_t size = next_pow(n * 2 + 2);
    
    for (size_t i = 1; i <= n; i++) {
        x1[i].real = q[i];
        x2[i].real = 1.0 / i / i; 
    }

    fft(x1, X1, size);
    fft(x2, X2, size);

    for (size_t i = 0; i < size; i++)
        X1[i] *= X2[i];

    fft(X1, x1, size, true);

    for (size_t i = 1; i <= n; i++)
        L[i] = x1[i].real;

    memset(x1, 0, sizeof(x1));

    for (size_t i = 1; i <= n; i++)
        x1[i].real = q[n - i + 1];

    fft(x1, X1, size);

    for (size_t i = 0; i < size; i++)
        X1[i] *= X2[i];

    fft(X1, x1, size, true);

    for (size_t i = 1; i <= n; i++)
        R[n - i + 1] = x1[i].real;

    for (size_t i = 1; i <= n; i++)
        // printf("%.6lf\n", L[i] - R[i]);
        write_double(L[i] - R[i]);

    flush_output();

    return 0;
}
