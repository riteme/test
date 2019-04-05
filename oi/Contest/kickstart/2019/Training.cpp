#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n, K;
static int S[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d", &n, &K);
        for (int i = 1; i <= n; i++) scanf("%d", S + i);
        sort(S + 1, S + n + 1);
        i64 ans = LLONG_MAX, sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += min(i - 1, K) * (S[i] - S[i - 1]);
            if (i > K) sum -= S[i] - S[i - K];
            if (i >= K) ans = min(ans, sum);
        }
        printf("Case #%d: %lld\n", t, ans);
    }
    return 0;
}
