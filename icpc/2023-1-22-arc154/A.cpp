#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;
constexpr i64 MOD = 998244353;

int n;
char A[NMAX], B[NMAX];

int main() {
    scanf("%d%s%s", &n, A, B);
    for (int i = 0; i < n; i++) {
        char a = A[i];
        char b = B[i];
        A[i] = min(a, b);
        B[i] = max(a, b);
    }
    i64 a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        a = (a * 10 + A[i] - '0') % MOD;
        b = (b * 10 + B[i] - '0') % MOD;
    }
    printf("%lld\n", a * b % MOD);
    return 0;
}
