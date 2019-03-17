#include <cstdio>

#include <algorithm>

using namespace std;

int main() {
    int ans = 1, n;
    int a = 0, b = 0;
    scanf("%d", &n);
    while (n--) {
        int c, d;
        scanf("%d%d", &c, &d);
        if (a == b) ans += min(c - a, d - a);
        else if (c == d) ans += min(c - a, c - b) + 1;
        else ans += max(0, min(c, d) - max(a, b) + 1);
        a = c;
        b = d;
    }
    printf("%d\n", ans);
    return 0;
}
