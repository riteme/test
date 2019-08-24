#include <cstdio>
#include <cstring>
#include <climits>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;
typedef long double ld;

inline i64 qmul(i64 a, i64 b, i64 m) {
    i64 r = a * b, s = ld(a) * b / m;
    r = (r - m * s) % m;
    if (r < 0) r += m;
    return r;
}

inline i64 qpow(i64 a, i64 k, i64 m) {
    //if (m == 1) return 0;
    i64 r = 1;
    for ( ; k; k >>= 1, a = qmul(a, a, m))
        if (k & 1) r = qmul(r, a, m);
    return r;
}

inline bool miller(i64 n, i64 base) {
    i64 n2 = n - 1, s = 0;
    while (!(n2 & 1)) n2 >>= 1, s++;
    i64 t = qpow(base, n2, n);
    if (t == 1 || t == n - 1) return true;
    for (s--; s >= 0; s--)
        if ((t = qmul(t, t, n)) == n - 1) return true;
    return false;
}

inline bool isprime(i64 n) {
    static i64 base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (n < 2) return false;
    for (int i = 0; i < 12 && base[i] < n; i++)
        if (!miller(n, base[i])) return false;
    return true;
}

inline i64 exgcd(i64 a, i64 b, i64 &n, i64 &m) {
    if (!b) {
        n = 1;
        m = 0;
        return a;
    }
    i64 x, y, r = exgcd(b, a % b, x, y);
    n = y;
    m = x - a / b * y;
    return r;
}
inline i64 inv(i64 x, i64 m) {
    i64 r, _;
    exgcd(x, m, r, _);
    return r;
}

#define ACM_BEGIN
#define KMAX 64
static i64 p0[KMAX], p1[KMAX];
static int k0[KMAX], k1[KMAX], c0, c1;
inline i64 _f(i64 x, i64 m) {
    i64 r = qmul(x, x, m) + 1;
    if (r >= m) r -= m;
    return r;
}
inline void factor(i64 n) {
    if (n == 2 || isprime(n)) p0[c0++] = n;
    else if (!(n & 1)) factor(2), factor(n >> 1);
    else {
        for (int i = 1; ; i++) {
            i64 x = i, y = _f(x, n), p = __gcd(y - x, n);
            while (p == 1) {
                x = _f(x, n);
                y = _f(_f(y, n), n);
                p = __gcd((y - x + n) % n, n) % n;
            }
            if (p != 0 && p != n) {
                factor(p), factor(n / p);
                return;
}}}}
inline void psort(i64 *p, int *k, int &c) {
    sort(p, p + c);
    int t = 0;
    for (int i = 0, j; i < c; i = j) {
        for (j = i; j < c && p[i] == p[j]; j++) ;
        p[t] = p[i];
        k[t++] = j - i;
    } c = t;
}
void ord(i64 a, i64 m, int p = 0, i64 cur = 1) {
    static i64 tmp[KMAX + 10], mi;
    static int t;
    if (p == 0) mi = LLONG_MAX;
    if (p == c0 && qpow(a, cur, m) == 1 && cur < mi) {
        mi = cur;
        memcpy(p1, tmp, sizeof(i64) * t);
        c1 = t;
    } else if (p != c0) {
        int t0 = t;
        for (int k = 0; k <= k0[p] && cur < mi; k++, cur *= p0[p]) {
            if (k) tmp[t++] = p0[p];
            ord(a, m, p + 1, cur);
        } t = t0;
}}
inline i64 log(i64 a, i64 b, i64 m, i64 p, int k) {
    typedef unordered_map<i64, i64> Map;
    static Map tb;
    i64 pw = 1, bc, bt = 1, s = 1;
    for (int i = 1; i < k; i++) pw *= p;
    i64 g = qpow(a, pw, m), ai = inv(a, m), x = 0;
    for (bc = g; s * s <= p; s++) bc = qmul(bc, g, m);
    tb.clear();
    for (i64 i = 1, t = bc; i <= s; i++, t = qmul(t, bc, m))
        tb.insert(make_pair(t, i));
    for (int i = 0; i < k; i++, pw /= p, bt *= p) {
        i64 b0 = qpow(qmul(b, qpow(ai, x, m), m), pw, m), d = -1;
        for (i64 j = 0, t = b0; j < s; j++, t = qmul(t, g, m)) {
            Map::iterator it = tb.find(t);
            if (it != tb.end()) {
                d = it->second * s - j;
                if (d >= p) d -= p;
                break;
        }}
        if (d == -1) return -1;
        x += bt * d;
    } return x;
}
inline i64 log(i64 a, i64 b, i64 m) {
    if (a == 1) return b == 1 ? 0 : -1;
    i64 m0 = 1, x = 0;
    for (int i = 0; i < c1; i++)
        for (int j = 0; j < k1[i]; j++) m0 *= p1[i];
    for (int i = 0; i < c1; i++) {
        i64 pw = p1[i];
        for (int j = 1; j < k1[i]; j++) pw *= p1[i];
        i64 mi = m0 / pw, r = log(qpow(a, mi, m), qpow(b, mi, m), m, p1[i], k1[i]);
        if (r == -1) return -1;
        x = (x + qmul(qmul(r, mi, m0), inv(mi, pw), m0)) % m0;
    } return x < 0 ? x + m0 : x;
}
#define ACM_END

int main() {
    int T;
    scanf("%d", &T);
    i64 m, a, b;
    scanf("%lld", &m);
#define ACM_BEGIN
    factor(m - 1);
    psort(p0, k0, c0);
#define ACM_END
    while (T--) {
        fprintf(stderr, "%d\n", T);
        scanf("%lld%lld", &a, &b);
#define ACM_BEGIN
    ord(a, m);
    psort(p1, k1, c1);
    i64 ans = log(a, b, m);
#define ACM_END
        printf("%lld\n", ans);
    }
    return 0;
}
