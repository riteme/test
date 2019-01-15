#include <cstdio>
#include <algorithm>

using namespace std;

static int f[100][100];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++)
        f[i][0] = 1;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= min(i, m); j++)
        f[i][j] = f[i - 1][j] + f[i][j - 1];
    printf("%d\n", f[n][m]);
    return 0;
}
