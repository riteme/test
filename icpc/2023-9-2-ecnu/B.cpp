#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100;
constexpr int INF = 0x3f3f3f3f;

int n, cnt;
int a[NMAX + 10];
int f[NMAX + 10][NMAX + 10];
int ws[NMAX * NMAX + 10];
int minw;

int w(int l, int r) {
    return a[r] - a[l - 1];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
    }
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            ws[cnt++] = w(l, r);
        }
    }
    sort(ws, ws + cnt);
    cnt = unique(ws, ws + cnt) - ws;

    int ans = INF;
    for (int i = cnt - 1; i >= 0; i--) {
        minw = ws[i];
        for (int l = n; l >= 1; l--) {
            for (int r = l; r <= n; r++) {
                f[l][r] = INF;
                if (w(l, r) < minw || w(l, r) > minw + ans)
                    continue;
                if (r == n)
                    f[l][r] = w(l, r);
                for (int r2 = r + 1; r2 <= n; r2++) {
                    f[l][r] = min(f[l][r], max(w(l, r), f[r + 1][r2]));
                }
            }
        }
        for (int r = 1; r < n; r++) {
            ans = min(ans, f[1][r] - minw);
        }
    }

    printf("%d\n", ans);
    return 0;
}
