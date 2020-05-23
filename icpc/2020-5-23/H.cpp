#include <cstdio>

typedef long long i64;

int main() {
    i64 x, k, T = 0;
    while (scanf("%lld%lld", &x, &k) != EOF) {
        T++;
        if (x == 0 && k == 0)
            break;

        i64 last = 0;
        for (i64 i = 1; i <= k; i++) {
            i64 y = (x + i - 1) / i;
            if (y == last)
                break;
            x = y * i;
            last = y;
        }
        x = last * k;
        printf("Case #%lld: %lld\n", T, x);
    }
    return 0;
}