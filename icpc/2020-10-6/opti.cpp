#pragma GCC optimize(0)

#include <cstdio>

int main() {
    int s = 0;
    for (long long i = 0; i < 1000000000L; i++) {
        s += i;
    }
    printf("%d\n", s);
    return 0;
}
