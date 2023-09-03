#include <cstdio>
#include <cassert>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 10000;
constexpr int KMAX = 61;
constexpr int CNTMAX = 100000;

struct lp {
    mutable i64 l;
    mutable int v;

    bool operator<(const lp &z) const {
        return l < z.l;
    }
};

int n;
i64 L[NMAX + 10], R[NMAX + 10];
set<lp> f;
lp g[CNTMAX];

void dp(int k) {
    i64 x = 0;
    i64 xmax = 1ll << k;
    int cnt = 0;
    while (x < xmax) {
        auto t0 = prev(f.upper_bound(lp{x, 0}));
        auto t1 = prev(f.upper_bound(lp{x + xmax, 0}));
        int v = !(t0->v && t1->v);
        g[cnt++] = {x, v};
        x = xmax;
        if (next(t0) != f.end())
            x = min(x, next(t0)->l);
        if (next(t1) != f.end())
            x = min(x, next(t1)->l - xmax);
    }

    f.clear();
    for (int i = 0; i < cnt; i++) {
        f.insert(g[i]);
    }
}

int hcnt;
lp h[5 * NMAX];

void add(i64 l1, i64 r1, i64 l2, i64 r2) {
    i64 l = max(l1, l2);
    i64 r = min(r1, r2);
    if (r <= l)
        return;
    h[hcnt++] = {l, +1};
    h[hcnt++] = {r, -1};
}

void scan(i64 l, i64 r, i64 xmax) {
    assert(l < r);
    auto it = f.lower_bound(lp{l, 0});
    if (it == f.end()) {
        int old_v = f.rbegin()->v;
        f.insert({l, 0});
        if (r < xmax)
            f.insert({r, old_v});
        return;
    }

    it->l = l;
    int old_v = it->v;
    it->v = 0;
    it++;
    while (it != f.end() && it->l < r) {
        old_v = it->v;
        it = f.erase(it);
    }
    if (it == f.end() || r < it->l) {
        if (r < xmax)
            f.insert({r, old_v});
    }
}

void update(int k) {
    hcnt = 0;
    i64 xmax = 1ll << k;
    for (int i = 1; i <= n; i++) {
        i64 vl = L[i] / xmax;
        i64 vr = R[i] / xmax;
        i64 xl = xmax - L[i] % xmax;
        i64 xr = xmax - R[i] % xmax;
        if (vl == vr)
            add(0, xl, 0, xr);
        if (vl + 1 == vr)
            add(xl, xmax, 0, xr);
        if (vl + 1 == vr + 1)
            add(xl, xmax, xr, xmax);
    }

    sort(h, h + hcnt, [](const lp &a, const lp &b) {
        return a.l < b.l || (a.l == b.l && a.v < b.v);
    });

    int s = 0;
    for (int i = 0; i < hcnt; i++) {
        s += h[i].v;
        if (s == n) {
            i64 l = h[i].l;
            i64 r = xmax;
            if (i + 1 < hcnt)
                r = h[i + 1].l;
                // r = min(r, h[i + 1].l);
            scan(l, r, xmax);
        }
    }
}

void merge() {
    for (auto it = f.begin(); it != f.end(); it++) {
        while (next(it) != f.end() && it->v == next(it)->v) {
            f.erase(next(it));
        }
    }
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", L + i, R + i);
        R[i]++;
    }

    f.clear();
    f.insert({0, 0});
    for (int k = KMAX; k >= 0; k--) {
        // f.insert({INF, 0});

        dp(k);
        // printf("dp(%d):", k);
        // for (auto &e : f) {
        //     printf(" [%lld,%d]", e.l, e.v);
        // }
        // puts("");

        update(k);
        // printf("update(%d):", k);
        // for (auto &e : f) {
        //     printf(" [%lld,%d]", e.l, e.v);
        // }
        // puts("");

        // TODO: This triggers a BUG
        // merge();

        // printf("merge(%d):", k);
        // for (auto &e : f) {
        //     printf(" [%lld,%d]", e.l, e.v);
        // }
        // puts("\n");

        // f.erase(lp{INF, 0});
    }

    assert(f.size() == 1);
    assert(f.begin()->l == 0);
    puts(f.begin()->v ? "Takahashi" : "Aoki");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
