#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

static int n;
static int f[1000][1000], g[1000][1000];
static int pos[1000], val[1000];
int main() {
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        val[i] = x;
        x /= 2;
        for (int j = 1; j <= n; j++)
        for (int k = 1; k <= j; k++) {
            if (f[i - 1][k] + abs(j - x) < f[i][j]) {
                f[i][j] = f[i - 1][k] + abs(j - x);
                g[i][j] = k;
            }
        }
    }

    int ans = INT_MAX, j;
    for (int i = 1; i <= n; i++) {
        if (f[n][i] < ans) {
            j = i;
            ans = f[n][i];
        }
    }
    printf("%d\n", ans);
    pos[n] = j;
    for (int i = n - 1; i >= 1; i--) {
        j = g[i + 1][j];
        pos[i] = j;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", pos[i]);
    }
    puts("");
    int i = 1;
    for (int j = 1; j <= n; j++) {
        while (i < n && pos[i] < j) i++;
        if (pos[i] != j) printf("%d ", 2 * j - 1);
        else {
            printf("%d (", 2 * j - 1);
            while (i <= n && pos[i] == j) {
                printf("%d", val[i]);
                if (pos[i + 1] == j) printf(" ");
                i++;
            }
            printf(") ");
        }
    }
    puts("");

    return 0;
}
