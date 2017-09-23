#include <cstdio>

int fac(int n) {
    if (n == 0)
        return 1;
    return fac(n - 1) * n;
}

int main() {
    int n;
    scanf("%d", &n);
    n = fac(n);
    
    for (unsigned i = n; i >= 0; i--) {
        puts("Aha!");
    }

    return 0;
}
