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

struct mat3 {
    mat3() {
        memset(a, 0, sizeof(a));
    }

    i64 a[3][3];

    void set_ident() {
        for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            a[i][j] = i == j;
        }
    }

    bool is_ident() const {
        for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (a[i][j] != (i == j))
                return false;
        };
        return true;
    }

    void apply(i64 &s0, i64 &s1) {
        i64 t0 = (s0 * a[0][0] + s1 * a[0][1] + a[0][2]) % MOD;
        i64 t1 = (s0 * a[1][0] + s1 * a[1][1] + a[1][2]) % MOD;
        s0 = t0;
        s1 = t1;
    }

    const i64 *operator[](int i) const {
        return a[i];
    }

    mat3 &operator*=(const mat3 &b) {
        i64 c[3][3];
        memset(c, 0, sizeof(c));
        for (int k = 0; k < 3; k++)
        for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            c[i][j] += b[i][k] * a[k][j];
        };

        for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            c[i][j] %= MOD;
        };

        memcpy(a, c, sizeof(a));
        return *this;
    }
};

int n, q;
ran p[NMAX + 10];
i64 ans[NMAX + 10];
vector<ran> buc[NMAX + 10];

mat3 am;

struct Node {
    int l, r;
    i64 s0, s1;
    mat3 m;
    Node *lch, *rch;

    Node(int L, int R)
        : l(L), r(R), s0(0), s1(0), lch(NULL), rch(NULL) {
        m.set_ident();
        if (l < r) {
            int mi = (l + r) / 2;
            lch = new Node(l, mi);
            rch = new Node(mi + 1, r);
        }
    }

    i64 real_s0() {
        return (s0 * m.a[0][0] + s1 * m.a[0][1] + m.a[0][2]) % MOD;
    }

    i64 real_s1() {
        return (s0 * m.a[1][0] + s1 * m.a[1][1] + m.a[1][2]) % MOD;
    }

    void commit() {
        if (!m.is_ident()) {
            m.apply(s0, s1);
            if (lch) {
                lch->m *= m;
                rch->m *= m;
            }
            m.set_ident();
        }
    }

    void fetch() {
        assert(lch);
        s0 = lch->real_s0() + rch->real_s0();
        s1 = lch->real_s1() + rch->real_s1();
    }

    void mul(const mat3 &m1) {
        m *= m1;
    }

    void modify(int x, i64 v) {
        if (l == x && r == x) {
            am.a[0][2] = v;
            m *= am;
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

Node *tr;
set<ran> C;

void update(i64 l, i64 x, i64 y) {
    tr->modify(x, MOD - l * x % MOD);
    tr->modify(y, l * y % MOD);
}

void cover(int i, int l, int r) {
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
        C.insert({l, r0, i});
        // printf("[%d, %d]: %d → %d\n", l, r0, j, i);
        update(r0 - l + 1, j, i);

        if (r < R)
            C.insert({r + 1, R, j});

        l = r0 + 1;
    }
}

int main() {
    am.set_ident();

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

    mat3 cm;
    cm.set_ident();
    cm.a[1][0] = 1;

    C.insert({1, INF - 1});
    C.insert({INF, INF});

    tr = new Node(0, n);
    for (int i = 1; i <= n; i++) {
        cover(i, p[i].l, p[i].r);
        tr->mul(cm);

        for (auto &a : buc[i]) {
            i64 L = a.r - a.l + 1;
            i64 c = L * (L + 1) / 2;
            i64 s = tr->query(a.l, a.r);
            // printf("[%d, %d] ⇒ %lld\n", a.l, a.r, s);
            ans[a.j] = s * inv(c) % MOD;
        }
    }

    for (int i = 1; i <= q; i++) {
        if (ans[i] < 0)
            ans[i] += MOD;
        printf("%lld\n", ans[i]);
    }

    return 0;
}