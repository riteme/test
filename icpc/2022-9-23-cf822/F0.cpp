#include <cstdio>

#include <algorithm>

using namespace std;

using i64 = long long;

i64 nxtp(i64 x) {
    i64 k = 1;
    while (k <= x) {
        k <<= 1;
    }
    return k;
}

int walk(i64 x) {
    if (x <= 0)
        return 0;
    i64 k = nxtp(x) >> 1;
    return walk(x - k) ^ 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 i, n, j = 0;
        scanf("%lld%lld", &i, &n);
        for (int k = 0; k < n; k++) {
            putchar('0' + (walk(k) ^ walk(i + k)));
        }
        puts("");
        i64 ans = 0;
        while (n > 0) {
            int v = walk(i) ^ walk(j);
            i64 ki = min(nxtp(i), i + n);
            i64 kj = min(nxtp(j), j + n);
            i64 d = min(ki - i, kj - j);
            if (v)
                ans += d;
            n -= d;
            i += d;
            j += d;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
