#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, K;
static char s[NMAX + 10];

int main() {
    scanf("%d%d%s", &n, &K, s + 1);
    int m = unique(s + 1, s + n + 1) - s - 1;
    int ans = n - m;
    int c = (m + 1) / 2 - 1;
    ans += 2 * min(c, K);
    if (K > c && !(m & 1)) ans++;
    printf("%d\n", ans);
    return 0;
}
