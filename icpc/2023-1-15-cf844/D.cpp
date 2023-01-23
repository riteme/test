#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>

using namespace std;

using i64 = long long;

constexpr int NMAX = 50;
constexpr i64 XMAX = 1000000000000000000;

int n;
i64 a[NMAX];
unordered_map<i64, int> cnt;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", a + i);
        }
        sort(a, a + n);
        cnt.clear();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                i64 d = a[j] - a[i];
                for (i64 b = 1; b * b <= d; b++) {
                    if (d % b != 0)
                        continue;
                    i64 t = d / b - b;
                    if (t % 2 != 0)
                        continue;
                    t /= 2;
                    i64 x = t * t - a[i];
                    if (x < 0 || x > XMAX)
                        continue;
                    cnt[x]++;
                }
            }
        }

        int ans = 1;
        for (auto &e : cnt) {
            int c = e.second;
            for (int k = 1; k <= n; k++) {
                if (k * (k - 1) / 2 == c)
                    ans = max(ans, k);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
