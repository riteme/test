#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000

int n;
i64 xs[NMAX + 10], ys[NMAX + 10];
int xi[NMAX + 10], yi[NMAX + 10];
i64 ax[NMAX + 10], ay[NMAX + 10];

void scan(i64 *x, int *p, i64 *a) {
    i64 pre = 0, suf = 0;
    for (int i = 1; i <= n; i++)
        suf += x[i];

    for (int c = 1; c <= n; c++) {
        int i = p[c];
        suf -= x[i];
        a[i] = (c - 1) * x[i] - pre + suf - (n - c) * x[i];
        pre += x[i];
    }
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", xs + i, ys + i);
        xi[i] = yi[i] = i;
    }

    sort(xi + 1, xi + n + 1, [](int i, int j) {
        return xs[i] < xs[j];
    });
    sort(yi + 1, yi + n + 1, [](int i, int j) {
        return ys[i] < ys[j];
    });

    scan(xs, xi, ax);
    scan(ys, yi, ay);

    i64 ans = LLONG_MAX;
    for (int i = 1; i <= n; i++)
        ans = min(ans, ax[i] + ay[i]);

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
        solve();
    return 0;
}