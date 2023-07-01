#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 100;
constexpr int CMAX = 26;
constexpr int MOD = 998244353;

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int n;
char s[NMAX + 10];
int nxt[NMAX + 10][CMAX];
int f[NMAX + 10][NMAX + 10][NMAX + 10];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int c = 0; c < CMAX; c++) {
        nxt[n][c] = n + 1;
    }
    s[n] -= 'a';
    for (int i = n - 1; i >= 0; i--) {
        memcpy(nxt[i], nxt[i + 1], sizeof(nxt[i]));
        s[i] -= 'a';
        nxt[i][s[i + 1]] = i + 1;
    }
    for (int i = 1; i <= n; i++) {
        f[i][0][i] = 1;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                for (int c = 0; c < CMAX; c++) {
                    int nj = nxt[j][c];
                    int nk = nxt[k][c];
                    if (nj <= i)
                        add(f[i][nj][nk], f[i][j][k]);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n; k++) {
            add(ans, f[i][i][k]);
        }
    }
    printf("%d\n", ans);

    return 0;
}
