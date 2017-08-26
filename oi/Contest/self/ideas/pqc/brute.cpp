#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

int p(int n, int m) {
    if (m == 0)
        return n == 0;
    if (n < 0)
        return 0;

    return p(n, m - 1) + p(n - m, m - 1);
}

int c(int n, int m) {
    if (m == 0)
        return n == 0;
    if (n < 0)
        return 0;

    return c(n, m - 1) - c(n - m, m - 1);
}

int q(int n, int m) {
    if (m == 0)
        return n == 0;
    if (n < 0)
        return 0;

    int r = 0;
    do {
        r += q(n, m - 1);
        n -= m;
    } while (n >= 0);

    return r;
}

int main() {
    int n;
    scanf("%d", &n);

    printf("i: ");
    for (int i = 0; i <= n; i++) {
        printf("%3d ", i);
    }
    puts("");

    printf("q: ");
    for (int i = 0; i <= n; i++) {
        printf("%3d ", q(i, i));
    }
    puts("");

    printf("p: ");
    for (int i = 0; i <= n; i++) {
        printf("%3d ", p(i, i));
    }
    puts("");

    printf("c: ");
    for (int i = 0; i <= n; i++) {
        printf("%3d ", c(i, i));
    }
    puts("");

    return 0;
}
