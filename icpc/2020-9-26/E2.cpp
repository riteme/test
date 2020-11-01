#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cctype>

#include <algorithm>

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE;
char _buf[BUFFERSIZE];

char _getc() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _buf[_pos++];
}

template<typename T>
void read(T &x) {
    x = 0;
    T f = 1;
    char c;
    do {
        c = _getc();
        if (c == '-')
            f = -1;
    } while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
    x *= f;
}

using i64 = long long;

constexpr i64 INF = 1000000000;

using namespace std;

struct vec {
    vec() : x(0), y(0) {}
    vec(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    int idx() const {
        if (x >= 0 && y >= 0)
            return 1;
        if (x <= 0 && y >= 0)
            return 2;
        if (x <= 0 && y <= 0)
            return 3;
        return 4;
    }

    i64 len2() const {
        return x * x + y * y;
    }

    vec operator-() const {
        return vec(-x, -y);
    }
    vec operator+(const vec &z) const {
        return vec(x + z.x, y + z.y);
    }
    vec operator-(const vec &z) const {
        return vec(x - z.x, y - z.y);
    }
    i64 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }
    i64 operator%(const vec &z) const {
        return x * z.y - y * z.x;
    }
};

#define NMAX 40000
#define MMAX 5

struct Node {
    Node(Node *x)
        : sum(x->sum), lch(x->lch), rch(x->rch) {}
    Node(int l, int r)
        : sum(0), lch(NULL), rch(NULL) {
        if (l < r) {
            int mi = (l + r) / 2;
            lch = new Node(l, mi);
            rch = new Node(mi + 1, r);
        }
    }

    int sum;
    Node *lch, *rch;
};

Node *modify(Node *x, int l, int r, int p, int v) {
    x = new Node(x);
    x->sum += v;
    if (l < r) {
        int m = (l + r) / 2;
        if (p <= m)
            x->lch = modify(x->lch, l, m, p, v);
        else
            x->rch = modify(x->rch, m + 1, r, p, v);
    }
    return x;
}

int query(Node *x, int l, int r, int L, int R) {
    if (R < l || r < L)
        return 0;
    if (L <= l && r <= R)
        return x->sum;

    int rax = 0;
    int m = (l + r) / 2;
    if (L <= m)
        rax += query(x->lch, l, m, L, R);
    if (R > m)
        rax += query(x->rch, m + 1, r, L, R);
    return rax;
}

int n, m, q, f[2048];
int cnt, ys[NMAX + 10];
int idx[1000010];
vec P[NMAX + 10]/*, Q[NMAX + 10]*/;
vec L[MMAX + 10], R[MMAX + 10];

int ps[2 * MMAX + 1][NMAX + 10];
Node *base;
Node *tr0[MMAX * 2 + 1][NMAX + 10], *tr1[MMAX * 2 + 1][NMAX + 10];

bool iup(const vec &o, const vec &u) {
    return o.y < u.y || (o.y == u.y && o.x <= u.x);
}

vec dir(const vec &o, vec u) {
    return iup(o, u) ? u - o : o - u;
}

int zquery(int k, int i, const vec &o, const vec &u, bool f, int y) {
    bool b = ((u - o) % (P[ps[k][i]] - o) == 0) && !f;
    return query(b ? tr0[k][i] : tr1[k][i], 1, cnt, -INF, y);
}

// left: i, right: m + i
void process(int k, vec O) {
    for (int i = 1; i <= n; i++) {
        ps[k][i] = i;
    }
    sort(ps[k] + 1, ps[k] + n + 1, [O](int i, int j) {
        vec u = dir(O, P[i]);
        vec v = dir(O, P[j]);
        i64 c = u % v;
        return c > 0/* || (c == 1 && u.len2() < v.len2())*/;
    });

    Node *t = base;
    for (int i = 1; i <= n; i++) {
        if (!iup(O, P[i]))
            t = modify(t, 1, cnt, idx[P[i].y], +1);
    }
    tr0[k][0] = base;
    tr1[k][0] = t;

    for (int i = 1; i <= n; i++) {
        if (iup(O, P[ps[k][i]])) {
            tr0[k][i] = t;
            t = modify(t, 1, cnt, idx[P[ps[k][i]].y], +1);
            tr1[k][i] = t;
        } else {
            tr0[k][i] = t;
            t = modify(t, 1, cnt, idx[P[ps[k][i]].y], -1);
            tr1[k][i] = t;
        }
    }
}

