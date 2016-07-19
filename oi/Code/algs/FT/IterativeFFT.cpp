#include <iostream>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <complex>
#include <algorithm>

using namespace std;

#define NMAX 1024

typedef long double float128;
typedef complex<float128> Complex;

static size_t n;
static Complex x[NMAX];
static Complex ix[NMAX];
static Complex X[NMAX];
static Complex iX[NMAX];
static Complex rx[NMAX];
static Complex aux[NMAX];

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
    cin >> n;
    for (size_t i = 0; i < n; i++) {
        cin >> x[i];
    }  // for

    memcpy(ix, x, sizeof(x));
    fft(0, n - 1, ix, X);

    memcpy(iX, X, sizeof(X));
    fft(0, n - 1, iX, rx, true);
    for (size_t i = 0; i < n; i++) {
        rx[i] /= float128(n);
    }  // for

    // cout.precision(24);
    cout << fixed;

    cout << "x_k:" << endl;
    for (size_t i = 0; i < n; i++) {
        cout << x[i] << " ";
    }  // for
    cout << endl;

    cout << "X_k:" << endl;
    for (size_t i = 0; i < n; i++) {
        cout << X[i] << " ";
    }  // for
    cout << endl;

    cout << "x_k:" << endl;
    for (size_t i = 0; i < n; i++) {
        cout << rx[i] << " ";
    }  // for
    cout << endl;

    return 0;
}  // function main
