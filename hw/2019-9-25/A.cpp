#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100

static int n;
static int M[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
        scanf("%d", &M[i][j]);
        M[i][j] += M[i - 1][j] + M[i][j - 1] - M[i - 1][j - 1];
    }
    int ans = -0x3f3f3f3f;
    for (int x1 = 1; x1 <= n; x1++) for (int y1 = 1; y1 <= n; y1++)
    for (int x2 = x1; x2 <= n; x2++) for (int y2 = y1; y2 <= n; y2++)
        ans = max(ans, M[x2][y2] - M[x1 - 1][y2] - M[x2][y1 - 1] + M[x1 - 1][y1 - 1]);
    printf("%d\n", ans);
    return 0;
}
