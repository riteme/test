#include <cstdio>
#include <cstring>

#include <tuple>
#include <numeric>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

int n;
struct rect {
    int a, b, c, d;
} rt[NMAX + 10];
struct range {
    int l, r;
} ran[NMAX + 10];

enum : int {
    L = 1, R = 0
};

int m;
struct event {
    int t, p;

    bool operator<(const event &z) const {
        return tie(t, p) < tie(z.t, z.p);
    }
} ev[NMAX * 2 + 10];

i64 scanline() {
    m = 0;
    i64 lall = 0;
    for (int i = 1; i <= n; i++) {
        ev[m++] = {ran[i].l, L};
        ev[m++] = {ran[i].r, R};
        lall += ran[i].l;
    }
    sort(ev, ev + m);

    i64 ans = numeric_limits<i64>::max();
    i64 lcnt = 0, lsum = 0;
    i64 rcnt = 0, rsum = 0;
    for (int i = 0; i < m; i++) {
        i64 rax = (rcnt * ev[i].t - rsum) + (lall - lsum - (n - lcnt) * ev[i].t);
        ans = min(ans, rax);

        if (ev[i].p == L) {
            lcnt++;
            lsum += ev[i].t;
        } else {
            rcnt++;
            rsum += ev[i].t;
        }
    }

    return ans;
}

void _main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &rt[i].a, &rt[i].b, &rt[i].c, &rt[i].d);
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        ran[i] = {rt[i].a, rt[i].c};
    }
    ans += scanline();
    for (int i = 1; i <= n; i++) {
        ran[i] = {rt[i].b, rt[i].d};
    }
    ans += scanline();
    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}