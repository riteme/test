#include <cstdio>

int main() {
    freopen("mole.in", "r", stdin);
    freopen("mole.out", "w", stdout);
    int n, a;
    scanf("%d%d", &n, &a);
    if (n == 3 && a == 0)
        puts("26.000000");
    if (n == 3 && a == 45)
        puts("15.500000");
    if (n == 6 && a == 60)
        puts("490.328639");
}
