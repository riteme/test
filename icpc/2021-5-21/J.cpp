#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

using d64 = double;

constexpr int NMAX = 2500;
constexpr d64 EPS = 1e-10;

bool eq(d64 x, d64 y) {
    return fabs(x - y) < EPS;
}

struct vec {
    vec() : x(0), y(0) {}
    vec(d64 _x, d64 _y) : x(_x), y(_y) {}

    d64 x, y;

    int idx() const {
        if (x >= 0 && y >= 0)
            return 1;
        if (x <= 0 && y >= 0)
            return 2;
        if (x <= 0 && y <= 0)
            return 3;
        return 4;
    }

    d64 len2() const {
        return x * x + y * y;
    }

    d64 len() const {
        return hypot(x, y);
    }

    vec unit() const {
        return (*this) / len();
    }

    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }

    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }

    vec operator*(d64 k) const {
        return vec(x * k, y * k);
    }

    vec operator/(d64 k) const {
        return vec(x / k, y / k);
    }

    d64 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    d64 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

struct cir {
    d64 r;
    vec C;
};

enum IStatus {
    ISEP, IOUTER, ISECT, IINNER, ICONTAIN,
};

struct IResult {
    vec u, v;
    IStatus stat;
};

IResult isect(const cir &a, const cir &b) {
    vec p = b.C - a.C;
    d64 d = p.len(), d0 = max(a.r, b.r) - min(a.r, b.r);

    IStatus stat;
    if (a.r + b.r <= d - EPS) stat = ISEP;
    else if (eq(a.r + b.r, d)) stat = IOUTER;
    else if (d - EPS >= d0) stat = ISECT;
    else if (eq(d, d0)) stat = IINNER;
    else stat = ICONTAIN;

    d64
    R2 = a.r * a.r,
    t = (R2 - b.r * b.r) / d,
    L = (d + t) * 0.5,
    H = sqrt(max(0.0, R2 - L * L));
    p = p / d;
    vec v = vec(p.y, -p.x) * H;
    vec O = a.C + p * L;
    return {O + v, O - v, stat};
}

struct Node {
    int l, r, s;
    d64 w;
    Node *lch, *rch;

    Node(int L, int R)
        : l(L), r(R), s(0), w(0.0), lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
        }
    }

    void commit() {
        if (s) {
            w = -w;
            if (lch) {
                lch->s ^= s;
                rch->s ^= s;
            }
            s = 0;
        }
    }

    d64 realw() {
        return s ? -w : w;
    }

    void fetch() {
        assert(lch);
        w = lch->realw() + rch->realw();
    }

    void reset() {
        s = 0;
        w = 0;
        if (lch) {
            lch->reset();
            rch->reset();
        }
    }

    void modify(int x, d64 v) {
        commit();
        if (l == x && r == x)
            w += v;
        else {
            int m = (l + r) / 2;
            if (x <= m)
                lch->modify(x, v);
            else
                rch->modify(x, v);
            fetch();
        }
    }

    void negate(int L, int R) {
        if (L <= l && r <= R)
            s ^= 1;
        else {
            commit();
            int m = (l + r) / 2;
            if (L <= m)
                lch->negate(L, R);
            if (R > m)
                rch->negate(L, R);
            fetch();
        }
    }
};

struct endp {
    vec p;
    int b, s;
};

int n;
cir C[NMAX + 10];
d64 ans1[NMAX + 10], ans2[NMAX + 10];
int cnt;
endp e[NMAX + 10];
int lp[NMAX + 10], rp[NMAX + 10];
// int tm[NMAX + 10];
// vector<int> buc[NMAX + 10];
Node *tr1, *tr2;

d64 p2arc(d64 r, const vec &u, const vec &v) {
    if (eq(u.x, v.x) && eq(u.y, v.y))
        return 0;
    d64 d = u * v;
    d64 cr = u % v;
    d64 t = acos(max(-1.0, min(1.0, d / r / r)));
    return cr > 0 ? t : 2 * M_PI - t;
}

