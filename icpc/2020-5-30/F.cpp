#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define MOD 2015

int K;

struct Matrix {
    Matrix() {
        memset(a, 0, sizeof(a));
    }

    int a[64][64];

    auto operator*=(const Matrix &z) -> Matrix& {
        int c[64][64];
        memset(c, 0, sizeof(c));
        for (int k = 1; k <= K; k++)
        for (int i = 1; i <= K; i++)
        for (int j = 1; j <= K; j++) {
            c[i][j] = (c[i][j] + a[i][k] * z.a[k][j]) % MOD;
        }
        memcpy(a, c, sizeof(a));
        return *this;
    }
};

int n, m;

void solve() {
    scanf("%d%d", &n, &m);
    K = n + 1;

    Matrix T;
    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);
        for (int j = 0; j < c; j++) {
            int v;
            scanf("%d", &v);
            T.a[v][i] = 1;
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        T.a[n + 1][i] = 1;
    }

    Matrix R;
    for (int i = 1; i <= n + 1; i++) {
        R.a[i][i] = 1;
    }

    int p = m - 1;
    for ( ; p; p >>= 1) {
        if (p & 1)
            R *= T;
        T *= T;
    }

    int ans = 0;
    for (int i = 1; i <= n + 1; i++)
    for (int j = 1; j <= n + 1; j++) {
        ans += R.a[i][j];
        if (ans >= MOD)
            ans -= MOD;
    }

    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}