/**
 * Recursive FFT
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

#define NMAX 300000

typedef complex<double> Complex;

static int n, m;
static int ra;
static Complex x1[NMAX + 10];
static Complex X1[NMAX + 10];
static Complex x2[NMAX + 10];
static Complex X2[NMAX + 10];
static Complex x3[NMAX + 10];
static Complex aux[NMAX + 10];

inline int next_pow(int x) {
    int k = 1;
    while (k < x)
        k <<= 1;
    return k;
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i <= n; i++) {
        double v;
        scanf("%lf", &v);
        x1[i].real(v);
    }
    for (int i = 0; i <= m; i++) {
        double v;
        scanf("%lf", &v);
        x2[i].real(v);
    }

    ra = next_pow(n + m + 2);
}

inline void quick_dft(size_t left, size_t right, Complex *output,
                      bool reverse = false) {
    size_t n = right - left + 1;
    size_t mid = (left + right) / 2;
    Complex wn = exp(Complex(0, (reverse ? -1 : 1) * 2 * M_PI / n));
    Complex w = Complex(1);
    for (size_t k = 0; k < n / 2; k++) {
        Complex t = output[mid + k + 1] * w;
        output[mid + k + 1] = output[left + k] - t;
        output[left + k] = output[left + k] + t;
        w *= wn;
    }  // for
}

inline void radering(size_t n, Complex *input, Complex *output) {
    output[0] = input[0];
    size_t rev = 0;
    for (size_t i = 1; i < n; i++) {
        size_t k = n >> 1;
        while (k <= rev) {
            rev -= k;
            k >>= 1;
        }
        rev += k;
        output[rev] = input[i];
    }  // for
}

static void fft(size_t left, size_t right, Complex *input, Complex *output,
                bool reverse = false) {
    size_t n = right - left + 1;
    radering(n, input, output);

    for (size_t s = 1; (1 << s) <= n; s++) {
        for (size_t i = 0; i < n; i += (1 << s)) {
            quick_dft(i, i + (1 << s) - 1, output, reverse);
        }  // for
    }      // for
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
        printf("%d ", int(x3[i].real() + 0.5));

    return 0;
}  // function main
