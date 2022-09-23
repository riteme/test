#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000000;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n;
int a[NMAX + 10];
int lp[NMAX + 10], rp[NMAX + 10];
i64 ls[NMAX + 10], rs[NMAX + 10];
int stk[NMAX + 10], t;
i64 f[NMAX + 10];

i64 solve2() {
    f[0] = 0;
    memset(f + 1, 0x3f, sizeof(i64) * n);

    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", a[i]);
    // }
    // puts("");

    t = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < a[i]; j++) {
            stk[++t] = i;
        }
        if (a[i]) {
            rp[i] = -1;
            rs[i] = 0;
            continue;
        }
        if (t) {
            lp[i] = stk[t--];
            ls[i] = i - lp[i];
        } else {
            lp[i] = -1;
            ls[i] = 0;
        }
    }
    t = 0;
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j < a[i]; j++) {
            stk[++t] = i;
        }
        if (a[i]) {
            lp[i] = -1;
            ls[i] = 0;
            continue;
        }
        if (t) {
            rp[i] = stk[t--];
            rs[i] = rp[i] - i;
        } else {
            rp[i] = -1;
            rs[i] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        ls[i] += ls[i - 1];
        rs[i] += rs[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            f[i] = min(f[i], f[i - 1]);
        }
        if (i > 1 && !a[i - 1] && !a[i] && lp[i - 1] > 0 && rp[i] > 0) {
            int l = lp[i - 1];
            int r = rp[i];
            i64 s = rs[r] - rs[i - 1] + ls[i - 1] - ls[l - 1];
            // printf("%d [%d, %d] %lld\n", i, l, r, s);
            f[r] = min(f[r], f[l] + s);
        }
        if ((i == 1 || a[i - 1]) && !a[i] && rp[i] > 0) {
            int l = i;
            int r = rp[i];
            i64 s = rs[r] - rs[i - 1];
            // printf("%d [%d, %d] %lld\n", i, l, r, s);
            f[r] = min(f[r], f[l - 1] + s);
        }
        if ((i == n || a[i + 1]) && !a[i] && lp[i] > 0) {
            int l = lp[i];
            int r = i;
            i64 s = ls[i] - ls[l - 1];
            // printf("%d [%d, %d] %lld\n", i, l, r, s);
            f[r] = min(f[r], f[l] + s);
        }
    }

    return f[n] < INF ? f[n] : INF;
}

int b[NMAX + 10];

i64 solve1(int k) {
    memcpy(a + 1, b + 1, sizeof(int) * n);
    i64 sum = 0;
    for (int i = k + 1; i <= n; i++) {
        a[k] += a[i];
        sum += i64(a[i]) * (i - k);
    }
    int m = n;
    n = k;
    i64 ans = solve2();
    n = m;
    ans += sum;
    return ans < INF ? ans : INF;
}

int main() {
    int c;
    scanf("%d", &c);
    for (int i = 0; i < c; i++) {
        int v;
        scanf("%d", &v);
        a[v]++;
        n = max(n, v);
    }
    memcpy(b + 1, a + 1, sizeof(int) * n);
    int l = 1, r = n;
    while (l + 2 < r) {
        int m1 = (2 * l + r) / 3;
        int m2 = (l + 2 * r) / 3;
        i64 r1 = solve1(m1);
        i64 r2 = solve1(m2);
        if (r1 < r2)
            r = m2;
        else
            l = m1;
    }
    i64 ans = INF;
    for (int k = l; k <= r; k++) {
        ans = min(ans, solve1(k));
    }
    // for (int k = 1; k <= n; k++) {
    //     printf("%d: %lld\n", k, solve1(k));
    // }
    printf("%lld\n", ans);
    return 0;
}
