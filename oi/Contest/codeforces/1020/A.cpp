#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

static i64 n, h, a, b, q;
#define out(x) printf("%lld\n", x);

int main() {
    scanf("%lld%lld%lld%lld%lld", &n, &h, &a, &b, &q);

    while (q--) {
        i64 x1, y1, x2, y2;
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        if (x1 == x2)
            printf("%lld\n", abs(y1 - y2));
        else {
            if (y1 < a) {
                if (y2 < a) {
                    printf("%lld\n", abs(x1 - x2) + abs(y1 - a) + abs(y2 - a));
                } else {
                    out(abs(x1 - x2) + abs(y1 - y2));
                }
            } else if (y1 > b) {
                if (y2 > b) {
                    out(abs(x1 - x2) + abs(y1 - b) + abs(y2 - b));
                } else {
                    out(abs(x1 - x2) + abs(y1 - y2));
                }
            } else {
                out(abs(x1 - x2) + abs(y1 - y2));
            }
        }
    }

    return 0;
}
