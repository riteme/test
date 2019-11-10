#include <cstdio>
#include <cstring>

typedef long long i64;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 A, B, C, D;
        scanf("%lld%lld%lld", &A, &B, &C);
        D = A + B;
        printf("%lld.", D / C);
        D %= C;
        for (int i = 0; i < 50; i++) {
            D *= 10;
            printf("%lld", D / C);
            D %= C;
        }
        puts("");
    }
    return 0;
}
