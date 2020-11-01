#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

void solve() {
    int n, m, K;
    scanf("%d%d%d", &n, &m, &K);

    i64 ans = 2 * (K - 1), L = n + 1;
    for (int i = 0; i < m; i++) {
        i64 x;
        scanf("%lld", &x);
        ans += 2 * abs(x - K);
        L = min(L, x);
    }

    if (L < K) {
        ans -= 2 * abs(L - K);
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
