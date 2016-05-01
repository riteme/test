#include <cstdio>
#include <cstring>
#include <algorithm>

using std::swap;

#define MOD 1000000007

static int a1[1000010];
static int a2[1000010];
static int *current = a1;
static int *prev = a2;

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    prev[1] = 1;
    for (int i = 1; i <= m; i++) {
        memset(current, 0, sizeof(a1));

        for (int j = 1; j <= n; j++) {
            current[j] = current[j - 1] + prev[j];
            current[j] %= MOD;
        }  // for

        for (int k = 1; k <= n; k++) {
            printf("%d ", current[k]);
        }  // for
        putchar('\n');

        swap(current, prev);
    }  // for

    printf("%d", prev[n]);

    return 0;
}
