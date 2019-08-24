#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;
typedef __int128_t i8;

#define MOD 1000000007
#define INV2 500000004

i8 F(i8 n, i8 a, i8 b, i8 c) {
    if (n < 0) return 0;
    if (!a) return b / c * (n + 1) % MOD;
    if (a >= c) {
        return (F(n, a % c, b, c) + a / c * n % MOD * (n + 1) % MOD * INV2) % MOD;
    } else if (b >= c) {
        return (F(n, a, b % c, c) + b / c * (n + 1)) % MOD;
    } else {
        i8 m = (a * n + b) / c;
        return (m * n - F(m - 1, c, c - b - 1, a)) % MOD;
    }
}

int main() {
    i64 n, m;
    scanf("%lld%lld", &n, &m);
    i64 ans = 0;
    for (int i = 0; i < 63; i++) if ((m >> i) & 1) {
        i64 u = (F(n, m, 0, i8(1) << (i + 1)) << (i + 1)) % MOD;
        i64 v = (F(n, m, 0, i8(1) << i) << i) % MOD;
        ans = (ans + v - u) % MOD;
    }
    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);
    return 0;
}
