/**
 * 思路太僵化了，没往递推的方向想......
 * 用c(n)表示这个答案
 * 根据定义:
 * c(n) = c(n - 1) * 10^{L(n - 1)} + n
 * L(n)表示n在十进制下的长度
 * 考虑构造矩阵：
 * [10^L 1 1]   (c(n - 1))   (c(n))
 * [   0 1 1] x (  n - 1 ) = ( n  )
 * [   0 0 1]   (    1   )   ( 1  )
 * 对于10^L进行分组快速幂即可
 * 注意矩阵是右乘，计算答案时注意顺序
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef unsigned long long u64;

static u64 n, p;

inline void add(u64 &dest, u64 src) {
    dest += src;
    if (dest >= p)
        dest -= p;
}

struct Matrix {
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }

    void identity() {
        mat[0][0] = mat[1][1] = mat[2][2] = 1;
    }

    u64 mat[3][3];

    Matrix &operator*=(const Matrix &b) {
        u64 tmp [3][3];
        memset(tmp, 0, sizeof(tmp));

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    add(tmp[i][j], mat[i][k] * b.mat[k][j] % p);
                }
            }
        }

        memcpy(mat, tmp, sizeof(mat));
        return *this;
    }
};

inline Matrix quick_pow(Matrix a, u64 b) {
    Matrix r;
    r.identity();

    while (b) {
        if (b & 1)
            r *= a;
        a *= a;
        b >>= 1;
    }

    return r;
}

int main() {
    scanf("%llu%llu", &n, &p);

    Matrix ans;
    ans.identity();
    for (u64 tpow = 1; tpow <= n; tpow *= 10) {
        u64 bound = min(tpow * 10 - 1, n);
        Matrix t;
        t.mat[0][0] = tpow * 10 % p;
        t.mat[0][1] = t.mat[0][2] =
        t.mat[1][1] = t.mat[1][2] =
        t.mat[2][2] = 1;
        t = quick_pow(t, bound - tpow + 1);
        t *= ans;
        ans = t;
    }

    printf("%llu\n", ans.mat[0][2]);

    return 0;
}
