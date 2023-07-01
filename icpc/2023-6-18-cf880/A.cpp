#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

i64 minv(i64 d) {
    i64 v = 1;
    for (i64 i = 0; i < d - 1; i++) {
        v *= 10;
    }
    return v;
}

i64 maxv(i64 d) {
    return minv(d + 1) - 1;
}

void solve(i64 A, i64 B, i64 C, i64 K) {
    i64 minb0 = minv(B);
    i64 maxb0 = maxv(B);
    i64 minc = minv(C);
    i64 maxc = maxv(C);
    for (i64 a = minv(A); a <= maxv(A); a++) {
        i64 minb = max(minb0, minc - a);
        i64 maxb = min(maxb0, maxc - a);
        i64 cnt = maxb - minb + 1;
        if (cnt < 0)
            continue;
        if (K <= cnt) {
            i64 b = minb + K - 1;
            printf("%lld + %lld = %lld\n", a, b, a + b);
            return;
        }
        K -= cnt;
    }
    puts("-1");
}

int main() {
    i64 T;
    scanf("%lld", &T);
    while (T--) {
        i64 A, B, C, K;
        scanf("%lld%lld%lld%lld", &A, &B, &C, &K);
        solve(A, B, C, K);
    }
    return 0;
}
