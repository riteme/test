#include <stdio.h>
#include <string.h>

typedef long long i64;

static union {
    i64 a[3];
    char c[20];
} A1, A2;

static struct {
    i64 a1, a2, a3;
    char *p;
} B1, B2;

static char C1[100], C2[100];

i64 f() {
    A2.a[0] = A1.a[0];
    A2.a[1] = A1.a[1];
    A2.a[2] = A1.a[2];
    return A2.a[0] + A2.a[1] + A2.a[2];
}

i64 g() {
    B2.a1 = B1.a1;
    B2.a2 = B1.a2;
    B2.a3 = B1.a3;
    return B2.a1 + B2.a2 + B2.a3;
}

i64 h() {
    memcpy(C2, C1, sizeof(C2));
    return C2[4] + C2[17] + C2[78];
}

int main() {
    struct A {
        int a, b, c;
    } a;
    struct B {
        int a, b;
        char c;
    } b;
    printf("%zu %zu \n", sizeof(a), sizeof(b));
    return 0;
}
