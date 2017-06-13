#pragma GCC optimize(3)

// #define NDEBUG
// #define PRETREAT_INV

#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 60
#define MOD 1000000007
#define S 1000000

typedef long long i64;

static int n, m;
static i64 G[NMAX + 1][NMAX + 1];
static i64 W[NMAX + 1][NMAX + 1];
static i64 M[NMAX + 1][NMAX + 1];

#ifdef PRETREAT_INV

static i64 invtb[S + 10];

inline i64 inv(i64 n) {
    i64 r = 1;
    while (n > S) {
        i64 d = MOD / n;
        r = r * (MOD - d) % MOD;
        n = MOD - n * d;
    }  // while

    return r * invtb[n] % MOD;
}

#else

inline void exgcd(i64 a, i64 b, i64 &m, i64 &n) {
    if (b == 0) {
        m = 1;
        n = 0;
    } else {
        i64 x, y;
        exgcd(b, a % b, x, y);
        m = y;
        n = x - a / b * y;
    }
}

inline i64 inv(i64 n) {
    i64 a, b;
    exgcd(n, MOD, a, b);
    return a < 0 ? a + MOD : a;
}

#endif  // IFDEF PRETREAT_INV

i64 det() {
    bool flag = false;
    for (size_t i = 2; i < n; i++) {
        if (M[i][i] == 0) {
            for (size_t j = i + 1; j <= n; j++) {
                if (M[j][i]) {
                    flag ^= 1;

                    for (size_t k = i; k <= n; k++) {
                        swap(M[i][k], M[j][k]);
                    }  // for

                    break;
                }  // if
            }      // for
        }          // if

        for (size_t j = i + 1; j <= n; j++) {
            i64 r = M[j][i] * inv(M[i][i]) % MOD;
            for (size_t k = i; k <= n; k++) {
                M[j][k] -= M[i][k] * r % MOD;

                if (M[j][k] < 0)
                    M[j][k] += MOD;
            }  // for
        }      // for
    }          // for

    i64 ret = 1;
    for (size_t i = 2; i <= n; i++) {
        ret = ret * M[i][i] % MOD;
    }  // for

    return flag ? MOD - ret : ret;
}

void initialize() {
#ifdef PRETREAT_INV

    invtb[1] = 1;
    for (int i = 2; i <= S; i++) {
        invtb[i] = (MOD - MOD / i) * invtb[MOD % i] % MOD;
    }  // for

#endif  // IFDEF PRETREAT_INV

    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        G[u][v] = G[v][u] = MOD - 1;
        W[u][v] = W[v][u] = w;
        G[u][u]++;
        G[v][v]++;
    }  // for
}

int main() {
#ifdef USE_FILE_IO
    freopen("random.in", "r", stdin);
    freopen("random.out", "w", stdout);
#endif  // IFDEF USE_FILE_IO
    initialize();

    i64 ans = 0, all, allinv;
    memcpy(M, G, sizeof(G));
    all = det();
    allinv = inv(all);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (W[i][j]) {
                memcpy(M, G, sizeof(G));
                M[i][j] = M[j][i] = 0;
                M[i][i]--;
                M[j][j]--;
                ans = (ans + (all - det()) * allinv % MOD * W[i][j]) % MOD;
            }
        }  // for
    }      // for

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);

    return 0;
}  // function main
