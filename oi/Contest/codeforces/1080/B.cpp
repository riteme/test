#include <cstdio>

typedef long long i64;

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        i64 l, r;
        scanf("%lld%lld", &l, &r);
        i64 ans = (r - l + 1) / 2 * (l & 1 ? 1 : -1);
        if ((r - l) % 2 == 0) ans += r * (r & 1 ? -1 : 1);
        printf("%lld\n", ans);
    }
    return 0;
}
