// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define MOD 1000000007

struct Matrix {
    i64 mat[13][13];

    void set_identity() {
        memset(mat, 0, sizeof(mat));

        for (int i = 0; i < 13; i++) {
            mat[i][i] = 1;
        }
    }

    Matrix operator*=(const Matrix &b) {
        static Matrix c;
        memset(&c, 0, sizeof(c));

        for (size_t i = 0; i < 13; i++) {
            for (size_t j = 0; j < 13; j++) {
                for (size_t k = 0; k < 13; k++) {
                    c.mat[i][j] += mat[i][k] * b.mat[k][j] % MOD;
                    c.mat[i][j] %= MOD;
                }
            }
        }

        memcpy(this, &c, sizeof(c));
        return *this;
    }
};

inline void quick_pow(Matrix &a, i64 b, Matrix &r) {
    r.set_identity();

    for (; b; b >>= 1, a *= a) {
        if (b & 1)
            r *= a;
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("fox.in", "r", stdin);
    freopen("fox.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);

    while (T--) {
        i64 t, S, L, R;
        scanf("%lld%lld%lld%lld", &t, &S, &L, &R);
        Matrix M = {{
            {S + L + R, 0, S, 0, 0, -S, 0, S, 0, 0, -S, 0, 0},
            {0, S, 0, S, 0, 0, 0, R, 0, 0, L, 0, 0},
            {0, 0, S, 0, 0, 0, 0, 0, R, 0, 0, L, 0},
            {0, 0, 0, S, 0, 0, 0, 0, 0, R, 0, 0, L},
            {0, 0, 0, 0, S, 0,-S, L, 0, 0, R, 0, 0},
            {0, 0, 0, 0, 0, S, 0, 0, L, 0, 0, R, 0},
            {0, 0, 0, 0, 0, 0, S, 0, 0, L, 0, 0, R},
            {0, L, 0, 0, R, 0, 0, S, 0, 0, 0, 0, 0},
            {0, 0, L, 0, 0, R, 0, 0, S, S, 0, 0, 0},
            {0, 0, 0, L, 0, 0, R, 0, 0, S, 0, 0, 0},
            {0, R, 0, 0, L, 0, 0, 0, 0, 0, S, 0, 0},
            {0, 0, R, 0, 0, L, 0, 0, 0, 0, 0, S,-S},
            {0, 0, 0, R, 0, 0, L, 0, 0, 0, 0, 0, S}
        }};

        Matrix r;
        quick_pow(M, t, r);

        i64 ans = r.mat[0][3];
        if (ans < 0)
            ans += MOD;
        printf("%lld\n", ans);
    }

    return 0;
}
