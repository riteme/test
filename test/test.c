#include <stdio.h>

int main() {
    long a, b;
    scanf("%ld%ld", &a, &b);
    if ((a + b) > 2147483647 || (a + b) < -2147483648) puts("YES");
    else puts("NO");
    return 0;
}
