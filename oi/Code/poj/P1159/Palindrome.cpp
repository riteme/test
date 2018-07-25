#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

static int n;
static char s[5010];
static char rs[5010];
static int f1[5010];
static int f2[5010];

int main() {
    scanf("%d\n%s", &n, s);

    for (char *i = s, *j = rs + n - 1; i != s + n; i++, j--) { *j = *i; }

    memset(f1, 0, sizeof(f1));
    memset(f2, 0, sizeof(f2));
    int *up = f1;
    int *down = f2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            down[j] = max(max(up[j], down[j - 1]),
                          up[j - 1] + (s[i - 1] == rs[j - 1] ? 1 : 0));
        }

        swap(up, down);
    }

    printf("%d", n - up[n]);
}
