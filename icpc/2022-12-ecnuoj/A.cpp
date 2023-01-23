#include <cstdio>

using namespace std;

using i64 = long long;

constexpr int NMAX = 200000;

i64 kmax[NMAX + 10];
i64 pre[NMAX + 10];

int main() {
    kmax[2] = 1;
    for (i64 n = 3; n <= NMAX; n++) {
        kmax[n] = 114 * n * n - 514;
        if (kmax[n] < kmax[n - 1])
            kmax[n] = kmax[n - 1];
        pre[n] = pre[n - 1] + (n - 1) * (kmax[n] - kmax[n - 1]);
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        i64 k;
        scanf("%lld", &k);

        i64 l = 1, r = NMAX;
        while (l < r) {
            i64 m = (l + r) / 2;
            if (k < 114 * (m + 1) * (m + 1) - 514)
                r = m;
            else
                l = m + 1;
        }
        i64 n = l;
        i64 ans = (k - kmax[n] + 1) * n + pre[n];
        printf("%lld\n", ans);
    }

    return 0;
}
