#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

static int exgcd(int a, int b, int &m, int &n) {
    if (b == 0) {
        m = 1;
        n = 0;
        return a;
    }

    int x, y;
    int r = exgcd(b, a % b, x, y);
    m = y;
    n = x - (a / b) * y;
    return r;
}

static int inv(int a, int p) {
    int x, k;
    exgcd(a, p, x, k);

    return x;
}

#define P 23
#define E 28
#define I 33
#define M (P * E * I)
#define M1 (E * I)
#define M2 (P * I)
#define M3 (P * E)

inline int mod(int a, int p) {
    int r = a % p;

    if (r < 0)
        return r + p;
    return r;
}

static int evaluate(int p, int e, int i, int d) {
    int a = p * M1 * inv(M1, P) + e * M2 * inv(M2, E) + i * M3 * inv(M3, I);
    a = mod(a - d, M);

    if (a <= 0)
        a += M;

    return a;
}

int main() {
    int p, e, i, d;
    int t = 1;
    while (scanf("%d%d%d%d", &p, &e, &i, &d)) {
        if (p == -1)
            break;

        printf("Case %d: the next triple peak occurs in %d days.\n", t++,
               evaluate(p % M, e % M, i % M, d));
    }  // while

    return 0;
}  // function main
