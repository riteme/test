#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;

char s[NMAX];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d%s", &n, s);
        int cnt1 = 0, cnt11 = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1')
                cnt1++;
            if (i > 0 && s[i - 1] == '1' && s[i] == '1')
                cnt11++;
        }
        if (cnt1 % 2 == 1)
            puts("-1");
        else if (cnt1 == 2 && cnt11 == 1) {
            if (n == 3)
                puts("-1");
            else if (n == 4) {
                if (s[1] == '1' && s[2] == '1')
                    puts("3");
                else
                    puts("2");
            } else
                puts("2");
        } else
            printf("%d\n", cnt1 / 2);
    }
    return 0;
}
