#include <cstdio>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;
constexpr i64 MOD = 998244353;

int n;
int A[NMAX + 10], B[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", A + i, B + i);
    }
    i64 f0 = 1, f1 = 1;
    for (int i = 2; i <= n; i++) {
        i64 g0 = 0, g1 = 0;
        if (A[i] != A[i - 1])
            g0 += f0;
        if (A[i] != B[i - 1])
            g0 += f1;
        if (B[i] != A[i - 1])
            g1 += f0;
        if (B[i] != B[i - 1])
            g1 += f1;
        f0 = g0 % MOD;
        f1 = g1 % MOD;
    }
    i64 ans = (f0 + f1) % MOD;
    printf("%lld\n", ans);
    return 0;
}
