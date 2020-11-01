#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm>

using namespace std;

#define NMAX 3000

struct op_t {
    char d;
    int i;
    char c;
};

int n, m;
char a[NMAX + 10][NMAX + 10];
int cnt[2][NMAX + 10][27];
bool mark[2][NMAX + 10];
op_t op[NMAX * 2 + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", a[i] + 1);
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '?')
                a[i][j] = 0;
            else
                a[i][j] = a[i][j] - 'a' + 1;
        }
    }

    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        cnt[0][i][a[i][j]]++;
        cnt[1][j][a[i][j]]++;
    }

    for (int _ = 0; _ < 2 * n; _++) {
        bool ok = false;

        for (int i = 1; i <= n && !ok; i++)
        if (!mark[0][i])
        for (int c = 1; c <= 26 && !ok; c++)
        if (cnt[0][i][0] + cnt[0][i][c] == n) {
            ok = true;
            op[m++] = {'h', i, char(c + 'a' - 1)};
            mark[0][i] = true;

            for (int j = 1; j <= n; j++) {
                if (a[i][j]) {
                    cnt[1][j][a[i][j]]--;
                    cnt[1][j][0]++;
                }
            }
        }

        for (int j = 1; j <= n && !ok; j++)
        if (!mark[1][j])
        for (int c = 1; c <= 26 && !ok; c++)
        if (cnt[1][j][0] + cnt[1][j][c] == n) {
            ok = true;
            op[m++] = {'v', j, char(c + 'a' - 1)};
            mark[1][j] = true;

            for (int i = 1; i <= n; i++) {
                if (a[i][j]) {
                    cnt[0][i][a[i][j]]--;
                    cnt[0][i][0]++;
                }
            }
        }

        assert(ok);
    }

    for (int i = m - 1; i >= 0; i--) {
        printf("%c %d %c\n", op[i].d, op[i].i, op[i].c);
    }

    return 0;
}
