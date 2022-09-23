#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int MMAX = 1000000;

int n;
i64 lo, hi;
i64 cnt[MMAX + 10];
i64 sum[MMAX + 10];
i64 f[17][MMAX + 10];
struct {
    i64 i, len;
} g[17][MMAX + 10];

int main() {
    scanf("%lld%lld%d", &lo, &hi, &n);
    hi = hi - lo + 1;
    for (int i = 0; i < n; i++) {
        i64 v;
        scanf("%lld", &v);
        cnt[v - lo]++;
    }

    sum[0] = cnt[0];
    for (i64 i = 1; i <= hi; i++) {
        sum[i] = sum[i - 1] + cnt[i];
    }

    memset(f, 0x3f, sizeof(f));
    f[0][hi] = 0;
    for (int t = 1; t <= 16; t++) {
        for (i64 i = 0; i < hi; i++)
        for (int j = 0; j < 5; j++) {
            i64 k = i + (1 << (4 * j));
            if (k >= hi)
                k = hi;
            i64 c = i > 0 ? sum[k - 1] - sum[i - 1] : sum[k - 1];

            if (f[t][i] > f[t - 1][k] + (j + 1) * c) {
                f[t][i] = f[t - 1][k] + (j + 1) * c;
                g[t][i] = {k, j};
            }
        };

        if (f[t][hi] > f[t - 1][hi]) {
            f[t][hi] = f[t - 1][hi];
            g[t][hi] = {hi, 0};
        }
    }

    i64 ans = f[16][0];
    i64 t = 16, i = 0;
    i64 s1, l1;
    for (int j = 1; j < 5; j++) {
        i64 s = 1 << (4 * j);
        for (i64 k = 1; k <= s; k++) {
            i64 c = sum[k - 1];
            if (ans > f[15][k] + (j + 1) * c) {
                ans = f[15][k] + (j + 1) * c;
                t = 15;
                i = k;
                s1 = k - s;
                l1 = j;
            }
        }
    }

    // fprintf(stderr, "ans=%lld\n", ans);
    if (t == 15)
        printf("%lld %lld\n", l1, s1 + lo);
    while (true) {
        printf("%lld %lld\n", g[t][i].len, i + lo);
        i = g[t][i].i;
        t--;
        if (t <= 0)
            break;
    }
    return 0;
}