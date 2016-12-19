#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define KMAX 500
#define MOD 1000000007

typedef long long int64;

static int64 n, K;
static int64 c[KMAX * 2 + 10][KMAX * 2 + 10];;
static int64 f[KMAX + 10][10][KMAX + 10];
static int64 loop;
static int64 len[KMAX + 10];
static int64 cnt[KMAX + 10];
static int64 mod[KMAX + 10];

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

int main() {
    for (int i = 0; i <= KMAX * 2; i++)
        c[i][0] = c[i][i] = 1;
    for (int i = 1; i <= KMAX * 2; i++)
        for (int j = 1; j < i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;

    scanf("%lld%lld", &n, &K);

    int64 l = 1;
    int64 num = 1 % K;
    while (!cnt[num] && l <= n) {
        cnt[num]++;
        len[num] = l;
        mod[l] = num;
        num = (num * 10 + 1) % K;
        l++;
    }

    loop = l - 1;

    for (int64 i = 0; i < K; i++) {
        if (cnt[i]) {
            cnt[i] = (n - len[i]) / loop + 1;
        }
    }

    int64 base = mod[n % loop];
    cnt[base]--;
    f[0][0][0] = 1;
    for (int i = 1; i <= loop; i++) {
        if (cnt[mod[i]] == 0) {
            for (int j = 0; j <= 9; j++) {
                for (int k = 0; k < K; k++) {
                    f[i][j][k] = f[i - 1][j][k];
                }
            }
        } else {
    for (int j = 0; j <= 9; j++) {
    for (int k = 0; k < K; k++) {
    for (int m = 0; m <= j; m++) {
        f[i][j][k] += c[cnt[mod[i]] + m - 1][m] *
                      f[i - 1][j - m][((k - mod[i] * m) % K + K) % K] %
                      MOD;
        f[i][j][k] %= MOD;
    }}}}}

    int64 answer = 0;
    for (int j = 1; j <= 9; j++) {
        for (int m = 1; m <= j; m++) {
            answer += f[loop][j - m][((K - base * m) % K + K) % K];
            answer %= MOD;
        }
    }

    printf("%lld\n", answer);
    
    return 0;
}
