#include <cstdio>

int main() {
    __float128 a, b;

    while (scanf("%jf%jf", &a, &b) != EOF) {
        printf("%jf\n", a + b);
    }

    return 0;
}
