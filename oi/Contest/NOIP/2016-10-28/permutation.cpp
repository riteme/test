#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 50

typedef long long int64;

static int64 _f[NMAX + 10][NMAX + 10];

static int64 f(int n, int i) {
    if (n == 0 && i == 0)
        return 1;
    if (n == 1 && i == 0)
        return 1;
    if (n <= 1)
        return 0;

    if (_f[n][i] >= 0)
        return _f[n][i];

    int64 answer = 0;
    for (int j = 0; j <= n - i - 2; j++)
        answer += f(n - i - 2, j);

    if (n - i - 2 > 1)
        answer++;

    _f[n][i] = answer;
    return answer;
}

static int perm[NMAX + 10];

static void dfs(int n, int64 k, int pos) {
    if (n == 0)
        return;
    if (n == 1) {
        perm[pos] = 1;
        return;
    }

    if (k == 0) {
        for (int i = 1; i <= n; i++)
            perm[pos + i - 1] = i;
    } else {
        int j = n - 1;
        int64 sum = 0;
        while (j > 0 && sum + f(n, j - 1) < k) {
            j--;
            sum += f(n, j);
        }

        if (j > 0) {
            j--;
        }

        assert(j <= n - 2);
        dfs(n - j - 2, k - sum - 1, pos + j + 2);

        for (int i = j + 2; i <= n; i++)
            perm[pos + i] += j + 2;
        for (int i = 1; i <= j; i++)
            perm[pos + i - 1] = i;
        perm[pos + j] = j + 2;
        perm[pos + j + 1] = j + 1;
    }
}

int main() {
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    for (int i = 1; i <= NMAX; i++)
        for (int j = 0; j <= NMAX; j++)
            _f[i][j] = -1;

    int n;
    int64 k;
    scanf("%d%lld", &n, &k);

    for (int i = n; i >= 0; i--)
        f(n, i);

    dfs(n, k - 1, 1);

    for (int i = 1; i <= n; i++)
        printf("%d ", perm[i]);
    printf("\n");

    fclose(stdin);
    fclose(stdout);
    return 0;
}