int locate1(int k, const vec &o, vec u) {
    u = dir(o, u);
    int l = 1, r = n + 1;
    while (l < r) {
        int mi = (l + r) / 2;
        vec v = dir(o, P[ps[k][mi]]);
        if (u % v > 0)
            r = mi;
        else
            l = mi + 1;
    }
    return l - 1;
}

int locate0(int k, const vec &o, vec u) {
    u = dir(o, u);
    int l = 0, r = n;
    while (l < r) {
        int mi = (l + r) / 2 + 1;
        vec v = dir(o, P[ps[k][mi]]);
        if (u % v >= 0)
            r = mi - 1;
        else
            l = mi;
    }
    return l;
}

int eval(vec u, int S) {
    int lk, rk;
    vec lp = vec(-INF, 0), rp = vec(INF, 0);

    i64 maxy = 0;
    for (int i = 1; i <= m; i++)
    if ((S >> (i - 1)) & 1) {
        maxy = max(maxy, L[i].y);
        i64 cl = (L[i] - u) % (lp - u);
        i64 cr = (rp - u) % (R[i] - u);
        if (cl > 0 || (cl == 0 && L[i].y < lp.y)) {
            lk = i;
            lp = L[i];
        }
        if (cr > 0 || (cr == 0 && R[i].y < rp.y)) {
            rk = m + i;
            rp = R[i];
        }
    }

    if ((lp - u) % (rp - u) > 0)
        return 0;

    int yi = idx[maxy];
    int li = locate1(lk, lp, u);
    int ri = locate0(rk, rp, u);

    int rax = 0;
    rax += zquery(lk, li, lp, u, 1, INF);
    rax -= zquery(rk, ri, rp, u, 0, INF);
    rax -= zquery(lk, li, lp, u, 1, yi - 1);
    rax += zquery(rk, ri, rp, u, 0, yi - 1);

    return rax;
}

void _main() {
    base = new Node(1, cnt);
    for (int i = 1; i <= m; i++) {
        process(i, L[i]);
        process(m + i, R[i]);
    }

    while (q--) {
        vec u;
        //scanf("%lld%lld", &u.x, &u.y);
        read(u.x); read(u.y);

        int ans = n;
        for (int S = 1; S < (1 << m); S++) {
            ans += f[S] * eval(u, S);
        }

        printf("%d\n", ans);
    }
}

int main() {
    f[0] = 1;
    for (int S = 1; S < 2048; S++) {
        f[S] = f[S >> 1] * ((S & 1) ? -1 : 1);
    }

    //scanf("%d%d%d", &n, &m, &q);
    read(n); read(m); read(q);
    for (int i = 1; i <= n; i++) {
        //scanf("%lld%lld", &P[i].x, &P[i].y);
        read(P[i].x); read(P[i].y);
        ys[cnt++] = P[i].y;
    }

    for (int i = 1; i <= m; i++) {
        int l, r, y;
        //scanf("%d%d%d", &l, &r, &y);
        read(l); read(r); read(y);
        L[i] = vec(l, y);
        R[i] = vec(r, y);
        ys[cnt++] = y;
    }

    sort(ys, ys + cnt);
    cnt = unique(ys, ys + cnt) - ys;
    for (int i = 0; i < cnt; i++) {
        idx[ys[i]] = i + 1;
    }

    /*
    for (int i = 1; i <= q; i++) {
        scanf("%lld%lld", &Q[i].x, &Q[i].y);
    }
    */

    _main();

    return 0;
}
