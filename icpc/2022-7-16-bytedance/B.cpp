#include <cstdio>
#include <cstring>

using i64 = long long;

char buf[128];
int cnt[10];

int main() {
    scanf("%s", buf);
    if (buf[0] == 'A') {
        i64 v;
        scanf("%lld", &v);
        if (v == 0) {
            for (int i = 0; i < 50; i++) {
                putchar('0');
            }
            puts("");
            return 0;
        }
        int s = 0;
        for (int i = 0; i < 10; i++) {
            cnt[i] = v % 10;
            s += cnt[i];
            v /= 10;
        }
        if (s <= 45) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < cnt[i]; j++) {
                    putchar('0' + i);
                }
            }
        } else {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 9 - cnt[i]; j++) {
                    putchar('0' + i);
                }
            }
            s = 90 - s;
            cnt[1] = 9 - cnt[1];
            while (s <= 40 || s % 10 != cnt[1]) {
                putchar('1');
                s++;
            }
        }
        puts("");
    } else {
        scanf("%s", buf);
        int s = strlen(buf);
        for (int i = 0; i < s; i++) {
            cnt[buf[i] - '0']++;
        }
        if (s == 50 && cnt[0] == 50) {
            puts("0");
            return 0;
        }
        if (s > 40) {
            cnt[1] = s % 10;
            for (int i = 0; i < 10; i++) {
                cnt[i] = 9 - cnt[i];
            }
        }
        i64 v = 0;
        for (int i = 9; i >= 0; i--) {
            v = v * 10 + cnt[i];
        }
        printf("%lld\n", v);
    }
    return 0;
}
