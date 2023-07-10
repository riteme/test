#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 6000;
constexpr int Z = 3005;
constexpr i64 MOD = 998244353;

int n;
char s[NMAX + 10];
i64 f[NMAX + 10][NMAX + 10];
i64 g[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);

    g[0][Z] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = Z - n; j <= Z + n; j++) {
            if (s[i] == '+' || s[i] == '?') {
                // As lparen
                if (j >= Z) {
                    f[i][j + 1] = (f[i][j + 1] + f[i - 1][j] + (MOD - i) * g[i - 1][j]) % MOD;
                    g[i][j + 1] = (g[i][j + 1] + g[i - 1][j]) % MOD;
                }

                // As rparen
                if (j < Z) {
                    f[i][j + 1] = (f[i][j + 1] + f[i - 1][j] + i * g[i - 1][j]) % MOD;
                    g[i][j + 1] = (g[i][j + 1] + g[i - 1][j]) % MOD;
                }
            }

            if (s[i] == '-' || s[i] == '?') {
                // As lparen
                if (j <= Z) {
                    f[i][j - 1] = (f[i][j - 1] + f[i - 1][j] + (MOD - i) * g[i - 1][j]) % MOD;
                    g[i][j - 1] = (g[i][j - 1] + g[i - 1][j]) % MOD;
                }

                // As rparen
                if (j > Z) {
                    f[i][j - 1] = (f[i][j - 1] + f[i - 1][j] + i * g[i - 1][j]) % MOD;
                    g[i][j - 1] = (g[i][j - 1] + g[i - 1][j]) % MOD;
                }
            }
        }
    }

    i64 ans = f[2 * n][Z];
    printf("%lld\n", ans);
    return 0;
}
