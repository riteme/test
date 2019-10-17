#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define S 500
#define OMEGA 10

static int n, q;
static int A[NMAX + 10];
static char p[NMAX + 10][OMEGA];
static int B[500][OMEGA][OMEGA];
static char tmp[OMEGA];

void parse(int x, char *t) {
    for (int i = 0; i < OMEGA; i++, x /= 10)
        t[i] = x % 10;
}

void initialize() {
    scanf("%d%d", &n, &q);
    memset(B, 0, sizeof(B));
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        parse(A[i], p[i]);
        for (int j = 0; j < OMEGA; j++)
            B[i / S][j][p[i][j]]++;
    }
}

#define LP(x) ((x) * S)
#define RP(x) (LP(x + 1) - 1)

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        initialize();
        while (q--) {
            char buf[16];
            int a, b, c, d;
            scanf("%s", buf);
            if (buf[0] == 'Q') {
                scanf("%d%d%d%d", &a, &b, &c, &d);
                int ans = 0, l = a / S, r = b / S;
                if (l < r) {
                    for (int i = a; i <= RP(l) && i <= n; i++)
                        ans += p[i][c - 1] == d;
                    for (int i = LP(r); i <= b; i++)
                        ans += p[i][c - 1] == d;
                    for (int i = l + 1; i < r; i++)
                        ans += B[i][c - 1][d];
                } else {
                    for (int i = a; i <= b; i++)
                        ans += p[i][c - 1] == d;
                }
                printf("%d\n", ans);
            } else {
                scanf("%d%d", &a, &b);
                parse(b, tmp);
                int c = a / S;
                for (int i = 0; i < OMEGA; i++) {
                    B[c][i][p[a][i]]--;
                    B[c][i][tmp[i]]++;
                }
                A[a] = b;
                memcpy(p[a], tmp, sizeof(tmp));
            }
        }
    }
    return 0;
}
