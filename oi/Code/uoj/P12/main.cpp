#include <cstdio>
#include <cstring>
#include <climits>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef long long i64;

inline i64 gcd(i64 a, i64 b) {
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (b) {
        i64 t = a % b;
        a = b;
        b = t;
    }

    return a;
}

inline i64 qmul(i64 a, i64 b, i64 p) {
    i64 r = 0;
    for (; b; b >>= 1, a = (a << 1) % p) {
        if (b & 1)
            r = (r + a) % p;
    }

    return r;
}

inline i64 qpow(i64 a, i64 b, i64 p) {
    i64 r = 1;
    for (; b; b >>= 1, a = qmul(a, a, p)) {
        if (b & 1)
            // r = r * a % p;
            r = qmul(r, a, p);
    }

    return r;
}


inline bool miller_rabin(i64 x) {
    const i64 B[] = {2, 7, 61};

    i64 t = x - 1;
    int c = 0;
    while (!(t & 1)) {
        t >>= 1;
        c++;
    }

    for (int i = 0; i < 3; i++) {
        if (x == B[i])
            return true;

        i64 v = qpow(B[i], t, x);

        for (int j = 0; j < c; j++) {
            // i64 u = v * v % x;
            i64 u = qmul(v, v, x);

            if (u == 1 && v != 1 && v != x - 1)
                return false;

            v = u;
        }

        if (v != 1)
            return false;
    }

    return true;
}

int pollard_rho(i64 n, i64 a) {
    int i = 1, k = 2;
    i64 x = rand() % n, y = x % n;
    while (true) {
        // x = (x * x + a) % n;
        x = (qmul(x, x, n) + a) % n;
        i++;

        if (x == y)
            return 0;

        i64 d = gcd(y - x, n);

        if (1 < d && d < n)
            return d;

        if (i == k) {
            k <<= 1;
            y = x;
        }
    }
}

static unordered_map<i64, int> fac;

void factor(i64 n) {
    if (n == 1)
        return;
    if (miller_rabin(n)) {
        fac[n]++;
        return;
    }

    int a = 233, d = 0;
    while (!d && a > 0) {
        d = pollard_rho(n, a--);
    }

    factor(d);
    factor(n / d);
}

int main() {
    srand(time(0));
    int t;
    scanf("%d", &t);

    while (t--) {
        fac.clear();
        i64 g, l;
        scanf("%lld%lld", &g, &l);
        i64 ans1 = 1, ans2 = g + l;
        factor(g);
        factor(l);
        for (auto &e : fac) {
            ans1 *= qpow(e.first, e.second / 2, LLONG_MAX);
        }
        ans1 *= 2;
        printf("%lld %lld\n", ans1, ans2);
    }

    return 0;
}
