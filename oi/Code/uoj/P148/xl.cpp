#include <cstdio>

#define NMAX 50000

static int L, n, m;
static int rock[NMAX + 10];

inline int test(int x) {
    int cnt = 0;
    int i = 0, j = 1;
    while (i <= n) {
        if (i == j)
            j++;

        while (j <= n && rock[j] - rock[i] < x) {
            cnt++;
            j++;
        }

        if (j > n && rock[n + 1] - rock[i] < x)
            cnt++;

        i = j;
    }

    return cnt;
}

int main() {
    scanf("%d%d%d", &L, &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%d", rock + i);

    rock[n + 1] = L;

    int left = 0, right = L;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (test(mid) > m)
            right = mid;
        else
            left = mid;
    }

    if (left != right && test(right) <= m)
        left = right;

    printf("%d\n", left);

    return 0;
}
