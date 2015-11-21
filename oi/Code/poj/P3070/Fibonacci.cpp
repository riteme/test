//
// Copyright 2015 riteme
//

// Accepted

#include <iostream>
#include <vector>

using namespace std;

struct Matrix {
    int m11, m12, m21, m22;

    Matrix operator*(const Matrix &mat) {
        Matrix result;

        result.m11 = m11 * mat.m11 + m12 * mat.m21;
        result.m12 = m11 * mat.m12 + m12 * mat.m22;
        result.m21 = m21 * mat.m11 + m22 * mat.m21;
        result.m22 = m21 * mat.m12 + m22 * mat.m22;

        return result;
    }

    Matrix &operator%(const int lhs) {
        m11 %= lhs;
        m12 %= lhs;
        m21 %= lhs;
        m22 %= lhs;

        return *this;
    }
};  // struct Matrix

static vector<int> exps;

// Matrix Compute(Matrix &mat, int exp) {
//     if (exp == 1) return mat;

//     if (exp % 2 == 1)
//         return ((Compute(mat, exp / 2) % 10000) *
//                 (Compute(mat, exp / 2) % 10000) * (mat % 10000)) %
//                10000;

//     return ((Compute(mat, exp / 2) % 10000) * (Compute(mat, exp / 2) %
//     10000)) %
//            10000;
// }

int Compute(int exp) {
    if (exp == 0) { return 0; }

    Matrix a;
    a.m11 = 1;
    a.m12 = 1;
    a.m21 = 1;
    a.m22 = 0;
    Matrix result;
    result.m11 = 1;
    result.m22 = 1;
    result.m12 = 0;
    result.m21 = 0;

    while (exp >= 1) {
        if (exp % 2) { result = (result * a) % 10000; }

        exp /= 2;
        a = (a * a) % 10000;
    }  // while

    return result.m12;
}

int main() {
    ios::sync_with_stdio();

    int tmp;
    while (true) {
        cin >> tmp;

        if (tmp != -1) { exps.push_back(tmp); } else {
            break;
        }
    }  // while

    for (int i = 0; i < exps.size(); i++) { cout << Compute(exps[i]) << '\n'; }

    return 0;
}  // function main
