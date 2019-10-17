#include <stdio.h>

void mulstore(long, long, long*);

int main() {
    long x, y;
    scanf("%ld%ld", &x, &y);
    long d;
    mulstore(x, y, &d);
    printf("%ld × %ld = %ld\n", x, y, d);
    return 0;
}

long mul2(long x, long y) {
    return x * y;
}