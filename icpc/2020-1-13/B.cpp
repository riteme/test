#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b;
        scanf("%d%d", &a, &b);
        puts(a == b ? "YES" : "NO");
    }
    return 0;
}