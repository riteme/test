#include <cstdio>

#include <algorithm>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int a;
            scanf("%d", &a);
            if (i == 1)
                ans = 3 * a;
            else
                ans = max(ans, a + 1);
        }
        ans += ans & 1;
        printf("%d\n", ans);
    }
}