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
                bool reversed = false) {
    if (left == right) {
        output[left] = input[left];
        return;
    }

    memcpy(aux + left, input + left, sizeof(Complex) * (right - left + 1));
    size_t n = right - left + 1;
    size_t mid = (left + right) / 2;
    size_t pos = left;
    for (size_t i = left; i <= right; i += 2)
        input[pos++] = aux[i];
    for (size_t i = left + 1; i <= right; i += 2)
        input[pos++] = aux[i];

    fft(left, mid, input, output, reversed);
    fft(mid + 1, right, input, output, reversed);

    // A = A[0](w^2) + wA[1](w^2)
    Complex wn = exp(Complex(
        0, (reversed ? -1 : 1) * 2 * M_PI / n));  // Iterate to the next w
    Complex w = Complex(1);                       // w^0 = 1

    for (size_t k = 0; k <= n / 2 - 1; k++) {
        Complex t = w * output[mid + k + 1];
        output[mid + k + 1] = output[left + k] - t;
        output[left + k] = output[left + k] + t;
        w *= wn;
    }  // for
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
