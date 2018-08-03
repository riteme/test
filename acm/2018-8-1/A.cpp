#pragma GCC optimize(3)

#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define INF 2000000000

static unordered_map<int, int> id;

struct Circle {
    Circle() {}
    Circle(int _i, int _x, int _y)
        : i(_i), x(_x), y(_y), r(_y), lt(id[_x - _y]), rt(_x + _y) {}

    int i, x, y, r, lt, rt;

    bool operator<(const Circle &z) const {
        return rt > z.rt ||
              (rt == z.rt && lt < z.lt);
    }
};

struct Node {
    Node(int _l, int _r) : l(_l), r(_r), lch(NULL), rch(NULL) {}

    int l, r;
    set<Circle> cirs;
    Node *lch, *rch;
};

static int q;
static Node *seg;

void insert(Node *p, const Circle &c) {
    p->cirs.insert(c);
    if (p->l == p->r) return;

    int m = (p->l + p->r) >> 1;
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
    int m = (p->l + p->r) >> 1;
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
        if (c.rt <= rx) break; \
        if (test(c, rx, y)) { \
            ret = c; \
            return true; \
        } \
    }

static Circle ret;
bool query(Node *p, int x, int rx, int y) {
    if (!p) return false;
    if (p->l == p->r) {
        LOOP(p->cirs);
        return false;
    }

    int m = (p->l + p->r) >> 1;
    if (x <= m) return query(p->lch, x, rx, y);
    if (p->lch) {
        LOOP(p->lch->cirs);
    }
    return query(p->rch, x, rx, y);
}

#undef LOOP

static int type[NMAX + 10], X[NMAX + 10], Y[NMAX + 10];
static int seq[NMAX * 2 + 10], m;

int main() {
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d%d", type + i, X + i, Y + i);
        if (type[i] == 1) seq[++m] = X[i] - Y[i];
        else seq[++m] = X[i];
    }
    sort(seq + 1, seq + m + 1);
    m = unique(seq + 1, seq + m + 1) - seq;
    for (int i = 1; i <= m; i++)
        id[seq[i]] = i;

    seg = new Node(1, m);
    for (int i = 1; i <= q; i++) {
        if (type[i] == 1)
            insert(seg, Circle(i, X[i], Y[i]));
        else {
            if (!query(seg, id[X[i]], X[i], Y[i]))
                puts("-1");
            else {
                printf("%d\n", ret.i);
                remove(seg, ret);
            }
        }
    }

    return 0;
}
