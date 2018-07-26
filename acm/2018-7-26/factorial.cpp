#include <cstdio>

#define MOD 1000000007

typedef long long i64;

int main() {
    int t;
    scanf("%d", &t);
    i64 f = 1;
    printf("1,");
    for (int i = 1; i < MOD; i++) {
        f = f * i % MOD;
        if (i % t == 0) printf("%lld,", f);
    }
    return 0;
}
