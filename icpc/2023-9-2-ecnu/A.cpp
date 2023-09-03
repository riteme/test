#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

int n;
int a[20];

void solve() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }

    for (int S = 1; S < (1 << n) - 1; S++) {
        int s0 = 0, s1 = 0;
        for (int i = 0; i < n; i++) {
            if ((S >> i) & 1)
                s0 ^= a[i];
            else
                s1 ^= a[i];
        }
        if (s0 == s1) {
            puts("Yes");
            for (int i = 0; i < n; i++) {
                putchar(((S >> i) & 1) ? '1' : '0');
            }
            puts("");
            return;
        }
    }

    puts("No");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
