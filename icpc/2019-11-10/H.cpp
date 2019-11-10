#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 1000000007

typedef long long i64;

static int n;
static i64 C[NMAX + 10], L[NMAX + 10];
static i64 rt[NMAX + 10];
static i64 dp[NMAX + 10], sum[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%lld", C + i);
    for (int i = 1; i < n; i++)
        scanf("%lld", L + i);

    for (int i = n - 1; i >= 1; i--)
        C[i] += C[i + 1];
    for (int i = n, j = n; i >= 1; i--) {
        while (j > i && C[j] != C[i]) j--;
        rt[i] = j - i + 1;
    }

    dp[n] = sum[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        int l = min(rt[i + 1], L[i]);
        dp[i] = (sum[i + 1] - sum[i + l + 1]) % MOD;
        sum[i] = (sum[i + 1] + dp[i]) % MOD;
    }

    if (dp[1] < 0) dp[1] += MOD;
    printf("%lld %lld\n", C[1], dp[1]);

    return 0;
}
