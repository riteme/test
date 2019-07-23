#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 500
#define MMAX 1000000
#define MOD 998244353

typedef long long i64;

static int n, m;
static int c[MMAX + 10];
static int L[NMAX + 10], R[NMAX + 10];
static bool taken[NMAX + 10];
static vector<int> ch[NMAX + 10];

inline bool intersect(int l1, int r1, int l2, int r2) {
    return (l1 <= l2 && l2 <= r1 && r2 > r1) ||
           (l1 <= r2 && r2 <= r1 && l2 < l1);
}

inline bool contain(int l1, int r1, int l2, int r2) {
    return l1 <= l2 && r2 <= r1;
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

static i64 dp[NMAX + 10][NMAX + 10];

i64 eval(int x) {
    i64 ret = 1;
    for (int v : ch[x]) ret = ret * eval(v) % MOD;
    for (int i = 0, j = 0; i < ch[x].size(); j = i = j + 1) {
        while (j + 1 < ch[x].size() && R[ch[x][j]] + 1 == L[ch[x][j + 1]]) j++;
        for (int k = i; k <= j; k++) dp[k][k] = 1;
        for (int z = 2; i + z <= j + 1; z++) for (int l = i; l + z <= j + 1; l++) {
            int r = l + z - 1, mi = l;
            for (int k = l + 1; k <= r; k++)
                if (ch[x][k] < ch[x][mi]) mi = k;
            i64 s1 = l < mi ? 2 * dp[l][mi - 1] % MOD : 1;
            i64 s2 = mi < r ? 2 * dp[mi + 1][r] % MOD : 1;
            for (int k = l + 1; k < mi; k++) add(s1, dp[l][k - 1] * dp[k][mi - 1] % MOD);
            for (int k = mi + 1; k < r; k++) add(s2, dp[mi + 1][k] * dp[k + 1][r] % MOD);
            dp[l][r] = s1 * s2 % MOD;
        }
        ret = ret * dp[i][j] % MOD;
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d", c + i);
    L[0] = 1; R[0] = m;
    for (int i = 1; i <= m; i++) {
        if (!L[c[i]]) L[c[i]] = i;
        R[c[i]] = i;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = L[i]; j <= R[i]; j++)
            if (c[j] < i) return puts("0"), 0;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j <= n; j++)
            if (!taken[j] && contain(L[i], R[i], L[j], R[j])) {
                ch[i].push_back(j);
                taken[j] = true;
            }
        sort(ch[i].begin(), ch[i].end(), [](int x, int y) {
            return L[x] < L[y];
        });
    }
    printf("%lld\n", eval(0));
    return 0;
}
