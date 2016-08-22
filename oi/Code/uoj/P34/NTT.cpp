// #define NDEBUG

#include <bits/stdc++.h>

using namespace std;

#define NMAX 524288
#define MOD 1004535809
#define G 3

inline int next_pow(int x) {
    int k = 1;
    while (k < x)
        k <<= 1;
    return k;
}

typedef long long int64;

static int n;
static int length;
static int64 a[NMAX];
static int64 aout[NMAX];
static int64 b[NMAX];
static int64 bout[NMAX];

inline int64 quick_pow(int64 a, int64 b, int64 m) {
    int64 r = 1;
    while (b) {
        if (b & 1) {
            r *= a;
            r %= MOD;
        }

        a *= a;
        a %= MOD;
        b >>= 1;
    }  // while

    return r;
}

inline int64 exgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int64 m, n;
    int64 r = exgcd(b, a % b, m, n);
    x = n;
    y = m - (a / b) * n;
    return r;
}

inline int64 inv(int64 a, int64 m) {
    // return quick_pow(a, m - 2, m);
    int64 x, y;
    exgcd(a, m, x, y);
    return (x < 0 ? x + m : x);
}

static void rader(int64 *seqin, int64 *seqout) {
    seqout[0] = seqin[0];
    int rev = 0;
    for (int i = 1; i < n; i++) {
        int k = n >> 1;
        while (k <= rev) {
            rev -= k;
            k >>= 1;
        }
        rev += k;
        seqout[rev] = seqin[i];
    }  // for
}

static void ntt(int64 *seqin, int64 *seqout, bool reverse = false) {
    rader(seqin, seqout);

    for (int s = 2; s <= n; s <<= 1) {
        int mid = s >> 1;
        int64 wn;
        if (!reverse)
            wn = quick_pow(G, (MOD - 1) / s, MOD);
        else
            wn = quick_pow(G, MOD - 1 - (MOD - 1) / s, MOD);
        for (int i = 0; i < n; i += s) {
            int64 w = 1;
            for (int j = 0; j < mid; j++) {
                int64 t = (w * seqout[i + j + mid]) % MOD;
                seqout[i + j + mid] = (seqout[i + j] - t) % MOD;
                if (seqout[i + j + mid] < 0)
                    seqout[i + j + mid] += MOD;
                seqout[i + j] = (seqout[i + j] + t) % MOD;
                w *= wn;
                w %= MOD;
            }  // for
        }      // for
    }          // for
}

static void initialize() {
    int alen, blen;
    scanf("%d%d", &alen, &blen);

    length = alen + blen + 1;
    n = next_pow(length);

    for (int i = 0; i <= alen; i++) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }  // for

    for (int i = 0; i <= blen; i++) {
        int x;
        scanf("%d", &x);
        b[i] = x;
    }  // for
}

int main() {
    initialize();

    ntt(a, aout);
    ntt(b, bout);
    for (int i = 0; i < n; i++) {
        bout[i] *= aout[i];
        bout[i] %= MOD;
        // bout[i] %= MOD;
    }  // for
    ntt(bout, a, true);
    for (int i = 0; i < length; i++) {
        a[i] *= inv(n, MOD);
        a[i] %= MOD;
    }  // for
    for (int i = 0; i < length; i++) {
        printf("%lld ", a[i]);
    }  // for

    return 0;
}  // function main
