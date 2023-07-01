#include <cstdio>
#include <cstdlib>

int a[2000];

int q(int i, int j) {
    printf("0 %d %d\n", i, j);
    fflush(stdout);
    int v;
    scanf("%d", &v);
    return v;
}

int main() {
    int n;
    scanf("%d", &n);
    int u = -1, v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            a[i] |= q(i, (i + 1 + j) % n);
        }
        for (int j = 0; j < i; j++) {
            if ((a[j] | a[i]) == 1023) {
                u = j;
                v = i;
                goto out;
            }
        }
    }
    abort();

out:
    for (int i = 0; i < n; i++) {
        if (i != u)
            a[i] |= q(i, u);
        if (i != v)
            a[i] |= q(i, v);
    }
    printf("1 ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    puts("");
    fflush(stdout);
    return 0;
}
