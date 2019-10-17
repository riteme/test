// #include <stdio.h>

// long mul2(long x, long y) {
//     return x * y;
// }

long mul2(long, long);

void mulstore(long x, long y, long *dest) {
    long t = mul2(x, y);
    *dest = t;
}

// int main() {
//     long x, y;
//     scanf("%ld%ld", &x, &y);
//     long z;
//     mulstore(x, y, &z);
//     printf("%ld\n", z);
//     return 0;
// }