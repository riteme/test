#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

using namespace std;

constexpr int CMAX = 26;
constexpr int NMAX = 100000;

int n;
int a[NMAX + 10];
int nxt[NMAX + 10][CMAX + 1];

int maxpos(int l, int r) {
    for (int c = CMAX; c >= 1; c--) {
        if (nxt[l][c] <= r)
            return nxt[l][c];
    }
    return -1;
}

int solve(int l, int r, int u) {
    if (r < l)
        return 0;

    int m = maxpos(l, r);
    assert(l <= m && m <= r);
    int d = CMAX - (a[m] + u);
    return solve(l, m - 1, u + d) + solve(m + 1, r, u + d) + d;
}

char S[NMAX + 10];

int main() {
    scanf("%s", S + 1);
    n = strlen(S + 1);

    int ans = n * CMAX;
    for (int c = 0; c < CMAX; c++) {
        for (int i = 1; i <= n; i++) {
            int v = S[i] - 'a';
            if (v <= c)
                a[i] = CMAX - (c - v);
            else
                a[i] = v - c;
        }

        for (int i = 1; i <= CMAX; i++) {
            nxt[n + 1][i] = n + 1;
        }
        for (int i = n; i >= 1; i--) {
            memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
            nxt[i][a[i]] = i;
        }

        ans = min(ans, solve(1, n, 0));
    }
    printf("%d\n", ans);

    return 0;
}
