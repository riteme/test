#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

struct rect {
    i64 xmi, ymi, xmx, ymx;
};

#define YMIN +1
#define YMAX -1

struct ref {
    int l, r;
    int y, type;

    bool operator<(const ref &z) const {
        return y < z.y || (y == z.y && type < z.type);
    }
};

int n;
i64 K;
rect seg[NMAX + 10];
ref seq[2 * NMAX + 10];
rect region;

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        auto &s = seg[i];
        scanf("%lld%lld%lld%lld", &s.xmi, &s.ymi, &s.xmx, &s.ymx);
        if (s.xmi == s.xmx && s.ymi > s.ymx)
            swap(s.ymi, s.ymx);
        if (s.ymi == s.ymx && s.xmi > s.xmx)
            swap(s.xmi, s.xmx);
    }
    scanf("%lld%lld%lld%lld%lld", &K, &region.xmi, &region.ymi, &region.xmx, &region.ymx);
}

struct Node {
    Node(int _l, int _r) :
        l(_l), r(_r),
        mi(0), cnt(_r - _l + 1), mark(0),
        lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
        }
    }

    int l, r, mi, cnt, mark;
    Node *lch, *rch;

    int gmi() {
        return mi + mark;
    }

    void push() {
        if (mark) {
            mi += mark;
            if (lch) {
                lch->mark += mark;
                rch->mark += mark;
            }
            mark = 0;
        }
    }

    void update() {
        mi = min(lch->gmi(), rch->gmi());
        cnt =
            (lch->gmi() == mi ? lch->cnt : 0) +
            (rch->gmi() == mi ? rch->cnt : 0);
    }

    void modify(int L, int R, int v) {
        if (L <= l && r <= R)
            mark += v;
        else {
            push();
            int m = (l + r) / 2;
            if (L <= m) lch->modify(L, R, v);
            if (R > m) rch->modify(L, R, v);
            update();
        }
    }

    void clear() {
        mi = 0;
        cnt = r - l + 1;
        mark = 0;
        if (lch) {
            lch->clear();
            rch->clear();
        }
    }
};

Node *tr;
i64 solve(i64 w) {
    int m = 0;
    for (int i = 1; i <= n; i++) {
        auto &s = seg[i];
        int xmin = max(region.xmi, s.xmi - w);
        int ymin = max(region.ymi, s.ymi - w);
        int xmax = min(region.xmx, s.xmx + w);
        int ymax = min(region.ymx, s.ymx + w);
        seq[m++] = {xmin, xmax, ymin, YMIN};
        seq[m++] = {xmin, xmax, ymax, YMAX};
    }
    sort(seq, seq + m);

    tr->clear();
    i64 sum = 0, last = 0;
    for (int i = 0; i < m; i++) {
        ref &r = seq[i];
        i64 len = region.xmx - region.xmi;
        if (tr->gmi() == 0)
            len -= tr->cnt;
        sum += (r.y - last) * len;
        last = r.y;
        if (r.l < r.r)
            tr->modify(r.l + 1, r.r, r.type);
    }

    return sum;
}

int main() {
    initialize();
    tr = new Node(region.xmi + 1, region.xmx);

    i64 l = 0, r = max(
        region.xmx - region.xmi,
        region.ymx - region.ymi
    );
    i64 all = i64(region.xmx - region.xmi) * (region.ymx - region.ymi);
    while (l < r) {
        i64 m = (l + r) / 2;
        i64 area = solve(m);
        if (area * 100 >= all * K) r = m;
        else l = m + 1;
    }

    printf("%lld\n", l);
    return 0;
}