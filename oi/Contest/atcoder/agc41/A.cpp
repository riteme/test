#include <cstdio>

#include <algorithm>

using namespace std;

typedef long long i64;

int main() {
    i64 n, L, R;
    scanf("%lld%lld%lld", &n, &L, &R);
    if (L > R) swap(L, R);
    i64 ans = min(max(L, R) - 1, n - min(L, R));
    if ((R - L) % 2 == 0) {
        ans = min(ans, abs(R - L) / 2);
    } else {
        ans = min(ans, L + (R - L - 1) / 2);
        ans = min(ans, n - R + 1 + (R - L - 1) / 2);
    }
    printf("%lld\n", ans);
    return 0;
}
