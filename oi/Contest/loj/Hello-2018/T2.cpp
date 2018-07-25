#include <cstdio>
#include <cstring>

static int sa[200000], rk[200000];

int main() {
    int n;
    scanf("%d", &n);

    printf("%d\n", n + 1);

    int p = 1;
    for (int i = n; i > 0; i -= 2)
        sa[p++] = i;
    for (int i = (n & 1 ? 2 : 1); i <= n + 1; i += 2)
        sa[p++] = i;
    for (int i = 1; i <= n + 1; i++)
        rk[sa[i]] = i;
    for (int i = 1; i <= n + 1; i++)
        printf("%d ", rk[i]);

    return 0;
}
