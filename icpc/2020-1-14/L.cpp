#include <cstdio>

typedef long long i64;

int main() {
    i64 n;
    scanf("%lld", &n);
    int c = __builtin_popcountll(n);
    printf("%lld\n", (1LL << c));
    return 0;
}