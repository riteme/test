#include <cstdio>

using i64 = long long;

int main() {
    i64 n, m;
    scanf("%lld%lld", &n, &m);
    i64 pw = 1, s = 0;
    i64 li = 0, lc = 0;
    for (i64 i = 1; i <= n; i++) {
        s = (s + pw) % m;
        pw = pw * 10 % m;
        for (i64 c = 1; c <= 9; c++) {
            if (s * c % m == 0) {
                li = i;
                lc = c;
            }
        }
    }
    if (li > 0) {
        for (i64 j = 0; j < li; j++) {
            putchar('0' + lc);
        }
        puts("");
    } else {
        puts("-1");
    }
    return 0;
}
