#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n, m, D;
int L[NMAX + 10], p[NMAX + 10];
int a[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &m, &D);
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d", L + i);
        sum += L[i];
    }

    int x, i;
    for (x = 0, i = 1; x <= n; ) {
        if (x + D < n + 1 - sum) {
            if (i > m) break;
            sum -= L[i];
            p[i] = x + D;
            x = x + D + L[i] - 1;
            i++;
        } else {
            x = n + 1;
        }
    }

    if (x != n + 1) {
        puts("NO");
        return 0;
    }

    for (i = m, x = n + 1; n + 1 - x < sum; i--)
        p[i] = (x -= L[i]);

    for (i = 1; i <= m; i++)
    for (int j = p[i]; j < p[i] + L[i]; j++)
        a[j] = i;

    puts("YES");
    for (i = 1; i <= n; i++)
        printf("%d ", a[i]);
    puts("");

    return 0;
}