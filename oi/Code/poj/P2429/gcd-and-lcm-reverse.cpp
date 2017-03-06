/**
 * RE......
 */

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <climits>

#include <map>
#include <algorithm>

using namespace std;

typedef unsigned long long u64;

inline u64 quick_mul(u64 a, u64 b, u64 m) {
    u64 r = 0;

    while (b) {
        if (b & 1)
            r = (r + a) % m;
        a = (a << 1) % m;
        b >>= 1;
    }

    return r;
}

inline u64 quick_pow(u64 a, u64 b, u64 m) {
    u64 r = 1;

    while (b) {
        if (b & 1)
            r = quick_mul(r, a, m);
        a = quick_mul(a, a, m);
        b >>= 1;
    }

    return r;
}

inline u64 gcd(u64 a, u64 b) {
    while (b) {
        u64 m = a % b;
        a = b;
        b = m;
    }

    return a;
}

bool miller_rabin(u64 n) {
    const u64 BASIS[] = {2, 7, 61};

    u64 t = n - 1;
    int k = 0;
    while (!(t & 1)) {
        t >>= 1;
        k++;
    }

    for (size_t i = 0; i < sizeof(BASIS) / sizeof(u64); i++) {
        u64 u = quick_pow(BASIS[i] % n, t, n);

        if (u == 0)
            continue;

        for (int j = 0; j < k; j++) {
            u64 v = quick_mul(u, u, n);

            if (v == 1 && u != 1 && u != n - 1)
                return false;

            u = v;
        }

        if (u != 1)
            return false;
    }

    return true;
}

u64 pollard_rho(u64 n, u64 a) {
    int i = 1, k = 2;
    u64 x = rand() % n;
    u64 y = x;

    while (true) {
        i++;
        x = (quick_mul(x, x, n) + a) % n;

        if (x == y)
            return 0;

        u64 delta = y >= x ? y - x : y + n - x;
        u64 d = gcd(delta, n);
        
        if (1 < d && d < n)
            return d;

        if (i == k) {
            y = x;
            k <<= 1;
        }
    }
}

void factor(u64 n, int &pos, u64 *dest) {
    if (n == 1)
        return;
    if (miller_rabin(n))
        dest[pos++] = n;
    else {
        u64 a = 140;
        u64 d = 0;
        while (!d) {
            d = pollard_rho(n, a);
            a++;
        }

        factor(d, pos, dest);
        factor(n / d, pos, dest);
    }
}

static int tail;
static u64 divisor[100];
static map<u64, int> cnt;

int main() {
    srand(time(0));

    u64 g, l;
    while (scanf("%llu%llu", &g, &l) != EOF) {
        cnt.clear();

        tail = 0;
        factor(l, tail, divisor);
        for (int i = 0; i < tail; i++) {
            cnt[divisor[i]]++;
        }

        tail = 0;
        factor(g, tail, divisor);
        for (int i = 0; i < tail; i++) {
            cnt[divisor[i]]--;
        }

        tail = 0;
        for (map<u64, int>::iterator beg = cnt.begin();
             beg != cnt.end(); beg++) {
            if (beg->second == 0)
                continue;

            u64 v = 1;

            for (int i = 0; i < beg->second; i++) {
                v *= beg->first;
            }
            
            divisor[tail++] = v;
        }

        u64 a = LLONG_MAX, b = LLONG_MAX;
        for (int s = 0; s < (1 << tail); s++) {
            u64 u = g;
            for (int i = 0; i < tail; i++) {
                if ((s >> i) & 1)
                    u *= divisor[i];
            }
            u64 v = l / u * g;

            if (u + v < a + b) {
                a = u;
                b = v;
            }
        }

        if (a > b)
            swap(a, b);
        printf("%llu %llu\n", a, b);
    }
}
