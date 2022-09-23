#include <cstdio>
#include <cassert>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 300;
constexpr int INF = 0x3f3f3f3f;

int n, m;
int a[NMAX + 10][NMAX + 10];
int b[NMAX + 10];
int L[NMAX + 10], R[NMAX + 10];
i64 ans[NMAX * NMAX + 10];
int stk[NMAX + 10], cnt;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", a[i] + j);
        }
    }

    for (int x1 = 1; x1 <= n; x1++) {
        memset(b + 1, 0x3f, sizeof(int) * m);
        for (int x2 = x1; x2 <= n; x2++) {
            b[0] = b[m + 1] = -INF;
            for (int y = 1; y <= m; y++) {
                b[y] = min(b[y], a[x2][y]);
            }

            cnt = 1;
            stk[0] = 0;
            for (int y = 1; y <= m + 1; y++) {
                while (cnt > 0 && b[stk[cnt - 1]] > b[y]) {
                    R[stk[cnt - 1]] = y;
                    cnt--;
                }

                assert(cnt > 0);
                L[y] = stk[cnt - 1];
                stk[cnt++] = y;
            }

            for (int y = 1; y <= m; y++) {
                ans[b[y]] += (y - L[y]) * (R[y] - y);
            }
        }
    }

    for (int i = 1; i <= n * m; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}