#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_set>

using namespace std;

using ll = long long;
using i64 = ll;
using ld = long double;

ll qmul(ll a, ll b, ll m) { a %= m; b %= m;
ll r = a * b, s = ld(a) * b / m;
return ((r - m * s) % m + m) % m;
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
while(n2 % 2 == 0) n2 /= 2, s ++;
ll t = qpow(base, n2, n);
if(t == 1 || t == n - 1) return true;
for(s --; s >= 0; s --)
if((t = qmul(t, t, n)) == n - 1) return true;;
return false;
}
bool is_prime(ll n) {
static ll base[] = {2,3,5,7,11,13,17,19,23,29,31,37};
/*static ll lim[]={4,2047,1373653,25326001,3215031751LL,21\
52302898747LL,3474749660383LL,341550071728321LL,0,0,0,0};*/
if(n < 2) return false;
for(int i = 0; i < 12 && base[i] < n; i ++) {
// if(n < lim[i]) return true;
if(!miller_rabin(n, base[i])) return false;
}
return true;
}
ll f(ll x, ll m) { return (qmul(x, x, m) + 1) % m; }
ll rho(ll n) {
if(is_prime(n)) return n;
if(n % 2 == 0) return 2;
for(int i = 1; ; i ++) {
ll x = i, y = f(x, n), p = __gcd(y - x, n);
while(p == 1) { x = f(x, n); y = f(f(y, n), n);
p = __gcd((y - x + n) % n, n) % n;
}
if(p != 0 && p != n) return p;
}} // n=1

constexpr int NMAX = 1000;

using set = unordered_set<i64>;

void factor(set &s, i64 n) {
    if (n == 1)
        return;
    if (is_prime(n)) {
        s.insert(n);
    } else {
        i64 d = rho(n);
        factor(s, d);
        factor(s, n / d);
    }
}

int n;
i64 a[NMAX + 10];
set ps[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);
        factor(ps[i], a[i]);
    }

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