vec O(-3e4, -3e4);

d64 eval_poly(const cir &c, const vec &u, const vec &v) {
    return (u + c.C - O) % (v + c.C - O) / 2;
}

d64 eval_fan(const cir &c, const vec &u, const vec &v) {
    d64 a = p2arc(c.r, u, v);
    d64 s = a * c.r * c.r / 2;
    d64 st = fabs(u % v) / 2;
    if (a > M_PI)
        s += st;
    else
        s -= st;
    return s;
}

int wrap(int i) {
    while (i < 1)
        i += cnt;
    while (i > cnt)
        i -= cnt;
    return i;
}

void solve(int a) {
    cnt = 0;
    for (int b = 1; b <= n; b++) if (b != a) {
        auto s = isect(C[a], C[b]);
        if (s.stat == ISECT) {
            e[++cnt] = {s.u - C[a].C, b, +1};
            e[++cnt] = {s.v - C[a].C, b, -1};
        }
    }

    sort(e + 1, e + cnt + 1, [](const endp &u, const endp &v) {
        if (u.p.idx() != v.p.idx())
            return u.p.idx() < v.p.idx();
        return u.p % v.p > 0;
    });

    memset(lp, 0, sizeof(lp));
    memset(rp, 0, sizeof(rp));
    for (int i = 1; i <= cnt; i++) {
        if (e[i].s == +1)
            lp[e[i].b] = i;
        else
            rp[e[i].b] = wrap(i - 1);
    }

    // memset(tm, 0, sizeof(tm));
    // set<int> seq;
    // for (int i = 1; i <= n; i++) {
    //     seq.insert(i);
    // }

    // for (int b = 1; b <= n; b++) if (b != a) {
    //     if (lp[b] == 0)
    //         continue;
    //     assert(rp[b]);

    //     auto l = seq.lower_bound(lp[b]);
    //     auto r = seq.lower_bound(rp[b]);
    //     if (lp[b] > rp[b]) {
    //         while (l != seq.end()) {
    //             tm[*l] = b;
    //             l = seq.erase(l);
    //         }
    //         l = seq.begin();
    //     }

    //     while (l != r) {
    //         tm[*l] = b;
    //         l = seq.erase(l);
    //     }
    // }

    // for (int i = 1; i <= cnt; i++) {
    //     buc[i].clear();
    // }
    // for (int i = 1; i <= cnt; i++) {
    //     buc[tm[i]].push_back(i);
    // }

    tr1->reset();
    tr2->reset();
    for (int i = 1; i <= cnt; i++) {
        tr1->modify(i, eval_poly(C[a], e[i].p, e[i % cnt + 1].p));
        tr2->modify(i, eval_fan(C[a], e[i].p, e[i % cnt + 1].p));
    }

    for (int b = 1; b <= n; b++) {
        // for (int i : buc[b]) {
        //     tr->modify(i, eval(C[a], e[i].p, e[i % cnt + 1].p));
        // }

        if (lp[b]) {
            assert(rp[b]);

            int l = lp[b], r = rp[b];
            if (l > r) {
                tr1->negate(l, cnt);
                tr2->negate(l, cnt);
                l = 1;
            }
            if (l <= r) {
                tr1->negate(l, r);
                tr2->negate(l, r);
            }
        }

        if (b >= a) {
            ans1[b] += tr1->realw();
            ans2[b] += tr2->realw();
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &C[i].C.x, &C[i].C.y, &C[i].r);
    }

    tr1 = new Node(1, 3 * n);
    tr2 = new Node(1, 3 * n);
    for (int i = 1; i <= n; i++) {
        solve(i);
    }

    for (int i = 1; i <= n; i++) {
        printf("%.12lf\n", ans1[i] + ans2[i]);
    }

    return 0;
}