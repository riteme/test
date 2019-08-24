#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 3000
#define MOD 1000000007

typedef long long i64;

inline i64 qpow(i64 a, i64 k) {
    i64 r = 1;
    for ( ; k; k >>= 1, a = a * a % MOD)
        if (k & 1) r = r * a % MOD;
    return r;
}

inline i64 inv(i64 x) {
    return qpow(x, MOD - 2);
}

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

static i64 C[NMAX + 10][NMAX + 10];
static i64 fac[NMAX + 10], fi[NMAX + 10];

static int n, K, seq[NMAX + 10];
static vector<int> T[NMAX + 10];
static int s[NMAX + 10], fa[NMAX + 10];
static i64 dp[NMAX + 10];
static int v[NMAX + 10], a[NMAX + 10], m;
static int buc[NMAX + 10], cnt[NMAX + 10];

inline void bsort() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < m; i++) cnt[a[i]]++;
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < m; i++) buc[--cnt[a[i]]] = a[i];
    memcpy(a, buc, sizeof(int) * m);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < m; i++) cnt[v[a[i]]]++;
    for (int i = n - 1; i; i--) cnt[i] += cnt[i + 1];
    for (int i = 0; i < m; i++) buc[--cnt[v[a[i]]]] = a[i];
    memcpy(a, buc, sizeof(int) * m);
}

void build(int x) {
    dp[x] = s[x] = 1;
    for (int i = K * x - K + 2; i <= K * x + 1 && i <= n; i++) {
        build(i);
        T[x].push_back(i);
        fa[i] = x;
        s[x] += s[i];
        dp[x] = dp[x] * dp[i] % MOD * fi[s[i]] % MOD;
    }
    dp[x] = dp[x] * fac[s[x] - 1] % MOD;
}

int main() {
    for (int i = 0; i <= NMAX; i++) C[i][0] = 1;
    for (int i = 1; i <= NMAX; i++) for (int j = 1; j <= NMAX; j++)
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    fac[0] = 1;
    for (int i = 1; i <= NMAX; i++) fac[i] = fac[i - 1] * i % MOD;
    fi[NMAX] = inv(fac[NMAX]);
    for (int i = NMAX - 1; i >= 0; i--) fi[i] = fi[i + 1] * (i + 1) % MOD;
    int cas;
    scanf("%d", &cas);
    for (int _i = 1; _i <= cas; _i++) {
        printf("Case #%d: ", _i);
        scanf("%d%d", &n, &K);
        for (int i = 1; i <= n; i++) {
            scanf("%d", seq + i);
            T[i].clear();
        }
        build(1);
        i64 ans = 0;
        v[1] = 1;
        for (int i = 2; i <= n; i++) {
            a[m = 1, 0] = i;
            v[i] = seq[i];
            for (int j = 1; j < i; j++) a[m++] = j;
            for (int j = fa[i]; j < i; j++) for (int x : T[j]) if (x > i) {
                v[x] = seq[j];
                a[m++] = x;
            }
            bsort();
            //sort(a, a + m, [](int x, int y) {
            //    return v[x] > v[y] || (v[x] == v[y] && x > y);
            //});
            int sum = 0;
            i64 ret = 1;
            for (int j = 0; j < m; j++) {
                int x = a[j];
                if (x < i) sum++;
                else {
                    assert(n - v[x] - sum >= 0);
                    ret = ret * dp[x] % MOD * C[n - v[x] - sum][s[x]] % MOD;
                    sum += s[x];
                }
            }
            add(ans, ret);
        }
        ans = (dp[1] - ans + MOD) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
