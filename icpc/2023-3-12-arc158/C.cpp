#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

using i64 = long long;

constexpr int KMAX = 16;
constexpr int NMAX = 200000;

int n;
i64 a[NMAX + 10], a0[NMAX + 10];
i64 cnt[10];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", a + i);
    }
    memcpy(a0, a, sizeof(a));
    i64 ans = 0;
    i64 m0 = 1;
    for (int k = 1; k < KMAX; k++) {
        m0 *= 10;
    }
    for (int k0 = KMAX - 1; k0 > 0; k0--, m0 /= 10) {
        for (int i = 0; i < n; i++) {
            a[i] %= m0 * 10;
        }
        sort(a, a + n);
        for (int i = 0; i < n; i++) {
            int p0 = (a[i] / m0) % 10;
            // printf("i=%d, k0=%d, p0=%d\n", i, k0, p0);
            i64 Lb0 = (9 - p0) * m0;
            int L0 = lower_bound(a, a + n, Lb0) - a;
            int R0 = upper_bound(a, a + n, Lb0 + m0 - 1) - a;

            i64 m = m0 / 10;
            int L = L0, R = R0;
            i64 Lb = Lb0;
            for (int k = k0 - 1; k >= 0; k--, m /= 10) {
                int p = (a[i] / m) % 10;
                Lb += (9 - p) * m;
                int l = lower_bound(a + L, a + R, Lb) - a;
                int r = upper_bound(a + L, a + R, Lb + m - 1) - a;
                // printf("i=%d, k=%d, p=%d, r=%d, R=%d\n", i, k, p, r, R);
                ans -= 9 * (R - r);
                L = l;
                R = r;
            }
        }
    }
    memcpy(a, a0, sizeof(a));
    for (int k = 0; k < KMAX; k++) {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            cnt[a[i] % 10]++;
            a[i] /= 10;
        }
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                ans += ((x + y) % 10 + (x + y >= 10)) * cnt[x] * cnt[y];
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
