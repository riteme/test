#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;
constexpr int SMAX = 28;
constexpr int INF = 0x3f3f3f3f;

int n, m;
char s[NMAX + 10], t[NMAX + 10];
int nxt[NMAX + 10][SMAX + 10];

int main() {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    for (int i = 1; i <= n; i++) {
        s[i] = s[i] - 'a' + 2;
    }
    for (int i = 1; i <= m; i++) {
        t[i] = t[i] - 'a' + 2;
    }
    n++;
    m++;
    s[n] = 1;
    t[m] = 0;
    for (int c = 0; c < SMAX; c++) {
        nxt[n][c] = INF;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int c = 0; c < SMAX; c++) {
            nxt[i][c] = nxt[i + 1][c];
        }
        nxt[i][(int)s[i + 1]] = i + 1;
    }
    int ans = INF;
    for (int c = 0; c < t[1]; c++) {
        ans = min(ans, nxt[0][c] - 1);
    }
    int i = 1;
    for (int j = 1; j < m; i++, j++) {
        while (i <= n && s[i] != t[j]) {
            i++;
        }
        if (i > n)
            break;
        int mi = INF;
        for (int c = 0; c < t[j + 1]; c++) {
            mi = min(mi, nxt[i][c] - i - 1);
        }
        ans = min(ans, i - j + mi);
    }
    printf("%d\n", ans);
    return 0;
}
