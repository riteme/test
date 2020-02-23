#include <cstdio>

#define NMAX 10000

int n;
int a[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    bool ok = true;
    for (int i = 2; i <= n; i++)
        ok &= a[1] >= a[i];
    puts(ok ? "S" : "N");
    return 0;
}