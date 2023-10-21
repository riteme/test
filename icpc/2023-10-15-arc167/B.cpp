#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr i64 MOD = 998244353;
constexpr i64 INV2 = (MOD + 1) / 2;

int main() {
    i64 A, B;
    scanf("%lld%lld", &A, &B);
    i64 B2 = B % 2;
    B %= MOD;
    i64 d = 2, T = 1, T2 = 1;
    for ( ; d * d <= A; d++) {
        i64 k = 0;
        while (A % d == 0) {
            A /= d;
            k++;
        }
        T = T * (1 + B * k % MOD) % MOD;
        T2 = T2 * (1 + B2 * k % 2) % 2;
    }
    if (A > 1) {
        T = T * (1 + B) % MOD;
        T2 = T2 * (1 + B2) % 2;
    }
    i64 r = T2 * B2 % 2;
    i64 ans = (T * B - r) % MOD * INV2 % MOD;
    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);
    return 0;
}
