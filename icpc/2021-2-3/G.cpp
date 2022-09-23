#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>
#include <tr1/unordered_set>

using namespace std;

using ll = long long;
using i64 = ll;
using ld = long double;
using i8 = __int128_t;

// ll qmul(ll a, ll b, ll m) { a %= m; b %= m;
// ll r = a * b, s = ld(a) * b / m;
// return ((r - m * s) % m + m) % m;
// }
i64 qmul(i64 a, i64 b, i64 m) {
    return i8(a) * b % m;
}

ll qpow(ll a, ll k, ll m) {
    ll r = 1;
    for ( ; k; k >>= 1) {
        if (k & 1)
            r = qmul(r, a, m);
        a = qmul(a, a, m);
    }
    return r;
}

bool miller_rabin(ll n, ll base) {
ll n2 = n - 1, s = 0;
while((n2 & 1) == 0) (n2 >>= 1), s ++;
ll t = qpow(base, n2, n);
if(t == 1 || t == n - 1) return true;
for(s --; s >= 0; s --)
if((t = qmul(t, t, n)) == n - 1) return true;;
return false;
}
bool is_prime(ll n) {
static ll base[] = {2,3,5,7,11,13,17,19,23,29,31,37};
static ll lim[]={4,2047,1373653,25326001,3215031751LL,21\
52302898747LL,3474749660383LL,341550071728321LL,0,0,0,0};
if(n < 2) return false;
for(int i = 0; i < 12 && base[i] < n; i ++) {
if(n < lim[i]) return true;
if(!miller_rabin(n, base[i])) return false;
}
return true;
}

constexpr int NMAX = 1000;

using set = tr1::unordered_set<i64>;

int n;
bool mk[2000100];
bool ok[NMAX + 10];
i64 a[NMAX + 10];
set ps[NMAX + 10];

i64 isqrt(i64 a) {
    i64 l = 1, r = 2000000000ll;
    while (l < r) {
        i64 m = (l + r) / 2 + 1;
        if (m * m <= a)
            l = m;
        else
            r = m - 1;;
    }
    return l;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
    }

    constexpr int T = 1010000;
    for (i64 p = 2; p <= T; p++) {
        if (mk[p])
            continue;
        for (int i = 1; i <= n; i++) {
            int c = 0;
            while (a[i] % p == 0) {
                a[i] /= p;
                c++;
            }
            if (c)
                ps[i].insert(p);
        }
        for (int j = p + p; j <= T; j += p) {
            mk[j] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            ok[i] = true;
            continue;
        }
        if (is_prime(a[i])) {
            ok[i] = true;
            ps[i].insert(a[i]);
        } else {
            i64 s = isqrt(a[i]);
            if (s * s == a[i]) {
                ok[i] = true;
                ps[i].insert(s);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
    if (a[i] > 1 && a[j] > 1) {
        i64 r = __gcd(a[i], a[j]);
        if (r == 1)
            continue;
        if (!ok[i] && r != a[i]) {
            ok[i] = true;
            ps[i].insert(r);
            ps[i].insert(a[i] / r);
        }
        if (!ok[j] && r != a[j]) {
            ok[j] = true;
            ps[j].insert(r);
            ps[j].insert(a[j] / r);
        }
    };

    int sg = 0;
    for (int i = 1; i <= n; i++) {
        while (ps[i].size()) {
            i64 p = *ps[i].begin();
            int j = i + 1;
            for ( ; j <= n && ps[j].count(p); j++) {}

            int L = j - i;
            sg ^= L;

            for (int k = i; k < j; k++) {
                ps[k].erase(p);
            }
        }
    }

    puts(sg ? "First" : "Second");
    fprintf(stderr, "sg=%d\n", sg);
    return 0;
}