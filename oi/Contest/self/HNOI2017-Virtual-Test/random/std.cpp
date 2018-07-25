#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>

using namespace std;

#define NMAX 10

typedef long long i64;

static int n;
static i64 s, p;

struct Vector {
    Vector() {
        memset(vec, 0, sizeof(vec));
    }

    i64 operator[](const size_t i) const {
        return vec[i];
    }

    i64 &operator[](const size_t i) {
        return vec[i];
    }

    i64 vec[NMAX];
};  // struct Vector

struct Matrix {
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }

    const i64 *operator[](const size_t i) const {
        return &mat[i][0];
    }

    i64 *operator[](const size_t i) {
        return &mat[i][0];
    }

    i64 mat[NMAX][NMAX];
};  // struct Matrix

Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= p;
            }  // for
        }      // for
    }          // for

    return c;
}

Vector operator*(const Matrix &a, const Vector &b) {
    Vector c;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i] += a[i][j] * b[j];
            c[i] %= p;
        }  // for
    }      // for

    return c;
}

static Vector;

void initialize() {}
