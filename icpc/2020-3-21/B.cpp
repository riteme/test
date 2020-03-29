#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define INF 0x3f3f3f3f

typedef long long i64;

int n;
i64 a[NMAX + 10];
int p[NMAX + 10];
i64 pre[NMAX + 10], suf[NMAX + 10];

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    n = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= n; i++)
        p[i] = i;
    p[n + 1] = 0;
    suf[n + 1] = pre[n + 1] = 0;

    sort(p + 1, p + n + 1, [](int i, int j) {
        return a[i] < a[j];
    });
}

void solve() {
    initialize();

    a[0] = a[n + 1] = INF;
    i64 cnt = 0;
    for (int j = 1; j <= n; j++) {
        int i = p[j];
        pre[j] = pre[j - 1] + cnt * (a[i] - a[p[j - 1]]);
        if (a[i] < a[i - 1] && a[i] < a[i + 1])
            cnt++;
        else if (a[i] > a[i - 1] && a[i] > a[i + 1])
            cnt--;
    }

    a[0] = a[n + 1] = -INF;
    cnt = 0;
    for (int j = n; j >= 1; j--) {
        int i = p[j];
        suf[j] = suf[j + 1] + cnt * (a[p[j + 1]] - a[i]);
        if (a[i] > a[i - 1] && a[i] > a[i + 1])
            cnt++;
        else if (a[i] < a[i - 1] && a[i] < a[i + 1])
            cnt--;
    }

    i64 mi = LLONG_MAX, lv = LLONG_MAX;
    cnt = 0;
    for (int i = 1; i <= n; i++) {
        i64 v = pre[i] + suf[i];
        if (v < mi) {
            mi = v;
            cnt = 1;
        } else if (v == mi && v == lv)
            cnt += a[p[i]] - a[p[i - 1]];
        lv = v;
    }

    printf("%lld %lld\n", mi, cnt);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        printf("Case %d: ", t);
        solve();
    }
    return 0;
}