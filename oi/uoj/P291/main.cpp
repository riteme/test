#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 998244353LL
#define INV4 748683265LL

#define MODIFY 1
#define QUERY 2

typedef long long i64;

i64 _inverse(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * _inverse(MOD % x) % MOD;
}

i64 inverse(i64 x) {
    return _inverse(x < 0 ? x + MOD : x);
}

struct Array4i {
    Array4i() {
        a[0] = a[1] = a[2] = a[3] = 1;
        memset(cnt, 0, sizeof(cnt));
    }
    Array4i(i64 a0, i64 a1, i64 a2, i64 a3) {
        if (a0) a[0] = a0, cnt[0] = 0; else a[0] = 1, cnt[0] = 1;
        if (a1) a[1] = a1, cnt[1] = 0; else a[1] = 1, cnt[1] = 1;
        if (a2) a[2] = a2, cnt[2] = 0; else a[2] = 1, cnt[2] = 1;
        if (a3) a[3] = a3, cnt[3] = 0; else a[3] = 1, cnt[3] = 1;
    }
    Array4i(i64 a0, i64 a1, i64 a2, i64 a3, int c0, int c1, int c2, int c3) {
        a[0] = a0; a[1] = a1; a[2] = a2; a[3] = a3;
        cnt[0] = c0; cnt[1] = c1; cnt[2] = c2; cnt[3] = c3;
    }

    i64 a[4];
    int cnt[4];

    i64 get(const int i) const {
        return cnt[i] ? 0 : a[i];
    }

    Array4i inv() const {
        return {
            inverse(a[0]), inverse(a[1]), inverse(a[2]), inverse(a[3]),
            -cnt[0], -cnt[1], -cnt[2], -cnt[3]
        };
    }

    Array4i operator*(const Array4i &b) const {
        return {
            a[0] * b[0] % MOD, a[1] * b[1] % MOD, a[2] * b[2] % MOD, a[3] * b[3] % MOD,
            cnt[0] + b.cnt[0], cnt[1] + b.cnt[1], cnt[2] + b.cnt[2], cnt[3] + b.cnt[3]
        };
    }

    Array4i &operator*=(const Array4i &b) {
        for (int i = 0; i < 4; i++) {
            a[i] = a[i] * b[i] % MOD;
            cnt[i] += b.cnt[i];
        }
        return *this;
    }

    const i64 operator[](const int i) const {
        return a[i];
    }
};

inline Array4i fwt(const Array4i &ar) {
    i64 a0 = ar.get(0), a1 = ar.get(1), a2 = ar.get(2), a3 = ar.get(3);
    i64 a = a0 + a1, b = a0 - a1, c = a2 + a3, d = a2 - a3;
    return {(a + c) % MOD, (b + d) % MOD, (a - c) % MOD, (b - d) % MOD};
}

inline Array4i rfwt(const Array4i &ar) {
    i64 a0 = ar.get(0), a1 = ar.get(1), a2 = ar.get(2), a3 = ar.get(3);
    i64 a = a0 + a1, b = a0 - a1, c = a2 + a3, d = a2 - a3;
    return {(a + c) * INV4 % MOD, (b + d) * INV4 % MOD, (a - c) * INV4 % MOD, (b - d) * INV4 % MOD};
}

class Fenwick {
 public:
    Fenwick(int n) : cur(0), num(n) {
        memset(ver, 0, sizeof(ver));
    }

    void clear() {
        cur++;
    }

    void modify(int x, const Array4i &v) {
        for (; x <= num; x += x & -x) {
            access(x);
            bit[x] *= v;
        }
    }

    Array4i query(int x) {
        Array4i ret;
        for (; x; x ^= x & -x) {
            access(x);
            ret *= bit[x];
        }
        return ret;
    }

 private:
    Array4i bit[NMAX + 10];
    int ver[NMAX + 10], cur, num;

