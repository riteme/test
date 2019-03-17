#include <cstdio>

typedef long long i64;

static i64 w1, h1, w2, h2;

int main() {
    scanf("%lld%lld%lld%lld", &w1, &h1, &w2, &h2);
    printf("%lld\n", w1 + 2 + 2 * h1 + 2 * h2 + w2 + 2 + w1 - w2);
    return 0;
}
