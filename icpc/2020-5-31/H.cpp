#include <cstdio>
#include <cstring>

#include <tuple>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

int n, q;
int h[NMAX + 10];

struct Node {
    int l, r;
    i64 lv, rv, ans, tmp;
    Node *lch, *rch;

    Node(int _l, int _r)
    : l(_l), r(_r), lv(0), rv(0), ans(0), tmp(0), lch(nullptr), rch(nullptr) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
            update();
        } else
            lv = rv = ans = h[l];
    }

    ~Node() {
        if (lch)
            delete lch;
        if (rch)
            delete rch;
    }

    i64 real_lv() const {
        return lv + tmp;
    }

    i64 real_rv() const {
        return rv + tmp;
    }

    i64 real_ans() const {
        return ans + tmp;
    }

    void push() {
        if (tmp) {
            lv = real_lv();
            rv = real_rv();
            ans = real_ans();
            if (lch)
                lch->tmp += tmp;
            if (rch)
                rch->tmp += tmp;
            tmp = 0;
        }
    }

    void update() {
        lv = lch->real_lv();
        rv = rch->real_rv();
        ans = lch->real_ans() + rch->real_ans() - min(lch->real_rv(), rch->real_lv());
    }

    void modify(int L, int R, int v) {
        if (L <= l && r <= R)
            tmp += v;
        else {
            push();
            int m = (l + r) / 2;
            if (L <= m)
                lch->modify(L, R, v);
            if (R > m)
                rch->modify(L, R, v);
            update();
        }
    }

    auto query(int L, int R) -> tuple<i64, i64, i64> {
        if (L <= l && r <= R)
            return make_tuple(real_lv(), real_rv(), real_ans());

        push();
        int m = (l + r) / 2;
        if (R <= m)
            return lch->query(L, R);
        if (L > m)
            return rch->query(L, R);

        auto lret = lch->query(L, R);
        auto rret = rch->query(L, R);
        return make_tuple(
            get<0>(lret), get<1>(rret),
            get<2>(lret) + get<2>(rret) - min(
                get<1>(lret), get<0>(rret)
            )
        );
    }
};

void _main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", h + i);
    }

    auto tr = new Node(1, n);
    while (q--) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);

        if (op == 1) {
            int v;
            scanf("%d", &v);
            tr->modify(l, r, v);
        } else {
            i64 _, ans;
            tie(_, _, ans) = tr->query(l, r);
            printf("%lld\n", ans);
        }
    }

    delete tr;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}