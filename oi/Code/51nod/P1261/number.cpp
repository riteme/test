#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define KMAX 500
#define MOD 1000000007

typedef long long int64;

inline int64 quick_pow(int64 a, int64 b) {
    int64 r = 1;

    while (b) {
        if (b & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return r;
}

static int64 n, K;
static int64 f[2][10][KMAX + 10];
static int64 gcnt;
static int64 from, to, looplen;
static int64 len[KMAX + 10];
static int64 cnt[KMAX + 10];
static int64 mod[KMAX + 10];
static int64 inv[KMAX + 10];

int main() {
    for (int i = 1; i <= KMAX; i++)
        inv[i] = quick_pow(i, MOD - 2);

    scanf("%lld%lld", &n, &K);

    int64 l = 1;
    int64 num = 1 % K;
    while (!cnt[num]) {
        cnt[num]++;
        len[num] = l;
        mod[l] = num;
        num = (num * 10 + 1) % K;
        l++;
    }

    gcnt = min(n, l - 1);
    from = len[num];
    to = l - 1;
    looplen = to - from + 1;

    for (int64 i = 0; i < K; i++) {
        if (cnt[i]) {
            if (len[i] <= n && len[i] >= from)
                cnt[i] += (n - len[i]) / looplen;
            else if (len[i] > n)
                cnt[i] = 0;
        }
    }

    int64 base;

    if (n < from)
        base = mod[n];
    else
        base = mod[(n - from) % looplen + from];

    cnt[base]--;
    f[0][0][0] = 1;
    int current = 1, last = 0;
    for (int i = 1; i <= gcnt; i++) {
        if (cnt[mod[i]] == 0) {
            for (int j = 0; j <= 9; j++) {
                for (int k = 0; k < K; k++) {
                    f[current][j][k] = f[last][j][k];
                }
            }
        } else {
    for (int j = 0; j <= 9; j++) {
    for (int k = 0; k < K; k++) {
    f[current][j][k] = 0;

    int64 X = cnt[mod[i]] % MOD;
    int64 comb = 1;
    for (int m = 0; m <= j; m++) {
        f[current][j][k] += comb *
                      f[last][j - m][((k - mod[i] * m) % K + K) % K] %
                      MOD;
        f[current][j][k] %= MOD;
        comb = (comb * (X + m) % MOD) * inv[m + 1] % MOD;
    }

    }}}

        swap(current, last);
    }

    int64 answer = 0;
    for (int j = 1; j <= 9; j++) {
        for (int m = 1; m <= j; m++) {
            answer += f[last][j - m][((K - base * m) % K + K) % K];
            answer %= MOD;
        }
    }

    if (answer < 0)
        answer += MOD;

    printf("%lld\n", answer);
    
    return 0;
}
