#pragma GCC optimize(3)

#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define INF 2000000000

struct Circle {
    Circle() {}
    Circle(int i, i64 _x, i64 _y)
        : id(i), x(_x), y(_y), r(_y), lt(_x - _y), rt(_x + _y) {}

    int id;
    i64 x, y, r, lt, rt;

    bool operator<(const Circle &z) const {
        return rt > z.rt ||
              (rt == z.rt && lt < z.lt);
    }
};

struct Node {
    Node(i64 _l, i64 _r) : l(_l), r(_r), lch(NULL), rch(NULL) {}

    i64 l, r;
    set<Circle> cirs;
    Node *lch, *rch;
};

static int q;
static Node *seg;

void insert(Node *p, const Circle &c) {
    p->cirs.insert(c);
    if (p->l == p->r) return;

    i64 m = (p->l + p->r) >> 1;
    if (!p->lch) {
        p->lch = new Node(p->l, m);
        p->rch = new Node(m + 1, p->r);
    }
    if (c.lt <= m) insert(p->lch, c);
    else insert(p->rch, c);
}

void remove(Node *p, const Circle &c) {
    p->cirs.erase(c);
    if (p->l == p->r) return;
    i64 m = (p->l + p->r) >> 1;
    if (c.lt <= m) remove(p->lch, c);
    else remove(p->rch, c);
}

inline i64 p2(i64 x) {
    return x * x;
}

inline bool test(const Circle &c, i64 x, i64 y) {
    return p2(x - c.x) + p2(y - c.y) < p2(c.r);
}

#define LOOP(cirs) \
    for (auto &c : cirs) { \
        if (c.rt <= x) break; \
        if (test(c, x, y)) { \
            ret = c; \
            return true; \
        } \
    }

static Circle ret;
bool query(Node *p, i64 x, i64 y) {
    if (!p) return false;
    if (p->l == p->r) {
        LOOP(p->cirs);
        return false;
    }

    i64 m = (p->l + p->r) >> 1;
    if (x <= m) return query(p->lch, x, y);
    if (p->lch) {
        LOOP(p->lch->cirs);
    }
    return query(p->rch, x, y);
}

#undef LOOP

int main() {
    scanf("%d", &q);
    seg = new Node(-INF, INF);
    for (int t = 1; t <= q; t++) {
        int p;
        i64 x, y;
        scanf("%d%lld%lld", &p, &x, &y);

        if (p == 1)
            insert(seg, Circle(t, x, y));
        else {
            if (!query(seg, x, y))
                puts("-1");
            else {
                printf("%d\n", ret.id);
                remove(seg, ret);
            }
        }
    }

    return 0;
}
