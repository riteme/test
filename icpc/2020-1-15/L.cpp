#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n, m;
char a[NMAX + 10][NMAX + 10];
int mx[NMAX + 10][NMAX + 10];

bool solve(int K) {
    for (int j = 1; j <= m; j++) {
        int L = 0;
        for (int i = 1; i <= n; i++) {
            if (mx[j][i] >= K) L++;
            else L = 0;
            if (L >= K)
                return true;
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", a[i] + 1);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        mx[j][i] = a[i][j] == a[i][j - 1] ? mx[j - 1][i] + 1 : 1;

    int l = 0, r = min(n, m);
    while (l < r) {
        int mi = (l + r) / 2 + 1;
        if (solve(mi)) l = mi;
        else r = mi - 1;
    }

    printf("%d\n", l * l);
    return 0;
}