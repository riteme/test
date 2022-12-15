#include <cstdio>

using i64 = long long;

char s[2000000];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 n;
        scanf("%lld%s", &n, s + 1);
        i64 ans = 0;
        for (i64 i = 1; i <= n; i++) {
            if (s[i] != '1') {
                for (i64 j = i; j <= n; j += i) {
                    if (s[j] == '0') {
                        s[j] = '2';
                        ans += i;
                    } else if (s[j] == '1')
                        break;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
