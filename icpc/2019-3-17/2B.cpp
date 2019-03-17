#include <cstdio>

typedef long long i64;

#define M 1000000LL

i64 udiv(i64 a, i64 b) {
    return a / b + (a % b > 0);
}

int main() {
    i64 K;
    scanf("%lld", &K);
    i64 l = udiv(K - M + 2, M - 1);
    i64 x = K + 2 - (M - 1) * l;
    printf("%lld\n", l + 2);
    printf("-1 ");
    for (int i = 1; i <= l; i++) printf("%lld ", M);
    printf("%lld\n", x);

    return 0;
}
