#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define KMAX LLONG_MAX

typedef long long int64;

static int n;
static int64 k;
static int a[NMAX + 10];
static int b[NMAX + 10];

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

    void print() {
        for (int i = 1; i <= n; i++)
            printf("%d\n", left_distance[i]);
    }
};  // struct Matrix

static void quick_pow(Matrix &a, int64 b, Matrix &output) {
    while (b > 0) {
        if (b % 2 == 1)
            output *= a;
        a *= a;
        b /= 2;
    }  // while
}

static void generate(Matrix &a) {
    for (int i = 1; i <= n; i++)
        a.left_distance[i] = i;
}

int main() {
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", b + i);
    k %= n;

    Matrix p;
    for (int i = 1; i <= n; i++)
        p.left_distance[b[i]] = i;

    Matrix pk;
    generate(pk);
    quick_pow(p, k, pk);

    for (int i = 1; i <= n; i++)
        printf("%d ", a[pk.left_distance[i]]);

    return 0;
}  // function main
