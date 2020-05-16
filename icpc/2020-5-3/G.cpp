#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define M1 998244353
#define M2 1000000007
#define BASE 19260817
#define INF 0x3f3f3f3f

struct Hash {
    i64 h1 = 0, h2 = 0;

    Hash &operator+=(i64 v) {
        h1 += v;
        h2 += v;
        if (h1 >= M1)
            h1 -= M1;
        if (h2 >= M2)
            h2 -= M2;
        return *this;
    }

    Hash operator-(const Hash &z) const {
        i64 g1 = h1 - z.h1;
        i64 g2 = h2 - z.h2;
        if (g1 < 0)
            g1 += M1;
        if (g2 < 0)
            g2 += M2;
        return {g1, g2};
    }

    Hash &operator*=(i64 v) {
        h1 = h1 * v % M1;
        h2 = h2 * v % M2;
        return *this;
    }

    Hash operator*(i64 v) const {
        return {h1 * v % M1, h2 * v % M2};
    }

    Hash operator*(const Hash &z) const {
        return {h1 * z.h1 % M1, h2 * z.h2 % M2};
    }

    bool operator==(const Hash &z) const {
        return h1 == z.h1 && h2 == z.h2;
    }
};

#define NMAX 500
#define MMAX 1100000

int n, K, m, cnt, L;
char s[MMAX + 10], buf[MMAX + 10];
int len[MMAX + 10];
Hash Hs[MMAX + 10];
Hash H[MMAX + 10], pw[MMAX + 10];

void initialize() {
    pw[0] += 1;
    for (int i = 1; i <= MMAX; i++)
        pw[i] = pw[i - 1] * BASE;

    scanf("%s%d", s + 1, &cnt);
    n = strlen(s + 1);
    for (int i = 1; i <= cnt; i++) {
        scanf("%s", buf);
        len[i] = strlen(buf);
        m = max(m, len[i]);
        for (int j = 0; buf[j]; j++) {
            H[i] *= BASE;
            H[i] += buf[j];
        }
    }
}

Hash get(int l, int r) {
    return Hs[r] - Hs[l - 1] * pw[r - l + 1];
}

void border() {
    L = n + m;
    for (int i = n + 1; i <= L; i++)
        s[i] = s[i - n];
    for (int i = 1; i <= L; i++) {
        Hs[i] = Hs[i - 1] * BASE;
        Hs[i] += s[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        K = n - i;
        if (n % K == 0 && get(1, i) == get(n - i + 1, n))
            break;
    }
}

i64 G[NMAX + 10][NMAX + 10], W[NMAX + 10][NMAX + 10];

int main() {
    initialize();
    border();
    // fprintf(stderr, "K = %d", K);

    for (int i = 1; i <= K; i++)
    for (int j = 1; j <= K; j++)
        G[i][j] = INF;

    for (int i = 1; i <= K; i++)
    for (int k = 1; k <= cnt; k++) {
        int j = (i + len[k] - 1) % K + 1;
        if (H[k] == get(i + 1, i + len[k]))
            G[i][j] = 1;
    }
    // for (int i = 1; i <= K; i++)
    //     G[i][i] = 0;
    memcpy(W, G, sizeof(W));

    i64 ans = INF;
    for (int k = 1; k <= K; k++) {
        // for (int i = 1; i <= K; i++)
        // for (int j = 1; j <= K; j++)
        // if (i != k && j != k)
        //     ans = min(ans, W[i][j] + G[j][k] + G[k][i]);
        for (int i = 1; i <= K; i++)
        for (int j = 1; j <= K; j++)
            W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
    }

    for (int i = 1; i <= K; i++)
        ans = min(ans, W[i][i]);

    if (ans == INF)
        ans = -1;
    printf("%lld\n", ans);
    return 0;
}