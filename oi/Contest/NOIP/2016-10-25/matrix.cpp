#pragma GCC optimize(3)

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 50

typedef long long int64;

static int64 p;

struct Matrix {
    size_t size;
    int64 mat[NMAX][NMAX];

    void set_identity() {
        memset(mat, 0, sizeof(mat));

        for (size_t i = 0; i < size; i++)
            mat[i][i] = 1;
    }

    Matrix &operator=(const Matrix &b) {
        size = b.size;
        memcpy(mat, b.mat, sizeof(mat));

        return *this;
    }

    Matrix &operator*=(const Matrix &b) {
        static int64 c[NMAX][NMAX];
        memset(c, 0, sizeof(c));

        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                for (size_t k = 0; k < size; k++) {
                    c[i][j] += mat[i][k] * b.mat[k][j];
                    c[i][j] %= p;
                }
            }
        }

        memcpy(mat, c, sizeof(mat));

        return *this;
    }

    bool operator<(const Matrix &b) const {
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                if (mat[i][j] < b.mat[i][j])
                    return true;
                else if (mat[i][j] > b.mat[i][j])
                    return false;
            }
        }

        return false;
    }

    bool operator==(const Matrix &b) const {
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size; j++)
                if (mat[i][j] != b.mat[i][j])
                    return false;

        return true;
    }
};

static int n;
static Matrix A, B;

static int BSGS() {
    map<Matrix, int> table;

    int SQRTP = sqrt(p) + 0.5;
    Matrix BSA = B;
    table[B] = 0;
    for (int i = 1; i <= SQRTP; i++) {
        BSA *= A;

        table[BSA] = i;
    }

    Matrix SA = A;
    for (int i = 0; i < SQRTP - 1; i++)
        SA *= A;

    Matrix M;
    M.size = n;
    M.set_identity();
    for (int i = 0; i <= SQRTP; i++) {
        if (table.count(M))
            return i * SQRTP - table[M];

        M *= SA;
    }

    assert(false);
    return -1;
}

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    scanf("%d%lld", &n, &p);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &A.mat[i][j]);
    for (int i = 0; i < n; i++)
        for  (int j = 0; j < n; j++)
            scanf("%lld", &B.mat[i][j]);

    A.size = B.size = n;

    printf("%d\n", BSGS());

    fclose(stdin);
    fclose(stdout);
    return 0;
}
