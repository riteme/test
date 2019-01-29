#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 250000
#define BPC 32
#define MASK ((1LL << BPC) - 1)

typedef long long i64;
typedef unsigned int u32;

struct i8 {
    i8() = default;
    i8(i64 x) {
        fromll(x);
    }

    u32 a[4] = {0};

    void fromll(i64 x) {
        bool rev = false;
        if (x < 0) {
            x = -x;
            rev = true;
        }
        i8 c;
        c[0] = x & MASK;
        c[1] = x >> 32;
        if (rev) c = -c;
        memcpy(a, c.a, sizeof(a));
    }

    i64 toll() const {
        return a[0] + (i64(a[1]) << BPC);
    }

    int sgn() const {
        return a[3] >> (BPC - 1) ? -1 : 1;
    }

    void show() const {
        printf("[%u, %u, %u, %u]\n", a[3], a[2], a[1], a[0]);
    }

    u32 &operator[](int i) {
        return a[i];
    }

    u32 operator[](int i) const {
        return a[i];
    }

    i8 operator+(const i8 &b) const {
        i8 c;
        for (int i = 0; i < 4; i++) {
            i64 r = i64(a[i]) + b[i] + c[i];
            c[i] = r & MASK;
            if (i < 3) c[i + 1] = r >> BPC;
        }
        return c;
    }

    i8 operator*(int x) const {
        i8 c;
        for (int i = 0; i < 4; i++) {
            i64 r = i64(a[i]) * x + c[i];
            c[i] = r & MASK;
            if (i < 3) c[i + 1] = r >> BPC;
        }
        return c;
    }

    i8 operator-() const {
        i8 c = *this;
        for (int i = 0; i < 4; i++) c[i] = ~c[i];
        return c + i8(1);
    }

    i8 operator-(const i8 &b) const {
        return *this + (-b);
    }

    i8 operator>>(int x) const {
        assert(x <= BPC);
        bool neg = sgn() < 0;
        i8 c = *this;
        for (int i = 0; i < 4; i++) {
            c[i] >>= x;
            if (i < 3) c[i] |= (c[i + 1] & ((1 << x) - 1)) << (BPC - x);
        }
        if (neg) c[3] |= ((1 << x) - 1) << (BPC - x);
        return c;
    }

    bool operator==(const i8 &b) {
        return memcmp(a, b.a, sizeof(a)) == 0;
    }

    bool operator<(const i8 &b) {
        if (sgn() == 1 && b.sgn() == -1) return false;
        if (sgn() == -1 && b.sgn() == 1) return true;
        bool t = sgn() < 0 || b.sgn() < 0;
        i8 _a = t ? -(*this) : *this, _b = t ? -b : b;
        int i;
        for (i = 3; i >= 0 && _a[i] == _b[i]; i--) ;
        return i >= 0 && ((_a[i] < _b[i]) ^ t);
    }
} BOUND, INF;

struct Edge {
    int v;
    i8 w;
    int nxt;
};

static int n, m = 1, K, head[NMAX + 10];
static i8 mi;
static Edge e[NMAX * 2 + 10];

struct Data {
    i8 v[3] = {0, -INF, 0};
    int mi[3] = {0}, mx[3] = {0};

    void update() {
        if (v[1] < v[0]) {
            v[2] = v[0];
            mi[2] = mi[0];
            mx[2] = mx[0];
        } else if (v[0] < v[1]) {
            v[2] = v[1];
            mi[2] = mi[1];
            mx[2] = mx[1];
        } else {
            v[2] = v[0];
            mi[2] = min(mi[0], mi[1]);
            mx[2] = max(mx[0], mx[1]);
        }
    }
};

inline void chkmax(Data &a, int p, i8 v, int mi, int mx) {
    if (a.v[p] < v) {
        a.v[p] = v;
        a.mi[p] = mi;
        a.mx[p] = mx;
    } else if (v == a.v[p]) {
        a.mi[p] = min(a.mi[p], mi);
        a.mx[p] = max(a.mx[p], mx);
    }
}

Data eval(int x, int fa) {
    Data a;
    for (int i = head[x]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        Data b = eval(v, x);
        //printf("v = %d, {%lld, %lld, %lld, %d, %d, %d}\n", v, b.v0, b.v1, b.v2, b.c0, b.c1, b.c2);
        chkmax(a, 1, b.v[2] + a.v[1], b.mi[2] + a.mi[1], b.mx[2] + a.mx[1]);
        chkmax(a, 1, b.v[0] + e[i].w - mi + a.v[0], b.mi[0] + 1 + a.mi[0], b.mx[0] + 1 + a.mx[0]);
        chkmax(a, 0, b.v[2] + a.v[0], b.mi[2] + a.mi[0], b.mx[2] + a.mx[0]);
    }
    a.update();
    return a;
}

int main() {
    BOUND[2] = 1U << 10;
    INF[3] = 1U << (BPC - 3);
    scanf("%d%d", &n, &K);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        e[m] = {v, i8(1LL * K * w), head[u]};
        e[m + 1] = {u, i8(1LL * K * w), head[v]};
        head[u] = m;
        head[v] = m + 1;
        m += 2;
    }

    i8 l = -BOUND, r = BOUND;
    while (l < r) {
        mi = (l + r) >> 1;
        //printf("mi = %lld\n", mi);
        Data a = eval(1, 0);
        //printf("[%d, %d]\n", /*a.v[2],*/ a.mi[2], a.mx[2]);
        if (a.mx[2] < K) r = mi - 1;
        else if (a.mi[2] > K) l = mi + 1;
        else break;
    }
    if (r == -BOUND) puts("Impossible");
    else {
        if (mi < l || r < mi) mi = l;
        //mi.show();
        Data a = eval(1, 0);
        printf("%lld\n", (a.v[2] + mi * K).toll() / K);
    }

    return 0;
}
