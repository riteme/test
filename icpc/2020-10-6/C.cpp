#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 300;
constexpr i64 MOD = 1000000007;

enum Type : int {
    LEFT = 1,
    RIGHT = 2,
    BOTH = 3
};

int n, A[NMAX + 10];
bool G[NMAX + 10][NMAX + 10];
i64 f[NMAX + 10][NMAX + 10][4];

int wrap(int x) {
    while (x > n)
        x -= n;
    while (x < 1)
        x += n;
    return x;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
    }
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        int d = __gcd(A[i], A[j]);
        G[i][j] = G[j][i] = d > 1;
    }

    for (int i = 1; i <= n; i++) {
        f[i][i][LEFT] = f[i][i][RIGHT] = 1;
    }

    for (int s = 1; s < n; s++)
    for (int i = 1; i <= n; i++)
    for (int m = BOTH; m >= LEFT; m--) {
        int j = wrap(i + s);

        i64 &v = f[i][j][m];
        if (m == LEFT) {
            for (int k = j; k != i; k = wrap(k - 1)) {
                if (G[i][k])
                    v = (v + f[k][j][LEFT] * f[i][k][BOTH]) % MOD;
            }
        } else if (m == RIGHT) {
            for (int k = i; k != j; k = wrap(k + 1)) {
                if (G[j][k])
                    v = (v + f[i][k][RIGHT] * f[k][j][BOTH]) % MOD;
            }
        } else {
            for (int k = i; k != j; k = wrap(k + 1)) {
                v = (v + f[i][k][LEFT] * f[wrap(k + 1)][j][RIGHT]) % MOD;
            }
        }
    }

    i64 ans = 0;
    for (int k = 2; k <= n; k++) {
        if (G[1][k])
            ans = (ans + f[2][k][RIGHT] * f[k][1][BOTH]) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}
