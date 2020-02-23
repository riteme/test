#include <cstdio>

typedef long long i64;

int main() {
    i64 n, m;
    scanf("%lld%lld", &n, &m);
    for (i64 k = 1; k < 10; k++)
        printf("%lld ", (k * n * m + 9) / 10);
    puts("");
    return 0;
}