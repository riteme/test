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

static void fft(size_t left, size_t right, Complex *input, Complex *output,
                bool reverse = false) {
    size_t n = right - left + 1;
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

    for (size_t s = 2; s <= n; s <<= 1) {
        Complex wn = my_exp((reverse ? -1.0 : 1.0) * 2.0 * M_PI / s);
        for (size_t i = 0; i < n; i += s) {
            size_t mid = i + (s >> 1);
            Complex w = Complex(1);

            for (size_t k = 0; k < s / 2; k++) {
                Complex t = output[mid + k] * w;
                output[mid + k] = output[i + k] - t;
                output[i + k] = output[i + k] + t;
                w *= wn;
            }  // for
        }      // for
    }          // for
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
