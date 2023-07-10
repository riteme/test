#include <cstdio>

using i64 = long long;

int main() {
    i64 n;
    scanf("%lld", &n);
    for (i64 m = n + 1; m <= 1000000; m++) {
        if (m * n % (m - n) == 0)
            printf("%lld ", m);
    }
    puts("");
    return 0;
}
