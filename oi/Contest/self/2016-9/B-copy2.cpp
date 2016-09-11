// #define NDEBUG

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 4000
#define MOD 1000000007
#define NTT_MOD 1004535809
#define NTT_G 3

typedef long long int64;

inline int next_pow(int x) {
    int k = 1;
    while (k < x)
        k <<= 1;
    return k;
}

inline int64 quick_pow(int64 a, int64 b, int64 m) {
    int64 r = 1;
    while (b) {
        if (b & 1)
            r = r * a % m;
        a = a * a % m;
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
    int64 x, y;
    exgcd(a, m, x, y);
    return (x < 0 ? x + m : x);
}

static void rader(int n, int64 *seqin, int64 *seqout) {
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

static void _ntt(int n, int64 *seqin, int64 *seqout, bool reverse = false) {
    rader(n, seqin, seqout);

    for (int s = 2; s <= n; s <<= 1) {
        int mid = s >> 1;
        int64 wn;
        if (!reverse)
            wn = quick_pow(NTT_G, (NTT_MOD - 1) / s, NTT_MOD);
        else
            wn = quick_pow(NTT_G, NTT_MOD - 1 - (NTT_MOD - 1) / s, NTT_MOD);
        for (int i = 0; i < n; i += s) {
            int64 w = 1;
            for (int j = 0; j < mid; j++) {
                int64 t = (w * seqout[i + j + mid]) % NTT_MOD;
                seqout[i + j + mid] = (seqout[i + j] - t) % NTT_MOD;
                if (seqout[i + j + mid] < 0)
                    seqout[i + j + mid] += NTT_MOD;
                seqout[i + j] = (seqout[i + j] + t) % NTT_MOD;
                w *= wn;
                w %= NTT_MOD;
            }  // for
        }      // for
    }          // for
}

static void ntt(int n, int64 *seqin, int64 *seqout) {
    _ntt(n, seqin, seqout, false);
}

static void reverse_ntt(int n, int64 *seqin, int64 *seqout) {
    _ntt(n, seqin, seqout, true);

    for (int i = 0; i < n; i++) {
        seqout[i] *= inv(n, NTT_MOD);
        seqout[i] %= NTT_MOD;
    }  // for
}

static int n, m, people, c;

static int64 ctable[NMAX + 10][NMAX + 10];
static void compute_comb() {
    ctable[0][0] = 1;
    ctable[1][0] = ctable[1][1] = 1;

    for (int i = 2; i <= NMAX; i++) {
        ctable[i][0] = ctable[i][i] = 1;
        for (int j = 1; j < i; j++) {
            ctable[i][j] = (ctable[i - 1][j] + ctable[i - 1][j - 1]) % NTT_MOD;
        }  // for
    }      // for
}

inline int64 comb(int n, int m) {
    if (n < 0 || m < 0 || n < m)
        return 0;

    return ctable[n][m];
}

static int64 cw1[1000];
static int64 cw2[1000];
static int64 ch1[1000];
static int64 ch2[1000];
static int64 seq1[1000];
static int64 seq2[1000];
static int64 seq3[1000];
static int64 seq4[1000];

static int64 evaluate(int wmin1, int wmin2, int hmin1, int hmin2, int remain) {
    int w = m - 2 * (c - 1);
    int h = n - 2 * (c - 1);
    int64 answer = 0;

    memset(cw1, 0, sizeof(cw1));
    memset(cw2, 0, sizeof(cw2));
    memset(ch1, 0, sizeof(ch1));
    memset(ch2, 0, sizeof(ch2));

    for (int i = wmin1; i <= w - 2; i++)
        cw1[i] = comb(w - 2, i);
    for (int i = wmin2; i <= w - 2; i++)
        cw2[i] = comb(w - 2, i);
    for (int i = hmin1; i <= h - 2; i++)
        ch1[i] = comb(h - 2, i);
    for (int i = hmin2; i <= h - 2; i++)
        ch2[i] = comb(h - 2, i);

    int length = next_pow(2 * w + 2 * h);
    ntt(length, cw1, seq1);
    ntt(length, cw2, seq2);
    ntt(length, ch1, seq3);
    ntt(length, ch2, seq4);

    for (int i = 0; i < length; i++) {
        seq4[i] = (seq1[i] * seq2[i] % NTT_MOD) *
                  (seq3[i] * seq4[i] % NTT_MOD) % NTT_MOD;
    }  // for

    reverse_ntt(length, seq4, seq3);

    for (int i = 0; i <= min(remain, length - 1); i++) {
        answer += seq3[i] * comb(n * m - 2 * w - 2 * h + 4, remain - i) % MOD;
        answer %= MOD;
    }  // for

    return answer;
}

static int64 query() {
    int w = m - 2 * (c - 1);
    int h = n - 2 * (c - 1);
    int64 answer = 0;

    if (w == 1) {
        for (int i = 1; i <= h; i++) {
            answer += comb(h, i) * comb(n * m - h, people - i) % MOD;
            answer %= MOD;
        }  // for
    } else if (h == 1) {
        for (int i = 1; i <= w; i++) {
            answer += comb(w, i) * comb(n * m - w, people - i) % MOD;
            answer %= MOD;
        }  // for
    } else {
        answer += evaluate(1, 1, 1, 1, people);
        answer %= MOD;

        answer += evaluate(0, 1, 0, 1, people - 1) * 4 % MOD;
        answer %= MOD;

        answer += evaluate(0, 1, 0, 0, people - 2) * 2 % MOD;
        answer %= MOD;
        answer += evaluate(0, 0, 0, 1, people - 2) * 2 % MOD;
        answer %= MOD;
        answer += evaluate(0, 0, 0, 0, people - 2) * 2 % MOD;
        answer %= MOD;

        answer += evaluate(0, 0, 0, 0, people - 3) * 4 % MOD;
        answer %= MOD;

        answer += evaluate(0, 0, 0, 0, people - 4) % MOD;
        answer %= MOD;
    }

    return answer;
}

int main() {
    compute_comb();

    while (true) {
        scanf("%d%d%d%d", &n, &m, &people, &c);

        if (c == 0)
            break;

        printf("%lld\n", query());
    }  // while

    return 0;
}  // function main
