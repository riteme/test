#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MOD 1000000007
#define K 5000000

typedef long long i64;

static i64 c[K];
static i64 inv[K + 10];

int main() {
    inv[1] = 1;
    for (int i = 2; i <= K + 5; i++)
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
    c[0] = 1;
    for (int i = 0; i + 1 < K; i++)
        c[i + 1] = c[i] * (K - i) % MOD * inv[i + 1] % MOD;
    for (int i = 1; i < K; i++)
        c[i] = (c[i] + c[i - 1]) % MOD;
    i64 pw = 1;
    for (int i = 0; i < K; i++)
        pw = pw * inv[2] % MOD;
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        i64 ans = (1 - c[n - 1] * pw) % MOD;
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
