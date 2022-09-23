#pragma optimize("O3")
#pragma option("unroll-loops")

#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int BUFSIZE = 65536;

char _buf[BUFSIZE];
size_t _pos = BUFSIZE;

char _getc() {
    if (_pos == BUFSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFSIZE, stdin);
    }
    return _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getc(); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        c = _getc();
    } while (isdigit(c));
}

constexpr int NMAX = 200000;
constexpr int INF = 1000000000;
constexpr i64 MOD = 998244353;

i64 inv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * inv(MOD % x) % MOD;
}

struct ran {
    int l;
    mutable int r;
    int j;

    bool operator<(const ran &z) const {
        return l < z.l;
    }
};

int n, q;
ran p[NMAX + 10];
i64 ans[NMAX + 10];
vector<ran> buc[NMAX + 10];

struct Node {
    int l, r;
    i64 s0, s1;
    i64 A, X, U;
    Node *lch, *rch;

    Node(int L, int R)
        : l(L), r(R), s0(0), s1(0), A(0), X(0), U(0), lch(NULL), rch(NULL) {
        if (l < r) {
            int mi = (l + r) / 2;
            lch = new Node(l, mi);
            rch = new Node(mi + 1, r);
        }
    }

    i64 real_s0() {
        return (s0 + X) % MOD;
    }

    i64 real_s1() {
        return (s0 * A + s1 + U) % MOD;
    }

    void recv(i64 B, i64 Y, i64 V) {
        i64 A0 = A + B;
        i64 X0 = X + Y;
        i64 U0 = U + V + B * X;
        A = A0 % MOD;
        X = X0 % MOD;
        U = U0 % MOD;
    }

    void commit() {
        if (A || X || U) {
            i64 t0 = real_s0();
            i64 t1 = real_s1();
            s0 = t0;
            s1 = t1;
            if (lch) {
                lch->recv(A, X, U);
                rch->recv(A, X, U);
            }
            A = X = U = 0;
        }
    }

    void fetch() {
        assert(lch);
        s0 = (lch->real_s0() + rch->real_s0()) % MOD;
        s1 = (lch->real_s1() + rch->real_s1()) % MOD;
    }

    void acc() {
        recv(1, 0, 0);
    }

    void modify(int x, i64 v) {
        if (l == x && r == x) {
            recv(0, v, 0);
        } else {
            commit();
            int mi = (l + r) / 2;
            if (x <= mi)
                lch->modify(x, v);
            else
                rch->modify(x, v);
            fetch();
        }
    }

    i64 query(int L, int R) {
        commit();
        if (L <= l && r <= R)
            return s1;
        else {
            int mi = (l + r) / 2;
            i64 rax = 0;
            if (L <= mi)
                rax += lch->query(L, R);
            if (R > mi)
                rax += rch->query(L, R);
            rax %= MOD;
            return rax;
        }
    }
};

Node *ts, *tc;
set<ran> C;

void update(i64 l, i64 x, i64 y) {
    ts->modify(x, MOD - l * x % MOD);
    ts->modify(y, l * y % MOD);
    if (x > 0)
        tc->modify(x, MOD - l);
    tc->modify(y, l);
}

void cover(int i, int l, int r) {
    int ln = l, rn = r;
    while (l <= r) {
        auto it = C.upper_bound({l, l, 0});
        assert(it != C.end());
        assert(it != C.begin());
        it--;

        int L = it->l, R = it->r;
        int j = it->j;
        assert(L <= l);
        assert(l <= R);

        if (L < l)
            it->r = l - 1;
        else
            C.erase(it);

        int r0 = min(R, r);
        // C.insert({l, r0, i});
        // printf("[%d, %d]: %d → %d\n", l, r0, j, i);
        update(r0 - l + 1, j, i);

        if (r < R)
            C.insert({r + 1, R, j});

        l = r0 + 1;
    }

    C.insert({ln, rn, i});
}

int main() {
    // scanf("%d%d", &n, &q);
    read(n); read(q);
    for (int i = 1; i <= n; i++) {
        // scanf("%d%d", &p[i].l, &p[i].r);
        read(p[i].l); read(p[i].r);
        p[i].r--;
    }
    for (int i = 1; i <= q; i++) {
        int l, r;
        // scanf("%d%d", &l, &r);
        read(l); read(r);
        buc[r].push_back({l, r, i});
    }

    C.insert({0, INF - 1});
    C.insert({INF, INF});

    ts = new Node(0, n);
    tc = new Node(0, n);
    for (int i = 1; i <= n; i++) {
        cover(i, p[i].l, p[i].r);
        ts->acc();
        tc->acc();

        for (auto &a : buc[i]) {
            i64 L = a.r - a.l + 1;
            i64 m = L * (L + 1) / 2 % MOD;
            i64 s = ts->query(a.l, a.r);
            i64 c = tc->query(a.l, a.r);
            // printf("[%d, %d] ⇒ %lld\n", a.l, a.r, s);
            ans[a.j] = (s - c * (a.l - 1)) % MOD * inv(m) % MOD;
        }
    }

    for (int i = 1; i <= q; i++) {
        if (ans[i] < 0)
            ans[i] += MOD;
        printf("%lld\n", ans[i]);
    }

    return 0;
}