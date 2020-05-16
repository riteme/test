#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100
#define LMAX 30
#define INF 0x3f3f3f3f3f3f3f3f

int n, L;
i64 w[NMAX + 10];
int s[NMAX + 10];

i64 f[LMAX + 10][NMAX + 10][NMAX + 10];

struct state {
    int d, i, c;

    bool operator!=(const state &z) const {
        return d != z.d || i != z.i || c != z.c;
    }
};

state g[LMAX + 10][NMAX + 10][NMAX + 10];
int dep[NMAX + 10];

void solve() {
    for (int i = 1; i <= n; i++)
        s[i] = i;
    sort(s + 1, s + n + 1, [](int i, int j) {
        return w[i] > w[j];
    });

    memset(f, 0x3f, sizeof(f));
    f[1][0][min(n, 2)] = 0;
    for (int d = 0; d <= L; d++)
    for (int i = 0; i <= n; i++)
    for (int c = n; c >= 0; c--)
    if (i + c <= n && f[d][i][c] < INF) {
        int nc = min(c * 2, n);
        if (d < L && f[d][i][c] < f[d + 1][i][nc]) {
            f[d + 1][i][nc] = f[d][i][c];
            g[d + 1][i][nc] = {d, i, c};
        }

        i64 nw = f[d][i][c] + w[s[i + 1]] * d;
        if (i < n && c > 0 && nw < f[d][i + 1][c - 1]) {
            f[d][i + 1][c - 1] = nw;
            g[d][i + 1][c - 1] = {d, i, c};
        }
    }

    i64 ans = INF;
    int mc;
    for (int c = 0; c <= n; c++)
    if (f[L][n][c] < ans) {
        ans = f[L][n][c];
        mc = c;
    }

    printf("%lld\n", ans);
    for (state x = {L, n, mc}, y; x != state{0, 0, 0}; x = y) {
        y = g[x.d][x.i][x.c];
        if (y.i < x.i)
            dep[s[x.i]] = y.d;
        x = y;
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", dep[i]);
    puts("");
}

int main() {
    while (scanf("%d%d", &n, &L) != EOF) {
        if (n ==0 && L == 0)
            break;
        for (int i = 1; i <= n; i++)
            scanf("%lld", w + i);
        solve();
    }

    return 0;
}