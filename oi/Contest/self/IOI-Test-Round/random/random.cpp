#pragma GCC optimize(3)

// #define NDEBUG
#define PRETREAT_INV

#include <cassert>
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
static bool marked[NMAX + 10];
static i64 G[NMAX + 1][NMAX + 1];
static i64 W[NMAX + 1][NMAX + 1];
static i64 M[NMAX + 1][NMAX + 1];

#ifdef PRETREAT_INV

static i64 invtb[S + 10];

inline i64 inv(i64 n) {
    assert(n);

    i64 r = 1;
    while (n > S) {
        i64 d = MOD / n;
        r = r * (MOD - d) % MOD;
        n = MOD - n * d;
    }  // while

    return r * invtb[n] % MOD;
}

#else

inline i64 inv(i64 n) {
    assert(n);
    return n <= 1 ? n : (MOD - MOD / n) * inv(MOD % n) % MOD;
}

#endif  // IFDEF PRETREAT_INV

i64 det() {
    bool flag = false;
    for (size_t i = 2; i < n; i++) {
        if (M[i][i] == 0) {
            size_t j;
            for (j = i + 1; j <= n; j++) {
                if (M[j][i]) {
                    flag ^= 1;

                    for (size_t k = i; k <= n; k++) {
                        swap(M[i][k], M[j][k]);
                    }  // for

                    break;
                }  // if
            }      // for

            if (j > n)
                return 0;
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

void dfs(int x) {
    marked[x] = true;

    for (int y = 1; y <= n; y++) {
        if (G[x][y] && !marked[y])
            dfs(y);
    }
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

    dfs(1);
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        flag &= marked[i];
    }

    if (!flag) {
        puts("0");
        return 0;
    }

    i64 ans = 0, all, allinv;
    memcpy(M, G, sizeof(G));
    all = det();
    assert(all);
    allinv = inv(all);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (W[i][j]) {
                memcpy(M, G, sizeof(G));
                M[i][j] = M[j][i] = 0;
                M[i][i]--;
                M[j][j]--;
                ans = (ans + (all - det()) * W[i][j]) % MOD;
            }
        }  // for
    }      // for

    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans * allinv % MOD);

    return 0;
}  // function main
