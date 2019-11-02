#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MOD 9973

typedef long long i64;

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 A, B;
        scanf("%lld%lld", &A, &B);
        B %= MOD;
        A = A * inv(B) % MOD;
        if (A < 0) A += MOD;
        printf("%lld\n", A);
    }
    return 0;
}
