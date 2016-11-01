#include <cstdio>

int main() {
    int n, v;
    scanf("%d%d", &n, &v);

    int a = 1, b = 1;
    for (int i = 2; i <= n; i++) {
        int u;
        scanf("%d", &u);

        if (u > v)
            a = b + 1;
        else if (u < v)
            b = a + 1;

        v = u;
    }

    printf("%d\n", a > b ? a : b);

    return 0;
}
