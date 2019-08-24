#include <cmath>
#include <cfloat>
#include <iostream>
#include <complex>

using namespace std;

typedef complex<long double> Complex;

Complex Compute(Complex x);
bool AlmostEqualToZero(Complex n);

#define EPSILON 16

int main() {
    ios::sync_with_stdio(false);

    long double a, b;
    cin >> a >> b;

    Complex l = Complex(a);
    Complex r = Complex(b);
    Complex x = (l + r) / 2.0L;
    Complex v = Compute(x);
    int n = 1;

    cout.precision(EPSILON);
    cout << std::fixed;

    while (!AlmostEqualToZero(v) && n < EPSILON) {
        cout << "x: " << x << endl;

        if (v.real() < 0.0L) {
            r = x;
            x = (x + l) / 2.0L;
        } else {
            l = x;
            x = (x + r) / 2.0L;
        }

        n++;
        v = Compute(x);
    }  // while

    cout << x;

    return 0;
}  // function main

// Complex Compute(Complex x) {
//     return std::exp(x * std::log(Complex(2.0L))) +
//            std::exp(x * std::log(Complex(3.0L))) -
//            std::exp(x * std::log(Complex(4.0L)));
// }

Complex Compute(Complex x) {
    return std::pow(Complex(2.0L), x) + std::pow(Complex(3.0L), x) -
           std::pow(Complex(4.0L), x);
}

bool AlmostEqualToZero(Complex n) {
    return std::fabs(n.real() / n.imag()) < LDBL_EPSILON;
}
