#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10000

static int n;
static int p[NMAX + 10], c[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", p + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", c + i);
    int cnt = 1;
    for (int i = 2; i <= n; i++)
        cnt += c[i] != c[p[i]];
    printf("%d\n", cnt);
    return 0;
}
