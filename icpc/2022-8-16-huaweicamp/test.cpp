#include <cstdio>

int foo(int n) {
    if (n == 0)
        return 0;
    return n + foo(n - 1);
}

int main() {
    printf("%d\n", foo(10000000));
}
