#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 20
#define MOD 998244353

typedef long long i64;

static int n, perm[NMAX + 10];
static i64 A[NMAX + 10];

inline i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

inline i64 eval() {
    i64 pre = 0, ret = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        pre += A[perm[i]];
        ret = max(ret, pre);
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", A + i);
        perm[i] = i;
    }
    i64 ans = 0;
    do {
        ans = (ans + eval()) % MOD;
    } while (next_permutation(perm, perm + n));
    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);
    return 0;
}
