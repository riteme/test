#include <cstdio>
#include <cstring>

#include <vector>

using namespace std;

#define NMAX 1000000

int a[NMAX + 10], b[NMAX + 10];

void solve(int k) {
    if (k == 1) {
        a[1] = 2;
        a[2] = 3;
        a[3] = 1;
        a[4] = 4;
        return;
    }

    solve(k - 1);

    int m = 1 << (k + 1);
    memcpy(b + 1, a + 1, sizeof(int) * (m / 2));
    for (int i = 0; i < m / 2; i++) {
        int p = 4 * i, p0 = 2 * i;
        a[p + 1] = b[p0 + 1] + m / 2;
        a[p + 2] = b[p0 + 2];
        a[p + 3] = b[p0 + 1];
        a[p + 4] = b[p0 + 2] + m / 2;
    }
}

int perm[NMAX + 10];
vector<int> idx[300];

void _main() {
    int n, k;
    scanf("%d%d", &n, &k);

    solve(k);

    int m = 1 << (k + 1);
    // for (int i = 1; i <= m; i++) {
    //     printf("%d ", a[i]);
    // }
    // puts("");

    for (int i = 1; i <= n; i++) {
        idx[i].clear();
        idx[i].reserve(m);
    }
    for (int i = 1; i <= n * m; i += 4 * n) {
        for (int j = 1; j <= n; j++) {
            idx[n - j + 1].push_back(i + 2 * j - 2);
            idx[n - j + 1].push_back(i + 2 * j - 1);
        }
        for (int j = 1; j <= n; j++) {
            idx[j].push_back(i + 2 * n + 2 * j - 2);
            idx[j].push_back(i + 2 * n + 2 * j - 1);
        }
    }

    for (int i = 1; i <= n * m; i++) {
        scanf("%d", perm + i);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d", perm[idx[i][a[j] - 1]]);

            if (i == n && j == m)
                putchar('\n');
            else
                putchar(' ');
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }

    return 0;
}