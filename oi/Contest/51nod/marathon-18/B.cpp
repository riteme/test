#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MOD 1000000007

typedef long long int64;

struct Matrix {
    int64 mat[4][4];

    Matrix &operator*=(const Matrix &b) {
        int64 tmp[4][4];
        memset(tmp, 0, sizeof(tmp));

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    tmp[i][j] += mat[i][k] * b.mat[k][j] % MOD;
                    tmp[i][j] %= MOD;
                }  // for
            }      // for
        }          // for

        memcpy(mat, tmp, sizeof(tmp));

        return *this;
    }
};  // struct Matrix

inline Matrix quick_pow(int64 b) {
    Matrix a;
    memset(a.mat, 0, sizeof(a.mat));
    a.mat[0][0] = a.mat[0][2] = a.mat[1][0] = a.mat[1][2] = a.mat[2][3] =
        a.mat[3][1] = a.mat[3][3] = 1;

    Matrix r = a;

    while (b) {
        if (b & 1)
            r *= a;
        a *= a;
        b >>= 1;
    }  // while

    return r;
}

int main() {
    int64 n;
    scanf("%lld", &n);

    if (n == 0)
        puts("0");  // 1?
    else if (n == 1)
        puts("2");
    else if (n == 2)
        puts("4");
    else {
        Matrix m = quick_pow(n - 3);

        int64 answer = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                answer = (answer + m.mat[i][j]) % MOD;
            }  // for
        }      // for

        printf("%lld\n", answer);
    }

    return 0;
}  // function main
