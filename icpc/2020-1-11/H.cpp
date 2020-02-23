#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200
#define A 1
#define B 2
#define C (A | B)

int n, m;
char a[NMAX + 10][NMAX + 10];
int t[NMAX + 10][NMAX + 10];

bool isX(char c) {
    return c == 'X' || c == 'A' || c == 'B';
}

bool isD(char c) {
    return c == '.';
}

void dfs(int x, int y, int c) {
    if (x < 1 || x > n ||
        y < 1 || y > m ||
        t[x][y] || !isX(a[x][y]))
        return;
    t[x][y] = c;

    constexpr int dx[] = {-1, 1, 0, 0};
    constexpr int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (t[tx][ty] == C)
            dfs(tx + dx[i], ty + dy[i], c);
        else
            dfs(tx, ty, c);
    }
}

int cnt(int x, int y, int c) {
    int ret = 0;
    for (y++; y <= m; y++) if (t[x][y] & c) {
        int i = y;
        for ( ; i <= m && (t[x][i + 1] & c); i++) ;
        if (y < i) {
            int dy = t[x + 1][y] & c ? 1 : -1;
            int di = t[x + 1][i] & c ? 1 : -1;
            ret += dy != di ? 1 : 0;
        } else ret++;
        y = i;
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", a[i] + 1);

    for (int x = 2; x < n; x++)
    for (int y = 2; y < m; y++)
    if (isX(a[x][y]) && isX(a[x - 1][y]) && isX(a[x + 1][y]) &&
        isX(a[x][y - 1]) && isX(a[x][y + 1]) && isD(a[x - 1][y - 1]) &&
        isD(a[x - 1][y + 1]) && isD(a[x + 1][y - 1]) && isD(a[x + 1][y + 1]))
        t[x][y] = C;

    for (int x = 1; x <= n; x++)
    for (int y = 1; y <= m; y++)
        if (a[x][y] == 'A')
            dfs(x, y, A);
        else if (a[x][y] == 'B')
            dfs(x, y, B);

    int cA = 0, cB = 0, cC = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            if (isD(a[x][y])) {
                int aA = cnt(x, y, A);
                int aB = cnt(x, y, B);
                if (aA & aB & 1) {
                    cC++;
                    // putchar('c');
                } else if (aA & 1) {
                    cA++;
                    // putchar('a');
                } else if (aB & 1) {
                    cB++;
                    // putchar('b');
                } else {
                    // putchar('.');
                }
            } else {
                if (t[x][y] == A) {
                    // putchar('A');
                } else if (t[x][y] == B) {
                    // putchar('B');
                } else {
                    // putchar('C');
                }
            }
        }
        // putchar('\n');
    }

    printf("%d %d %d\n", cA, cB, cC);
    return 0;
}