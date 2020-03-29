#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>

using namespace std;

typedef long long i64;

i64 qpow(i64 a, i64 k, i64 p) {
    i64 r = 1;
    for ( ; k; a = a * a % p, k >>= 1)
        if (k & 1) r = r * a % p;
    return r;
}

i64 qr(i64 a, i64 p) {
    if (p == 2) return 1;
    i64 p2 = p / 2, tmp = qpow(a, p2, p);
    if (tmp == p - 1) return 0;
    if ((p + 1) % 4 == 0)
        return qpow(a, (p + 1) / 4, p);
    i64 t = 0, h = p - 1, b, pb;
    for ( ; h % 2 == 0; h /= 2) t++;
    if (t >= 2) {
        do {
            b = rand() % (p - 2) + 1;
        } while (qpow(b, p / 2, p) != p - 1);
        pb = qpow(b, h, p);
    }
    i64 s = qpow(a, h / 2, p);
    for (int i = 2; i <= t; i++) {
        i64 ss = (s * s) % p * a % p;
        for (int j = 0; i + j < t; j++)
            ss = ss * ss % p;
        if (ss + 1 == p)
            s = s * pb % p;
        pb = pb * pb % p;
    }
    return s * a % p;
}

int main() {
    srand(time(NULL));
    int T;
    scanf("%d", &T);
    while (T--) {
        i64 v;
        scanf("%lld", &v);
        if (v <= 1) printf("%lld\n", v);
        else {
            i64 m = 1;
            while (v >= m)
                m *= 10;
            // printf("m = %lld\n", m);

            i64 r = qr(v, m);
            if (!r) puts("None");
            else {
                if (m - r < r)
                    r = m - r;
                printf("%lld\n", r);
            }
        }
    }
    return 0;
}