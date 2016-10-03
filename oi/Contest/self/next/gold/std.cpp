#include <cstdio>
#include <cstring>
#include <algorithm>

#define NMAX 256
#define MOD 1073741824
#define BMOD (MOD - 1)

typedef long long int64;

static int64 tmp[NMAX][NMAX];

struct Matrix {
    Matrix(size_t _n) : n(_n) {
        memset(mat, 0, sizeof(mat));
    }

    size_t n;
    int64 mat[NMAX][NMAX];

    void set_identity() {
        for (size_t i = 0; i < n; i++)
            mat[i][i] = 1;
    }

    Matrix &operator*=(const Matrix &b) {
        memset(tmp, 0, sizeof(tmp));

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                for (size_t k = 0; k < n; k++) {
                    tmp[i][j] += (mat[i][k] * b.mat[k][j]) & BMOD;
                    tmp[i][j] &= BMOD;
                }  // for
            }      // for
        }          // for

        memcpy(mat, tmp, sizeof(mat));
        return *this;
    }
};  // struct Matrix

inline void quick_pow(Matrix &a, int64 b, Matrix &c) {
    while (b) {
        if (b & 1)
            c *= a;
        a *= a;
        b >>= 1;
    }  // while
}

static int64 T, K, C;
static bool valid[NMAX];

inline int count_bit(size_t x) {
    int answer = 0;

    for (int i = 0; i < K; i++)
        answer += (x & (1 << i)) >> i;

    return answer;
}

int main() {
    freopen("gold.in", "r", stdin);
    freopen("gold.out", "w", stdout);
    scanf("%lld%lld%lld", &T, &K, &C);

    size_t size = 1 << K;
    size_t pos = 0;
    for (; pos < size; pos++)
        if (count_bit(pos) < C)
            valid[pos] = true;

    if (T < K)
        printf("%d\n", 1 << T);
    else if (T == K)
        printf("%ld\n", std::count(valid, valid + size, true));
    else {
        Matrix f(size);
        Matrix r(size);
        r.set_identity();

        pos = 0;
        size_t mask = (size >> 1) - 1;
        for (; pos < (size >> 1); pos++) {
            if (valid[pos << 1]) {
                size_t next = (pos << 1) & mask;
                f.mat[next][pos] = 1;
            }

            if (valid[(pos << 1) | 1]) {
                size_t next = ((pos << 1) | 1) & mask;
                f.mat[next][pos] = 1;
            }
        }  // for

        quick_pow(f, T - K + 1, r);

        int64 answer = 0;
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                answer += r.mat[i][j];
                answer &= BMOD;
            }  // for
        }      // for

        printf("%lld\n", answer);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
