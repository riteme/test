// #define NDEBUG

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 4000
#define MOD 1000000007

typedef long long int64;

static int n, m, people, c;

static int64 ctable[NMAX + 10][NMAX + 10];
static void compute_comb() {
    ctable[0][0] = 1;
    ctable[1][0] = ctable[1][1] = 1;

    for (int i = 2; i <= NMAX; i++) {
        ctable[i][0] = ctable[i][i] = 1;
        for (int j = 1; j < i; j++) {
            ctable[i][j] = (ctable[i - 1][j] + ctable[i - 1][j - 1]) % MOD;
        }  // for
    }      // for
}

inline int64 comb(int n, int m) {
    if (n < 0 || m < 0 || n < m)
        return 0;

    return ctable[n][m];
}

static void multiply(int64 *a, int alen, int64 *b, int blen, int64 *c) {
    for (int i = 0; i <= alen; i++) {
        for (int j = 0; j <= blen; j++) {
            c[i + j] += a[i] * b[j] % MOD;
            c[i + j] %= MOD;
        }  // for
    }      // for
}

static int64 cw1[400];
static int64 cw2[400];
static int64 ch1[400];
static int64 ch2[400];
static int64 seq1[400];
static int64 seq2[400];
static int64 seq3[400];

static int64 evaluate(int wmin1, int wmin2, int hmin1, int hmin2, int remain) {
    int w = m - 2 * (c - 1);
    int h = n - 2 * (c - 1);
    int64 answer = 0;

    memset(cw1, 0, sizeof(cw1));
    memset(cw2, 0, sizeof(cw2));
    memset(ch1, 0, sizeof(ch1));
    memset(ch2, 0, sizeof(ch2));
    memset(seq1, 0, sizeof(seq1));
    memset(seq2, 0, sizeof(seq2));
    memset(seq3, 0, sizeof(seq3));

    for (int i = wmin1; i <= w - 2; i++)
        cw1[i] = comb(w - 2, i);
    for (int i = wmin2; i <= w - 2; i++)
        cw2[i] = comb(w - 2, i);
    for (int i = hmin1; i <= h - 2; i++)
        ch1[i] = comb(h - 2, i);
    for (int i = hmin2; i <= h - 2; i++)
        ch2[i] = comb(h - 2, i);

    multiply(cw1, w - 2, cw2, w - 2, seq1);
    multiply(seq1, 2 * w - 4, ch1, h - 2, seq2);
    multiply(seq2, 2 * w + h - 6, ch2, h - 2, seq3);

    for (int i = 0; i <= min(remain, 2 * w + 2 * h - 8); i++) {
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