    void access(int x) {
        if (cur > ver[x]) {
            ver[x] = cur;
            bit[x] = Array4i();
        }
    }
};

static int n, q;
static struct Op {
    int type, l, r;
    Array4i ans;
} op[NMAX + 10];
static i64 inv[NMAX + 10];
static Fenwick *bit;

void solve(int l, int r) {
    static struct Slot {
        Op *ptr;
        int *p;

        bool operator<(const Slot &b) const {
            if (*p == *b.p) {
                if (ptr->type == MODIFY && p == &ptr->r) return false;
                if (b.ptr->type == MODIFY && b.p == &b.ptr->r) return true;
                return ptr->type < b.ptr->type;
            }
            return *p < *b.p;
        }
    } seq[NMAX * 2 + 10];

    if (l == r) return;
    int m = (l + r) >> 1, cnt = 0;
    for (int i = l; i <= m; i++) {
        if (op[i].type != MODIFY) continue;
        seq[++cnt] = {op + i, &op[i].l};
        seq[++cnt] = {op + i, &op[i].r};
    }
    for (int i = m + 1; i <= r; i++) {
        if (op[i].type != QUERY) continue;
        seq[++cnt] = {op + i, &op[i].l};
        seq[++cnt] = {op + i, &op[i].r};
    }

    bit->clear();
    sort(seq + 1, seq + cnt + 1);
    Array4i pl, pr;
    for (int i = 1; i <= cnt; i++) {
        auto p = seq[i].ptr;
        if (p->type == MODIFY) {
            int L = p->r - p->l + 1;
            auto vl = fwt({(L - 1) * inv[L] % MOD, 0, inv[L], 0});
            auto vr = fwt({(L - 1) * inv[L] % MOD, inv[L], 0, 0});
            if (seq[i].p == &p->l) {
                pl *= vl;
                pr *= vr;
                bit->modify(p->l,
                    fwt({(L - 2) * inv[L] % MOD, inv[L], inv[L], 0})
                    * vl.inv() * vr.inv());
            } else {
                pl *= vl.inv();
                pr *= vr.inv();
                bit->modify(p->l,
                    fwt({(L - 2) * inv[L] % MOD, inv[L], inv[L], 0}).inv()
                    * vl * vr);
            }
        } else {
            if (seq[i].p == &p->l) p->ans *= pl;
            else p->ans *= pr * bit->query(p->l);
        }
    }

    solve(l, m);
    solve(m + 1, r);
}

int main() {
    scanf("%d%d", &n, &q);
    bit = new Fenwick(n);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
    for (int i = 1; i <= q; i++) {
        scanf("%d%d%d", &op[i].type, &op[i].l, &op[i].r);
        if (op[i].type == QUERY) op[i].l--;
    }

    solve(1, q);
    for (int j = 1, i = 0, c = 0; j <= q; j++) {
        if (op[j].type == MODIFY) i = j, c++;
        else {
            int l = op[j].l, r = op[j].r;
            auto ret = op[j].ans;
            if (!l && (c & 1)) {
                int L = op[i].r - op[i].l + 1;
                if (op[i].l <= r && r <= op[i].r) ret *= fwt({
                    (L - 1) * inv[L] % MOD, inv[L], 0, 0
                }).inv();
                if (op[i].r < r) ret *= fwt({0, 1, 0, 0});
                else if (op[i].l > r) ret *= fwt({0, 0, 1, 0});
                else ret *= fwt({inv[L], (r - op[i].l) * inv[L] % MOD,
                    (op[i].r - r) * inv[L] % MOD, 0});
                //else ret *= fwt({inv[L], (op[i].r - r) * inv[L] % MOD,
                //    (r - op[i].l) * inv[L] % MOD, 0});
            }
            ret = rfwt(ret);
            i64 ans = (ret.get(0) + ret.get(3)) % MOD;
            if (ans < 0) ans += MOD;
            printf("%lld\n", ans);
        }
    }

    return 0;
}
