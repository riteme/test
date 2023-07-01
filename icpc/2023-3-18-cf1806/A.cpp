#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int ans = 0;
        int dx = c - a;
        int dy = d - b;
        if (dy < 0) {
            puts("-1");
            continue;
        }
        ans += dy;
        dx -= dy;
        if (dx > 0) {
            puts("-1");
            continue;
        }
        ans += -dx;
        printf("%d\n", ans);
    }
    return 0;
}
