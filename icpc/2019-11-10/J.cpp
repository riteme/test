#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n;
static i64 a[NMAX + 10];

struct Pair {
    i64 a, b;
};

Pair p2(int L, int R) {
    int l = L, r = R - 1;
    while (l < r) {
        int m = (l + r) / 2 + 1;
        if (a[m] - a[L - 1] >= a[R] - a[m]) r = m - 1;
        else l = m;
    }
    if (abs(2 * a[l] - a[L - 1] - a[R]) < abs(2 * a[l + 1] - a[L - 1] - a[R]))
        return {a[l] - a[L - 1], a[R] - a[l]};
    else
        return {a[l + 1] - a[L - 1], a[R] - a[l + 1]};
}

i64 p4(int m) {
    auto L = p2(1, m);
    auto R = p2(m + 1, n);
    i64 mi = min(min(L.a, L.b), min(R.a, R.b));
    i64 mx = max(max(L.a, L.b), max(R.a, R.b));
    return mx - mi;
}

i64 solve() {
    i64 ret = LLONG_MAX;
    for (int i = 2; i <= n - 2; i++)
        ret = min(ret, p4(i));
    return ret;
}

int main() {
    scanf("%d", &n);
    scanf("%lld", a + n);
    for (int i = 1; i < n; i++)
        scanf("%lld", a + i);
    printf("%lld\n", solve());
    return 0;
}
