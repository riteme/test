#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

int a[NMAX + 10], b[NMAX + 10];

bool cmp(int i, int j) {
    return a[i] > a[j] || (a[i] == a[j] && i < j);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, K;
        scanf("%d%d%d", &n, &m, &K);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            b[i] = i;
        }

        if (K > 0)
            sort(b + 1, b + n + 1, cmp);

        for (int i = 1; i <= n; i++) {
            printf(i < n ? "%d " : "%d\n", b[i]);
        }
    }
    return 0;
}
