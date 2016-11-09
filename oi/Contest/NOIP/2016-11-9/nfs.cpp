#include <cstdio>
#include <cctype>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100
#define KMAX 10
#define INFTY 1000000000

static int n, k;
static int stone[NMAX + 10][KMAX + 10];
static int f[NMAX + 10][KMAX + 10];

static int dp(int x, int y) {
    if (y < 1 || y > k)
        return INFTY;
    if (x <= 1)
        return 0;
    if (f[x][y] > 0)
        return f[x][y];

    int &answer = f[x][y];
    answer = INFTY;

    answer = min(answer, dp(x - 2, y) + stone[x - 1][y] + stone[x - 2][y]);
    answer = min(answer, dp(x - 2, y - 1) + stone[x - 2][y - 1]);
    answer = min(answer, dp(x - 2, y + 1) + stone[x - 2][y + 1]);

    return answer;
}

int main() {
    freopen("nfs.in", "r", stdin);
    freopen("nfs.out", "w", stdout);
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            char c = getchar();
            while (!isdigit(c))
                c = getchar();

            if (c == '1')
                stone[i][j] = 1;
            f[i][j] = -1;
        }
    }

    int answer = INFTY;
    for (int i = 1; i <= k; i++) {
        answer = min(answer, dp(n + 1, i));
    }

    printf("%d\n", answer);

    return 0;
}
