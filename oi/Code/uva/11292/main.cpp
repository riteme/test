#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 20000

static int n, m;
static int a[NMAX + 10], b[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d", b + i);
    }
}

int main() {
    while (true) {
        initialize();

        if (!n && !m)
            break;

        sort(a + 1, a + n + 1);
        sort(b + 1, b + m + 1);

        int j = 1;
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            while (j < m && b[j] < a[i])
                j++;
            if (j > m || b[j] < a[i])
                ans = -1;
            else {
                ans += b[j++];
            }
        }

        if (ans < 0)
            puts("Loowater is doomed!");
        else
            printf("%lld\n", ans);
    }

    return 0;
}
