#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 500
#define MOD 998244353
#define INV2 499122177

static int n, S[NMAX + 10][NMAX + 10];
static i64 G[NMAX + 10][NMAX + 10];
static bool m1[NMAX + 10], m2[NMAX + 10];

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        i64 sum = 0;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
            scanf("%lld", &G[i][j]);
            add(sum, G[i][j] % MOD);
        }
        for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
            if (G[i][j] > G[i][k] + G[k][j]) G[i][j] = G[i][k] + G[k][j];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) S[i][j] = j;
            sort(S[i] + 1, S[i] + n + 1, [i](int x, int y) {
                return G[i][x] < G[i][y];
            });
        }

        i64 ans = 0, d;
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
            memset(m1, 0, sizeof(m1));
            memset(m2, 0, sizeof(m2));
            for (int k = 1; k <= n; k++) {
                if (G[i][k] < G[j][k]) m2[k] = true;
                else m1[k] = true;
            }
            int p = 1, q = 1;
            for (int k = 1; k <= n; k++) {
                while (p <= n && m1[S[i][p]]) p++;
                while (q <= n && m2[S[j][q]]) q++;

                if (p <= n && q <= n) {
                    i64 id = G[i][S[i][p]], jd = G[j][S[j][q]];
                    if (id < jd) {
                        d = id;
                        p++;
                    } else {
                        d = jd;
                        q++;
                    }
                } else if (p <= n)
                    d = G[i][S[i][p++]];
                else
                    d = G[j][S[j][q++]];
                add(ans, d % MOD * (n - k) % MOD);
            }
        }
        i64 m = n * (n - 1) / 2;
        add(ans, sum * (m - 1) % MOD * INV2 % MOD);
        printf("%lld\n", ans);
    }

    return 0;
}
