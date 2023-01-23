#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int w, d, h;
        int a, b, x, y;
        scanf("%d%d%d%d%d%d%d", &w, &d, &h, &a, &b, &x, &y);
        int ans = h + min(
            min(abs(a - x) + b + y, abs(a - x) + d - b + d - y),
            min(abs(b - y) + a + x, abs(b - y) + w - a + w - x)
        );
        printf("%d\n", ans);
    }
    return 0;
}
