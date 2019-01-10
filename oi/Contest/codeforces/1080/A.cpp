#include <cstdio>

typedef long long i64;

inline i64 div(i64 a, i64 b) {
    return a / b + (a % b ? 1 : 0);
}

int main() {
    i64 n, k;
    scanf("%lld%lld", &n, &k);
    i64 r = 2*n, g = 5*n, b = 8*n;
    printf("%lld\n", div(r, k) + div(g, k) + div(b, k));
    return 0;
}
