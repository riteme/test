#include <cmath>
#include <cfloat>
#include <iostream>

using namespace std;

typedef long double Double;

Double Compute(Double x);
bool AlmostEqualToZero(Double n);

#define EPSILON 100

int main() {
    ios::sync_with_stdio(false);

    Double a, b;
    cin >> a >> b;

    // Double l = a, r = b;
    Double x = (a + b) / 2.0L;
    Double v = Compute(x);
    int n = 1;

    cout.precision(EPSILON);

    while (!AlmostEqualToZero(v) && n < EPSILON) {
        if (v < 0.0) {
            b = x;
            x = (x + a) / 2.0;
        } else {
            a = x;
            x = (x + b) / 2.0;
        }

        n++;
        cout << "x: " << x << endl;
        v = Compute(x);
    }  // while

    cout << x;

    return 0;
}  // function main

Double Compute(Double x) {
    return std::exp(x * std::log(2.0)) + std::exp(x * std::log(3.0)) -
           std::exp(x * std::log(4.0));
}

bool AlmostEqualToZero(Double n) { return std::fabs(n) < LDBL_EPSILON; }
