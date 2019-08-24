#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 20
#define SMAX (1 << (NMAX))
#define MOD 998244353

typedef long long i64;

static int n;
static i64 A[NMAX + 10];
static i64 S[SMAX], f[SMAX], g[SMAX], lb[SMAX];

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld", A + i);
    lb[1] = 0;
    S[1] = A[0];
    for (int s = 2; s < (1 << n); s++) {
        lb[s] = s & 1 ? 0 : lb[s >> 1] + 1;
        S[s] = S[s ^ (1 << lb[s])] + A[lb[s]];
    }
    f[0] = g[0] = 1;
    for (int s = 1; s < (1 << n); s++) {
        for (int i = lb[s], t = s; t; i = lb[t]) {
            t ^= 1 << i;
            int a = s ^ (1 << i);
            if (S[a] >= 0) add(f[s], f[a]);
            if (S[s] < 0) add(g[s], g[a]);
        }
    }
    i64 ans = 0;
    int all = (1 << n) - 1;
    for (int s = 0; s <= all; s++)
        if (S[s]) add(ans, f[s] * S[s] % MOD * g[all ^ s] % MOD);
    printf("%lld\n", ans);
    return 0;
}
