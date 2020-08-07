#include <stdio.h>

int tmult_ok(long x, long y, long *dst);

int main() {
    long x, y, z;
    while (scanf("%ld%ld", &x, &y) != EOF) {
        int p = tmult_ok(x, y, &z);
        printf("z = %ld, p = %d\n", z, p);
    }

    return 0;
}
