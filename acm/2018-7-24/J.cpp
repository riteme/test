#define NDEBUG

#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#ifndef NDEBUG
template <typename ... T>
inline void DEBUG(const char *str, const T& ...args) {
    printf(str, args...);
    putchar('\n');
}
#else
#define DEBUG(...)
#endif

typedef long long i64;

#ifndef NDEBUG
template <>
const i64& std::max(const i64 &a, const i64 &b) {
    DEBUG("max: %lld, %lld", a, b);
    return a < b ? b : a;
}
#endif

#define KMAX 62

struct Interval {
    Interval(i64 _l, i64 _r) : l(_l), r(_r) {}

    i64 l, r;

    bool operator==(const Interval &b) const {
        return l == b.l && r == b.r;
    }

    i64 len() const {
        return l ? r - l + 1 : 0;
    }
};

inline Interval locate(i64 x, int k) {
    i64 l = x & (~((1LL << k) - 1));
    i64 r = l + ((1LL << k) - 1);
    return Interval(l, r);
}

inline int bit(i64 x, int k) {
    return (x >> k) & 1;
}

inline Interval detect(i64 l, i64 r, int k) {
    Interval il = locate(l, k), ir = locate(r, k);
    if (!bit(l, k) && il.l == l && il.r <= r) return il;
    if (!bit(r, k) && l <= ir.l && ir.r == r) return ir;

    l = il.r + 1;
    r = ir.l - 1;
    if (r < l) return Interval(0, 0);

    i64 p = l + (1LL << k) - 1, q = p + (1LL << k);
    if (bit(l, k)) return q <= r ? Interval(p + 1, q) : Interval(0, 0);
    else return p <= r ? Interval(l, p) : Interval(0, 0);
}

i64 dfs(i64 l, i64 r, i64 v, int k) {
    DEBUG("l = %lld, r = %lld, k = %d", l, r, k);
    if (k < 0) return r - l + 1;

    Interval il = locate(l, k), ir = locate(r, k), full = detect(l, r, k);
    il.l = l; il.r = min(il.r, r);
    ir.l = max(ir.l, l), ir.r = r;

    if (bit(v, k))
        return max(
            max(bit(l, k) ? 0 : il.len(), bit(r, k) ? 0 : ir.len()),
            max(full.len(), dfs(l, r, v, k - 1))
        );
    else {
        if (full.l) return dfs(full.l, full.r, v, k - 1);
        if (il == ir) return bit(l, k) ? 0 : dfs(l, r, v, k - 1);
        return max(
            bit(l, k) ? 0 : dfs(il.l, il.r, v, k - 1),
            bit(r, k) ? 0 : dfs(ir.l, ir.r, v, k - 1)
        );
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        i64 l, r, v;
        scanf("%lld%lld%lld", &l, &r, &v);
        printf("%lld\n", dfs(l, r, v, KMAX));
    }

    return 0;
}
