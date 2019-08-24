#include <iostream>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <complex>
#include <algorithm>

using namespace std;

#define NMAX 1000

typedef long double float128;
typedef complex<float128> Complex;

static size_t n;
static Complex x[NMAX];
static Complex X[NMAX];
static Complex rx[NMAX];

int main() {
    cin >> n;
    for (size_t i = 0; i < n; i++) {
        cin >> x[i];
    }  // for

    for (size_t k = 0; k < n; k++) {
        Complex v;
        for (size_t j = 0; j < n; j++) {
            v += x[j] * exp(Complex(0, (2 * M_PI * j * k) / n));
        }  // for
        X[k] = v;
    }  // for

    for (size_t k = 0; k < n; k++) {
        Complex v;
        for (size_t j = 0; j < n; j++) {
            v += X[j] * exp(Complex(0, (-2 * M_PI * j * k) / n));
        }  // for
        rx[k] = v / static_cast<float128>(n);
        // rx[k] = v;
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
