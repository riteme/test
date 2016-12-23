#pragma comment(linker, "/STACK:102400000,102400000")

#include <stdio.h>
#include <stdlib.h>

typedef long double float128;

float128 recursive(int n) {
    if (n <= 0)
        return rand();
    float128 a = recursive(n - 1);
    float128 b = a * a;
    float128 c = b * b + a * b;
    return a + b + c + (rand() ^ n);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%Lf\n", recursive(n));

    return 0;
}
