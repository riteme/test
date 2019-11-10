// 4k ^ 4k+1 ^ 4k+2 ^ 4k+3 = 0
#include <cstdio>

typedef long long i64;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n;
        scanf("%lld", &n);
        i64 m = n % 4;
        n = (n >> 2) << 2;
        i64 ans = 0;
        for (i64 i = 0; i <= m; i++)
            ans ^= n + i;
        printf("%lld\n", ans);
    }
    return 0;
}
