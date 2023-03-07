#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

constexpr int NMAX = 100000;
constexpr int MMAX = 10;

int n, m;
char S[NMAX + 10][MMAX + 1];
int pre[NMAX + 10], suf[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", S[i] + 1);
    }

    memset(pre, 0x3f, sizeof(pre));
    pre[1] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i - j >= 1 && S[i - j][j] == '1')
                pre[i] = min(pre[i], pre[i - j] + 1);
        }
    }

    memset(suf, 0x3f, sizeof(suf));
    suf[n] = 0;
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (i + j <= n && S[i][j] == '1')
                suf[i] = min(suf[i], suf[i + j] + 1);
        }
    }

    for (int k = 2; k < n; k++) {
        int ans = 2 * n;
        for (int i = max(1, k - m); i < k; i++) {
            for (int j = max(k + 1, i + 1); j <= n && j <= i + m; j++) {
                if (S[i][j - i] == '1')
                    ans = min(ans, pre[i] + 1 + suf[j]);
            }
        }
        if (ans > n)
            ans = -1;
        printf("%d ", ans);
    }
    puts("");

    return 0;
}
