#include <cstdio>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define INF 0x3f3f3f3f

#define USED __attribute__((used))

struct Segment {
    mutable int l, r, t;

    bool operator<(const Segment &z) const {
        if (!l || !z.l) return t < z.t;
        return r < z.l;
    }
};

struct Node {
    Node(int _l, int _r) : l(_l), r(_r), sum(0), cov(0), lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) >> 1;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
        }
    }

    int l, r;
    i64 sum, cov;
    Node *lch, *rch;

    i64 rsum() const {
        return cov ? (r - l + 1) * cov : sum;
    }

    void push() {
        if (cov) {
            sum = (r - l + 1) * cov;
            lch->cov = cov;
            rch->cov = cov;
            cov = 0;
        }
    }

    void update() {
        sum = lch->rsum() + rch->rsum();
    }

    void cover(int L, int R, i64 v) {
        if (L <= l && r <= R) cov = v;
        else {
            int m = (l + r) >> 1;
            push();
            if (L <= m) lch->cover(L, R, v);
            if (R > m) rch->cover(L, R, v);
            update();
        }
    }

    void cover(const Segment &s) {
        cover(s.l, s.r, s.t);
    }

    i64 query(int L, int R) {
        if (L <= l && r <= R) return rsum();
        push();
        int m = (l + r) >> 1;
        i64 rax = 0;
        if (L <= m) rax += lch->query(L, R);
        if (R > m) rax += rch->query(L, R);
        update();
        return rax;
    }
};

static int n, m, q;
static struct Item {
    int val, pos;

    bool operator<(const Item &z) const {
        return val < z.val;
    }
} a[NMAX + 10];
static struct Query {
    int l, r, k, i;
    i64 ans = 0;

    bool operator<(const Query &z) const {
        return k < z.k;
    }
} op[NMAX + 10], *ref[NMAX + 10];
static Node *tr;
static set<Segment> rsp;

int rmin(int l) {
    auto it = rsp.lower_bound({l, l, 0});
    return it->t;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &q);
    tr = new Node(1, n);
    for (int i = 1; i <= n; i++) {
        a[i].pos = i;
        scanf("%d", &a[i].val);
    }
    for (int i = 1; i <= q; i++) {
        op[i].i = i;
        scanf("%d%d%d", &op[i].l, &op[i].r, &op[i].k);
    }
    sort(a + 1, a + n + 1);
    sort(op + 1, op + q + 1);
    for (int i = 1; i <= q; i++)
        ref[op[i].i] = op + i;
    rsp.insert({1, n, INF});
    tr->cover(1, n, INF);
}

USED void print_rsp(int k) {
    fprintf(stderr, "K = %d\n", k);
    for (auto &s : rsp)
        fprintf(stderr, s.t > n ? "[%d, %d][INF] " : "[%d, %d][%d] ", s.l, s.r, s.t);
    fprintf(stderr, "\n");
}

int main() {
    initialize();

    for (int k = 1, i = 1, j = 1; k <= m; k++) {
        for (auto it = rsp.begin(), lt = rsp.end(); it != rsp.end(); lt = it++) {
            it->t = it->t < n ? rmin(it->t + 1) : INF;
            if (lt != rsp.end() && lt->t == it->t) {
                it->l = lt->l;
                rsp.erase(lt);
            }
            tr->cover(*it);
        }

        for ( ; i <= n && a[i].val == k; i++) {
            int p = a[i].pos;
            auto it = rsp.lower_bound({p, p, 0});
            Segment seg = {it->l, p, p};
            if (it->r > p) it->l = p + 1;
            else rsp.erase(it);
            it = rsp.insert(seg).first;
            for (auto ut = prev(it); it != rsp.begin(); ut = prev(it)) {
                if (ut->t < p) break;
                it->l = ut->l;
                rsp.erase(ut);
            }
            tr->cover(*it);
        }

        //print_rsp(k);
        //fprintf(stderr, "%lu\n", rsp.size());
        for ( ; j <= q && op[j].k == k; j++) {
            int l = op[j].l, r = op[j].r, r0 = op[j].r;
            auto it = rsp.lower_bound({0, 0, r0 + 1});
            if (it != rsp.end() && it->t > r0)
                r = min(r, it->l - 1);
            if (l <= r) {
                i64 sum = tr->query(l, r);
                //fprintf(stderr, "(%d, %d) → %lld\n", l, r, sum);
                op[j].ans = (r - l + 1LL) * (r0 + 1) - sum;
            }
        }
    }

    for (int i = 1; i <= q; i++)
        printf("%lld\n", ref[i]->ans);

    return 0;
}
