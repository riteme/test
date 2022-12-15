#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

using i64 = long long;

i64 a[1000];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", a + i);
        }
        i64 ans = LLONG_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    ans = min(ans, abs(a[j] - a[i]) + abs(a[k] - a[i]));
                    ans = min(ans, abs(a[i] - a[j]) + abs(a[k] - a[j]));
                    ans = min(ans, abs(a[i] - a[k]) + abs(a[j] - a[k]));
                }
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}
