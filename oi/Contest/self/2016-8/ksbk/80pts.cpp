#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define INPUT_BUFFERSIZE 4096
static size_t _pos = INPUT_BUFFERSIZE;
static char _buffer[INPUT_BUFFERSIZE];

inline char _getchar() {
    if (_pos == INPUT_BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, INPUT_BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 10000000

typedef unsigned long long uint64;

static int n;
static uint64 k;
static int a[NMAX + 10];
static int b[NMAX + 10];
static bool marked[NMAX + 10];
static uint64 length = 1;

static int top_distance[NMAX + 10];
static int top_pos[NMAX + 10];

struct Matrix {
    int left_distance[NMAX + 10];

    Matrix &operator*=(const Matrix &b) {
        for (int i = 1; i <= n; i++)
            top_distance[b.left_distance[i]] = i;
        for (int i = 1; i <= n; i++)
            top_pos[top_distance[i]] = i;

        memcpy(top_distance, left_distance, sizeof(left_distance));
        for (int i = 1; i <= n; i++)
            left_distance[i] = top_pos[top_distance[i]];

        return *this;
    }
};  // struct Matrix

static Matrix p;
static Matrix pk;

static void quick_pow(Matrix &a, uint64 b, Matrix &output) {
    while (b > 0) {
        if (b % 2 == 1)
            output *= a;
        a *= a;
        b /= 2;
    }  // while
}

inline void generate(Matrix &a) {
    for (int i = 1; i <= n; i++)
        a.left_distance[i] = i;
}

int main() {
    freopen("ksbk.in", "r", stdin);
    freopen("ksbk.out", "w", stdout);

    n = read<int>();
    k = read<uint64>();
    for (int i = 1; i <= n; i++)
        a[i] = read<int>();
    for (int i = 1; i <= n; i++)
        b[i] = read<int>();

    for (int i = 1; i <= n; i++)
        p.left_distance[b[i]] = i;

    generate(pk);
    quick_pow(p, k, pk);

    for (int i = 1; i <= n; i++)
        printf("%d ", a[pk.left_distance[i]]);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
