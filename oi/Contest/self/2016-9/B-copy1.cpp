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

static int64 evaluate(int wmin1, int wmin2, int hmin1, int hmin2, int remain) {
    int w = m - 2 * (c - 1);
    int h = n - 2 * (c - 1);
    int64 answer = 0;

    for (int i = wmin1; i <= w - 2; i++) {
        for (int j = wmin2; j <= w - 2; j++) {
            for (int k = hmin1; k <= h - 2; k++) {
                for (int l = hmin2; l <= h - 2; l++) {
                    if (i + j + k + l > remain)
                        continue;

                    int64 cw1 = comb(w - 2, i);
                    int64 cw2 = comb(w - 2, j);
                    int64 ch1 = comb(h - 2, k);
                    int64 ch2 = comb(h - 2, l);
                    int64 others =
                        comb(n * m - 2 * w - 2 * h + 4, remain - i - j - k - l);

                    answer += ((cw1 * cw2 % MOD) * (ch1 * ch2 % MOD) % MOD) *
                              others % MOD;
                    answer %= MOD;
                }  // for
            }      // for
        }          // for
    }              // for

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
