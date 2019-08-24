#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 64
#define LMAX 19
#define SMAX (1 << LMAX)

typedef long long i64;
typedef pair<i64, i64> i64Pair;

namespace std {
    template <>
    struct hash<i64Pair> {
        size_t operator()(const i64Pair &p) const {
            constexpr auto h = hash<i64>();
            return h(p.first) ^ h(p.second);
        }
    };
}

inline i64 readbits() {
    static char buf[BUFFERSIZE];
    scanf("%s", buf);
    i64 ret = 0;
    for (int i = 0; buf[i]; i++) ret = (ret << 1) | (buf[i] == '1');
    return ret;
}

static int n, m, L;
static i64 K, poly, str;
static unordered_map<i64Pair, bool> dat;

#ifndef NDEBUG
#define DEBUG(str, ...) printf(str "\n", __VA_ARGS__)

inline void bin(i64 x) {
    for (int i = L - 1; i >= 0; i--)
        putchar(((x >> i) & 1) ? '1' : '0');
}

inline void print(i64 *arr) {
    for (int s = 0; s < (1 << L); s++) {
        if (arr[s]) {
            bin(s);
            printf(": %lld\n", arr[s]);
        }
    }
}

inline void print(i64 s, i64 t, i64 v) {
    if (!v) return;
    if (s >= 0) bin(s);
    else printf("new");
    printf(" -> ");
    bin(t);
    printf(" [+%lld]\n", v);
}
#else
#define bin(...)
#define print(...)
#define DEBUG(...)
#endif

bool _bit(i64 p, i64 k) {
    if (k == 0) return !p;
    if (k == 1) return (poly >> p) & 1;
    if (k & 1) {
        auto pos = make_pair(p, k);
        if (dat.count(pos)) return dat[pos];
        bool &ret = dat[pos];
        for (int i = 0; i <= n; i++) if ((poly >> i) & 1)
            ret ^= _bit(p - i, k ^ 1);
        return ret;
    } else return p & 1 ? 0 : _bit(p >> 1, k >> 1);
}

i64 bit(i64 p, i64 k) {
    return _bit(p, k);
}

inline i64 prod(i64 a, i64 b, int bl) {
    i64 r = 0;
    for (int i = 0; i <= bl; i++)
        if ((b >> i) & 1) r ^= a << i;
    return r;
}

static int t1[SMAX], t2[SMAX];
static i64 f[SMAX], g[SMAX];

inline void scan(i64 low, i64 high, i64 k) {
    DEBUG("low = %lld, high = %lld", low, high);
    if (high - low + 1 < L) return;
    i64 tmp = 0;
    for (i64 i = 0; i < L; i++) tmp |= bit(low + i, k) << i;
    print(-1, tmp, 1);
    g[tmp]++;
    for (i64 i = low + L; i <= high; i++) {
        tmp = (tmp >> 1) | (bit(i, k) << (L - 1));
        print(-1, tmp, 1);
        g[tmp]++;
    }
}

void dp(i64 r, i64 k) {
    const i64 mask = (1 << L) - 1;
    if (k == 1) {
        DEBUG("r = %lld, k = %lld", r, k);
        for (i64 i = r; i + L <= n + 1; i++)
            g[(poly >> i) & mask]++;
    } else if (k & 1) {
        i64 p = r >> 1;
        dp(p, k >> 1);
        DEBUG("r = %lld, k = %lld", r, k);
        for (int s = 0; s < (1 << L); s++) {
            print(s, t2[s] >> 1, f[s]);
            g[t2[s] >> 1] += f[s];
            print(s, t2[s] & mask, f[s]);
            g[t2[s] & mask] += f[s];
        }
        i64 p1 = max(r, (p << 1) + n + L - 3), p2 = max(r, n * (k - 1) - L + 2);
        if (p1 - L + 1 >= p2) scan(r, n * k, k);
        else {
            scan(r, p1, k);
            scan(p2, n * k, k);
        }
    } else {
        dp(r >> 1, k >> 1);
        DEBUG("r = %lld, k = %lld", r, k);
        for (int s = 0; s < (1 << L); s++) {
            print(s, t1[s] >> 1, f[s]);
            g[t1[s] >> 1] += f[s];
            print(s, t1[s] & mask, f[s]);
            g[t1[s] & mask] += f[s];
        }
        scan(r, min(n * k, r + (L - 2) * 2 - (r & 1 ? 1 : 0)), k);
    }
    print(g);
    memcpy(f, g, sizeof(f));
    memset(g, 0, sizeof(g));
}

i64 query(i64 r) {
    if (r < m) return 0;
    const i64 mask = (1 << m) - 1;
    if (r < L) {
        i64 tmp = 0, ret = 0;
        for (int i = 0; i < r; i++) tmp |= bit(n * K - r + i + 1, K) << i;
        for (int i = 0; i + m <= r; i++)
            if (!(((tmp >> i) & mask) ^ str)) ret++;
        return ret;
    }
    dp(n * K - r + 1, K);
    i64 ret = 0;
    for (int s = 0; s < (1 << L); s++)
        if (!((s & mask) ^ str)) ret += f[s];
    if (L > m) {
        i64 tmp = 0;
        for (int i = 1; i < L; i++)
            tmp |= bit(n * K - L + i + 1, K) << i;
        for (int i = 1; i + m <= L; i++)
            if (!(((tmp >> i) & mask) ^ str)) ret++;
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 l, r;
        scanf("%d%lld%d%lld%lld", &n, &K, &m, &l, &r);
        L = max(n + 1, m);
        poly = readbits();
        str = readbits();
        dat.clear();
        const i64 mask = (1 << (L + 1)) - 1;
        for (int s = 0; s < (1 << L); s++) {
            i64 s2 = prod(s, s, L - 1) << 1;
            t1[s] = s2 >> (L - 1);
            t2[s] = (prod(s2, poly, n) >> (L - 1)) & mask;
        }

#ifndef NDEBUG
        for (int p = 1; p <= n * K + 1; p++)
            printf("!!!>>> p = %d, %lld <<<!!!\n\n", p, query(p));
#else
        if (r - l + 1 < m) puts("0");
        else printf("%lld\n", query(r) - query(l + m - 2));
#endif
    }
    return 0;
}
