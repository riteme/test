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
ll f(ll x, ll m) { return (qmul(x, x, m) + 1) % m; }
ll rho(ll n) {
// if(is_prime(n)) return n;
if(n % 2 == 0) return 2;
for(int i = 1; ; i ++) {
ll x = i, y = f(x, n), p = __gcd(y - x, n);
while(p == 1) { x = f(x, n); y = f(f(y, n), n);
i64 z = y - x;
if (z < 0)
    z += n;
else if (z >= n)
    z -= n;
p = __gcd(z, n);
}
if(p != 0 && p != n) return p;
}} // n=1

constexpr int NMAX = 1000;

using set = tr1::unordered_set<i64>;

i64 todo[120000] , cnt;

void factor(set &s, i64 n) {
    cnt = 1;
    todo[1] = n;
    while ( cnt ) {
    	if ( todo[cnt] == 1 ) {cnt--;continue;}
    	if ( is_prime(todo[cnt]) ) {
    		s.insert( todo[cnt] );
    		for ( i64 i = 1 ; i < cnt ; i++ ) {
    			while ( todo[i] % todo[cnt] == 0 ) {
    				todo[i] /= todo[cnt];
    			}
    		}
    		cnt--;
    	}
    	else {
    		i64 d = rho (todo[cnt]);
    		todo[cnt] /= d;
    		todo[++cnt] = d;
    	}
    }
}

int n;
i64 a[NMAX + 10];
set ps[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a + i);

        if (i == 1)
            factor(ps[i], a[i]);
        else {
            i64 r = __gcd(a[i], a[i - 1]);
            a[i] /= r;
            factor(ps[i], a[i]);
            for (i64 p : ps[i - 1]) {
                if (r % p == 0)
                    ps[i].insert(p);
            }
        }
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
    return 0;
}