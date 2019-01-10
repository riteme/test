#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 300
#define BASE 19260817

typedef long long i64;
typedef unsigned long long u64;

static u64 B[32];

inline u64 hash(const int cnt[32]) {
    u64 r = 0;
    for (int i = 0; i < 26; i++) r += cnt[i] * B[i];
    return r;
}

inline int odd(const int cnt[32]) {
    int r = 0;
    for (int i = 0; i < 26; i++) r += cnt[i] & 1;
    return r;
}

static int n, m, cnt[32], p;
static char M[NMAX + 10][NMAX + 10];
static u64 str[NMAX + 10], s[NMAX * 3 + 10];
static int r[NMAX * 3 + 10];

i64 eval() {
    for (int i = 1; i < p; i++) {
        s[2 * i - 1] = '#';
        s[2 * i] = str[i];
    }
    p = 2 * p - 1;
    s[p] = '#';
    s[p + 1] = '$';
    i64 ret = 0;
    int c = 1, R = 1;
    r[1] = 0;
    for (int i = 2; i <= p; i++) {
        if (i <= R) r[i] = min(R - i, r[2 * c - i]);
        else r[i] = 0;
        for (; s[i + r[i] + 1] == s[i - r[i] - 1]; r[i]++) ;
        if (i + r[i] > R) {
            c = i;
            R = i + r[i];
        }
        if (s[i] == '#') ret += (r[i] + 1) / 2;
        else ret += 1 + r[i] / 2;
    }
    return ret;
}

int main() {
    B[0] = BASE;
    for (int i = 1; i < 32; i++) B[i] = B[i - 1] * BASE;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", M[i] + 1);

    i64 ans = 0;
    for (int l = 1; l <= m; l++) for (int r = l; r <= m; r++) {
        p = 1;
        for (int i = 1; i <= n; i++) {
            memset(cnt, 0, sizeof(cnt));
            for (int j = l; j <= r; j++) cnt[M[i][j] - 'a']++;
            int c = odd(cnt);
            if ((((r - l) & 1) && c != 0) ||
                (((r - l) & 1) == 0 && c != 1)) {
                str[p] = 0;
                ans += eval();
                p = 1;
            } else str[p++] = hash(cnt);
        }
        str[p] = 0;
        ans += eval();
    }
    printf("%lld\n", ans);
    return 0;
}
