#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

i64 qpow(i64 a, i64 k, i64 m) {
    i64 r = 1;
    for ( ; k; k >>= 1, a = a * a % m) {
        if (k & 1)
            r = r * a % m;
    }
    return r;
}

struct pll {
    i64 div, rem;
};

typedef vector<pll> vpll;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) return x = 1, y = 0, a;
    i64 t = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return t;
}

i64 crt(vpll &s) {
    i64 re = 0, m = 1;
    for (auto &e : s)
        m *= e.div;
    for (auto &e : s) {
        i64 x, y, t = m / e.div;
        exgcd(t, e.div, x, y);
        re = (re + t * x % m * e.rem) % m;
    }
    return re;
}

void solve(i64 n) {
    i64 pr[32], t = 0;
    i64 phip[32];
    i64 phi = n, m = n;
    for (i64 p = 2; p * p <= m; p++) if (m % p == 0) {
        pr[t++] = 1;
        phip[t - 1] = p - 1;
        phi = phi * (p - 1) / p;
        while (m % p == 0) {
            m /= p;
            pr[t - 1] *= p;
            phip[t - 1] *= p;
        }
        phip[t - 1] /= p;
    }
    if (m > 1) {
        pr[t++] = m;
        phip[t - 1] = m - 1;
        phi = phi * (m - 1) / m;
    }

    vpll ret;
    for (int i = 0; i < t; i++) {
        i64 p = pr[i];
        i64 k = phi / phip[i];
        i64 v = k % 2 ? p - 1 : 1;
        if (p % 2 == 0 && p > 4)
            v = 1;

        ret.push_back({p, v});
    }

    i64 ans = crt(ret);
    if (ans < 0) ans += n;
    printf("%lld\n", ans);
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF)
        solve(n);

    return 0;
}