#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 1000;
constexpr int MMAX = NMAX * (NMAX - 1) / 2;

static int n, m;
static int cur[NMAX + 10];
static int seq[MMAX + 10];

void dfs(int x) {
    for (int &i = cur[x]; i <= n; ) {
        int v = i++;
        if (x == v || cur[v] > x)
            continue;
        dfs(v);
        seq[m--] = v;
    }
}

int main() {
    scanf("%d", &n);
    if (n & 1) {
        for (int i = 1; i <= n; i++)
            cur[i] = 1;
        m = n * (n - 1) / 2;
        dfs(1);
        seq[0] = 1;
        for (int i = 1; i < n; i++) {
            int l = i * (i - 1) / 2;
            int r = i * (i + 1) / 2;
            for (int j = l; j <= r; j++)
                printf(j < r ? "%d " : "%d\n", seq[j]);
        }
    } else {
        for (int i = 1; 2 * i <= n; i++) {
            m = 0;
            for (int j = 1; j < i; j++) {
                seq[m++] = 2 * i - 1;
                seq[m++] = 2 * j - 1;
                seq[m++] = 2 * i;
                seq[m++] = 2 * j;
            }
            seq[m++] = 2 * i - 1;
            seq[m++] = 2 * i;
            if (i > 1)
                for (int j = 0; j < 2 * i - 1; j++)
                    printf(j < 2 * i - 2 ? "%d " : "%d\n", seq[j]);
            for (int j = 2 * i - 2; j < m; j++)
                printf(j < m - 1 ? "%d " : "%d\n", seq[j]);
        }
    }

    return 0;
}
