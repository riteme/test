#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;

using i64 = long long;

int m;
int a[NMAX];

void solve() {
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", a + i);
    }

    for (int n = 1; n <= m; n++) {
        sort(a, a + n);
        i64 ans = 0;
        int b = 0;
        for (int i = 0; i < n; i++) {
            if (b + 1 <= a[i])
                b++;
            ans += a[i] - b;
        }
        printf("%lld ", ans);
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
