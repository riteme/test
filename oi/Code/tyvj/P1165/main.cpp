#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

// TODO(riteme): 坑爹的浮点数！！！！！！！！！！！

typedef complex<long double> Complex;

unsigned long GetDigit(const char c);
Complex GetComplex(const string &data);

int main(/*int argc, char *argv[]*/) {
    // long double base;
    Complex base;
    string baseData;

    while (cin >> baseData) {
        base = GetComplex(baseData);

        if (1 <= abs(base) && abs(base) < 10) {
            cout << base << endl;
            continue;
        }

        if (base == 0.0L) {
            cout << 0 << endl;
            continue;
        }

        // base * 10 ^ n
        int n = 0;
        bool baseOp = base >= 0;
        bool nOp = !(abs(base) < 1);
        base = abs(base);

        while (1 > base || base >= 10) {
            if (base < 1) {
                base *= 10.0L;
                n++;
            } else {
                base /= 10.0L;
                n++;
            }
        }  // while

        cout << (baseOp ? "" : "-");
        if (base != 1.0L) { cout << base << '*'; }

        cout << "10";
        if (n - (nOp ? 1 : 0) != 0) {
            cout << "^";
            cout << (nOp ? "" : "(-");
            cout << n;
            cout << (nOp ? "" : ")");
        }

        cout << endl;
    }  // while

    return 0;
}  // function main

unsigned long GetDigit(const char c) {
    switch (c) {
        case '0': return 0UL;
        case '1': return 1UL;
        case '2': return 2UL;
        case '3': return 3UL;
        case '4': return 4UL;
        case '5': return 5UL;
        case '6': return 6UL;
        case '7': return 7UL;
        case '8': return 8UL;
        case '9': return 9UL;
    }  // switch to c
}

Complex GetComplex(const string &data) {
    unsigned long real = 0, imag = 1;
    bool hasDot = false;
    int op = 1;

    for (auto c : data) {
        if (c == '-') {
            op = -1;
            continue;
        }
        if (c == '.') {
            hasDot = true;
            continue;
        }

        real = real * 10UL + GetDigit(c);
        imag *= hasDot ? 10UL : 1UL;

        return Complex(real, imag);
    }  // foreach in data
 }
