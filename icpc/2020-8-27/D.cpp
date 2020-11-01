#include <cstdio>
#include <cstring>
#include <climits>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef __int128_t i8;
typedef long long i64;
typedef pair<i64, i64> pi;
typedef unordered_map<pi, pi> mp_t;

namespace std {
    template <>
    struct hash<pi> {
        size_t operator()(const pi &z) const {
            static hash<i64> H;
            return H(z.first) ^ H(z.second);
        }
    };
};

#define LMAX 9
#define NMAX 800
#define INF (i8(LLONG_MAX) + 10)

mp_t ans;

i8 C(i8 n, int k) {
    if (n < k)
        return 0;
    i8 r = 1;
    for (int i = 0; i < k; i++) {
        r *= n - i;
    }
    for (int i = 0; i < k; i++) {
        r /= i + 1;
    }
    return r;
}

i8 locate(i8 a, int k) {
    static i8 lim[] = {
        i8(9223372036854775807) + 1,
        i8(9223372036854775807) + 1,
        8589934592,
        4194304,
        131072,
        16384,
        8192,
        1800,
        900,
        600,
        400
    };
    i8 l = 1, r = lim[k] - 1;
    while (l < r) {
        i8 m = ((l + r) >> 1) + 1;
        i8 v = C(m, k);
        if (v <= a)
            l = m;
        else
            r = m - 1;
    }

    i8 v = C(l, k);
    if (v == a)
        return l;
    return -1;
}

void output(i8 x) {
    if (x == 0)
        putchar('0');
    else {
        int c = 0;
        char buf[64];
        while (x) {
            buf[c++] = x % 10 + '0';
            x /= 10;
        }
        for (int i = c - 1; i >= 0; i--) {
            putchar(buf[i]);
        }
    }
}

void solve(i8 a, i8 b) {
    bool ok = false;
    i8 ansr, ansc;
    for (int k = LMAX; k >= 0; k--) {
        i8 r = locate(a, k);
        if (r > 0) {
            i8 y = a * (r - k) / (k + 1);
            if (y == b) {
                //i64 r4 = r;
                //printf("%lld %d\n", r4 + 1, k + 1);
                if (!ok || r + 1 < ansr) {
                    ansr = r + 1;
                    ansc = k + 1;
                }
                ok = true;
                //output(r + 1);
                //putchar(' ');
                //output(k + 1);
                //puts("");
                //return;
            }
        }

        r = locate(b, k);
        if (r > 0) {
            i8 rk = r - k;
            i8 y = b * rk / (r - rk + 1);
            if (y == a) {
                //i64 r4 = r;
                //printf("%lld %lld\n", r4 + 1, r4 - k);
                if (!ok || r + 1 < ansr) {
                    ansr = r + 1;
                    ansc = r - k;
                }
                ok = true;
                //output(r + 1);
                //putchar(' ');
                //output(r - k);
                //puts("");
                //return;
            }
        }
    }

    if (ok) {
        output(ansr);
        putchar(' ');
        output(ansc);
        puts("");
    } else {
        puts("fuck");
        int *a = NULL;
        *a = 1;
    }
}

void _main() {
    i64 a, b;
    scanf("%lld%lld", &a, &b);

    pi key(a, b);
    if (ans.count(key)) {
        pi ret = ans[key];
        printf("%lld %lld\n", ret.first, ret.second);
    } else
        solve(a, b);
}

i8 D[NMAX + 10][NMAX + 10];

int main() {
    for (int i = 0; i <= NMAX; i++) {
        D[i][0] = 1;
    }

    for (int i = 1; i <= NMAX; i++)
    for (int j = 1; j <= i; j++) {
        D[i][j] = D[i - 1][j] + D[i - 1][j - 1];
        if (D[i][j] >= INF)
            D[i][j] = INF;
    }

    /*4457400 5200300*/
    //for (int i = 1; i <= NMAX; i++)
    for (int i = NMAX; i >= 1; i--)
    for (int j = 0; j < i; j++) {
        i64 r = i + 1, c = j + 1;
        if (D[i][j] < INF && D[i][j + 1] < INF) {
            i64 x = D[i][j], y = D[i][j + 1];
            if (x > 0 && y > 0)
                ans[pi(x, y)] = pi(r, c);
        }
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
