#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

i64 qpow(i64 a, i64 k, i64 m) {
    i64 r = 1;
    for ( ; k; a = a * a % m, k >>= 1)
        if (k & 1) r = r * a % m;
    return r;
}

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) return x = 1, y = 0, a;
    i64 t = exgcd(b, a % b, y, x);
    return y -= a / b * x, t;
}

struct Item {
    i64 div, rem;
};

typedef vector<Item> vpll;

i64 crt(const vpll &s) {
    i64 ret = 0, m = 1;
    for (auto &e : s)
        m *= e.div;

    for (auto &e : s) {
        i64 x, y, t = m / e.div;
        exgcd(t, e.div, x, y);
        ret = (ret + t * x % m * e.rem) % m;
    }

    return ret;
}

i64 inv(i64 a, i64 n) {
    i64 x, y;
    exgcd(a, n, x, y);
    return x;
}

i64 get(i64 n, i64 mod, i64 p) {
    i64 ans = 1;
    for (int i = 1; i <= n; i++)
        if (i % p != 0) ans = ans * i % mod;
    return ans;
}

struct Pair {
    i64 fi, se;
};

Pair fac(i64 n, i64 mod, i64 p) {
    i64 init = get(mod, mod, p);
    Pair ans = {1, 0};
    for (i64 now = p; now <= n; now *= p) {
        ans.se += n / now;
        if (now > n / p) break;
    }

    while (n > 0) {
        ans.fi = ans.fi * qpow(init, n / mod, mod) % mod;
        ans.fi = ans.fi * get(n % mod, mod, p) % mod;
        n /= p;
    }

    return ans;
}

i64 C(i64 n, i64 k, i64 mod, i64 p) {
    auto a = fac(n, mod, p);
    auto b = fac(k, mod, p);
    auto c = fac(n - k, mod, p);
    return a.fi * inv(b.fi, mod) % mod
        * inv(c.fi, mod) % mod
        * qpow(p, a.se - b.se - c.se, mod) % mod;
}

void solve() {
    i64 n, k, MOD;
    scanf("%lld%lld%lld", &n, &k, &MOD);

    vpll vec;
    i64 M = MOD;
    for (i64 i = 2; i * i <= M; i++) if (M % i == 0) {
        i64 pr = i;
        while (M % (pr * i) == 0)
            pr *= i;
        M /= pr;
        vec.push_back({pr, C(n, k, pr, i)});
    }
    if (M > 1)
        vec.push_back({M, C(n, k, M, M)});

    i64 v = crt(vec);
    if (v < 0) v += MOD;
    if (v) {
        i64 ans = 0;
        for (int j = n - k; j >= 0; j--) {
            ans = (ans + (j & 1 ? -1 : 1) * v) % MOD;
            v = v * j % MOD;
            if (v == 0) break;
        }

        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    } else puts("0");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case %d: ", i);
        solve();
    }

    return 0;
}