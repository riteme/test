#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 40
#define MOD 1011110011

typedef long long i64;

static int n, K, T;
static i64 ans;
static int cnt[NMAX + 10];
static i64 f[NMAX + 10][NMAX + 10];

i64 c(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return (c(n - 1, k) + c(n - 1, k - 1)) % MOD;
}

i64 qpow(i64 a, i64 b) {
    i64 r = 1;
    for (; b; a = a * a % MOD, b >>= 1) {
        if (b & 1)
            r = r * a % MOD;
    }

    return r;
}

void initialize() {
    scanf("%d%d%d", &n, &K, &T);
}

void dfs(int i) {
    if (i > K) {
        ans++;
        return;
    }

    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            bool flag = false;
            for (int k = l; k <= r; k++) {
                if (cnt[k] == T) {
                    flag = true;
                    break;
                }
            }

            if (flag)
                continue;

            for (int k = l; k <= r; k++) {
                cnt[k]++;
            }

            dfs(i + 1);

            for (int k = l; k <= r; k++) {
                cnt[k]--;
            }
        }
    }
}

int main() {
    freopen("container.in", "r", stdin);
    freopen("container.out", "w", stdout);
    initialize();

    if (T == 1) {
        f[0][0] = 1;
        for (int i = 1; i <= K; i++) {
            for (int j = 1; j <= n; j++) {
                i64 pre = 0;
                for (int k = 0; k < j; k++) {
                    pre += f[i - 1][k];
                    pre %= MOD;
                    f[i][j] += pre * i;
                    f[i][j] %= MOD;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            ans += f[K][i];
            ans %= MOD;
        }
    } else if (T == K)
        ans = qpow(n * (n + 1) / 2, K);
    else
        dfs(1);

    printf("%lld\n", ans);

    return 0;
}
