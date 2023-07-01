#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000000;

int n, K;
i64 m;
i64 a[NMAX + 10];

i64 eval(i64 x, i64 L, i64 R) {
    L = L < 0 ? 0 : (L + x) / 2 + 1;
    R = R < 0 ? m : (x + R - 1) / 2;
    if (x < L || x > R)
        return 0;
    return R - L + 1;
}

int main() {
    scanf("%d%lld%d", &n, &m, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }
    sort(a + 1, a + n + 1);
    a[n + 1] = m + 1;

    i64 max_len = 0;
    i64 min_pos = 0;
    int cnt = 1;
    for (int i = 0; i <= n; i++) {
        if (a[i] == a[i + 1]) {
            cnt++;
            continue;
        }

        if (a[i] == 0)
            cnt--;

        // printf("a[%d]=%lld, cnt=%d\n", i, a[i], cnt);

        i64 L, R;
        auto update = [&](i64 x) {
            i64 len = eval(x, L, R);
            if (len > max_len) {
                max_len = len;
                min_pos = x;
            } else if (len == max_len) {
                min_pos = min(min_pos, x);
            }
        };

        if (K > cnt) {
            L = i - K + 1 > 0 ? a[i - K + 1] : -1;
            R = i + K - cnt <= n ? a[i + K - cnt] : -1;
            update(a[i]);
        }

        L = i - K + 1 > 0 ? a[i - K + 1] : -1;
        R = i + K <= n ? a[i + K] : -1;

        for (i64 x = a[i] + 1; x < a[i + 1] && x < a[i] + 10; x++) {
            update(x);
        }
        for (i64 x = a[i + 1] - 1; x > a[i + 1] - 11 && x > a[i]; x--) {
            update(x);
        }

        if (a[i] != a[i + 1])
            cnt = 1;
    }

    printf("%lld %lld\n", max_len, min_pos);
    return 0;
}
