#include <cstdio>
#include <cassert>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int INF = 0x3f3f3f3f;
constexpr int NMAX = 200000;

int n;
int a[NMAX + 10], b[NMAX + 10], rev[NMAX + 10], rk[NMAX + 10];

struct Node {
    Node(int _l, int _r) : l(_l), r(_r) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
            pull();
        } else {
            mina = a[l];
            minp = l;
            s = a[l] - b[l];
        }
    }

    void push() {
        if (smark || mamark) {
            s += cnt * smark;
            mina += mamark;
            if (lch) {
                lch->smark += smark;
                lch->mamark += mamark;
            }
            if (rch) {
                rch->smark += smark;
                rch->mamark += mamark;
            }
            smark = 0;
            mamark = 0;
        }
    }

    void pull() {
        mina = min(lch->mareal(), rch->mareal());
        if (mina == lch->mareal())
            minp = lch->minp;
        else
            minp = rch->minp;
        s = lch->sreal() + rch->sreal();
        cnt = lch->cnt + rch->cnt;
    }

    i64 sreal() {
        return s + cnt * smark;
    }

    int mareal() {
        return mina + mamark;
    }

    void remove(int x) {
        push();
        if (l < r) {
            int m = (l + r) / 2;
            if (x <= m)
                lch->remove(x);
            else
                rch->remove(x);
            pull();
        } else {
            cnt = 0;
            s = 0;
            smark = 0;
            mina = INF;
        }
    }

    struct Min {
        int v, p;
    };

    Min find_min(int R) {
        push();
        if (l < r) {
            int m = (l + r) / 2;
            if (R <= m)
                return lch->find_min(R);

            Min mi = rch->find_min(R);
            if (mi.v < lch->mareal())
                return mi;
            else
                return {lch->mareal(), lch->minp};
        } else {
            return {mina, minp};
        }
    }

    int find_below(int L, int v) {
        push();
        if (l < r) {
            int m = (l + r) / 2;
            if (L <= m && lch->mareal() < v)
                return lch->find_below(L, v);
            return rch->find_below(L, v);
        } else {
            return mina < v ? l : n + 1;
        }
    }

    void add_s(int L, int R, i64 v) {
        if (L <= l && r <= R) {
            smark += v;
        } else {
            push();
            int m = (l + r) / 2;
            if (L <= m)
                lch->add_s(L, R, v);
            if (R > m)
                rch->add_s(L, R, v);
            pull();
        }
    }

    void add_ma(int L, int R, int v) {
        if (L <= l && r <= R) {
            mamark += v;
        } else {
            push();
            int m = (l + r) / 2;
            if (L <= m)
                lch->add_ma(L, R, v);
            if (R > m)
                rch->add_ma(L, R, v);
            pull();
        }
    }

    ~Node() {
        if (lch)
            delete lch;
        if (rch)
            delete rch;
    }

    Node *lch = NULL, *rch = NULL;
    int l, r;
    int mina = INF, minp, mamark = 0;
    int cnt = 1;
    i64 s = 0, smark = 0;
};

i64 ans[NMAX + 10];

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        rev[i] = i;
    }

    sort(rev + 1, rev + n + 1, [](int i, int j) {
        return a[i] < a[j];
    });
    for (int i = 1; i <= n; i++) {
        rk[rev[i]] = i;
    }

    sort(a + 1, a + n + 1);

    b[1] = 1;
    for (int i = 2; i <= n; i++) {
        b[i] = b[i - 1];
        if (b[i] + 1 <= a[i])
            b[i]++;
    }

    a[0] = 0;
    b[0] = 0;
    rk[0] = 0;

    for (int i = 1; i <= n; i++) {
        a[i] -= i;
        b[i] -= i;
    }

    Node *t = new Node(0, n);
    for (int _j = n; _j >= 1; _j--) {
        ans[_j] = t->sreal();

        int j = rk[_j];
        auto mi = t->find_min(j);
        int i = mi.p;
        int vi = mi.v;
        int k = t->find_below(i, mi.v) - 1;
        // printf("%d, i=%d, j=%d, k=%d\n", _j, i, j, k);

        mi = t->find_min(j - 1);
        // printf("vi=%d, mi.v=%d\n", vi, mi.v);
        assert(mi.v >= vi);
        assert(mi.v <= vi + 1);
        if (mi.v == vi)
            t->add_s(j, k, +1);
        t->add_ma(j, n, +1);
        t->remove(j);
    }

    for (int i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }
    puts("");

    delete t;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
