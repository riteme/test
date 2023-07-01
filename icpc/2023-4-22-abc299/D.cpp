#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    int l = 1, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2 + 1;
        printf("? %d\n", m);
        fflush(stdout);
        int v;
        scanf("%d", &v);
        if (v)
            r = m - 1;
        else
            l = m;
    }
    printf("! %d\n", l);
    return 0;
}
