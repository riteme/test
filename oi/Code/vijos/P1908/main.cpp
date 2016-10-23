#include <cstdio>

static int d;
static int n;
static int pre[200][200];

int query(int l, int r, int t, int b) {
    if (l < 1)
        l = 1;
    if (r >= 200)
        r = 199;

    if (t < 1)
        t = 1;
    if (b >= 200)
        b = 199;

    return pre[r][b] - pre[l - 1][b] - pre[r][t - 1] + pre[l - 1][t - 1];
}

int main() {
    scanf("%d%d", &d, &n);
    for (int i = 0; i < n; i++) {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k);
        x++, y++;
        pre[x][y] += k;
    }  // for

    for (int i = 1; i < 200; i++) {
        for (int j = 1; j < 200; j++) {
            pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }  // for
    }      // for

    int answer = 0;
    int cnt = 0;
    for (int i = 1; i <= 129; i++) {
        for (int j = 1; j <= 129; j++) {
            int q = query(i - d, i + d, j - d, j + d);
            if (q > answer) {
                answer = q;
                cnt = 1;
            } else if (q == answer) {
                cnt++;
            }
        }  // for
    }      // for

    printf("%d %d\n", cnt, answer);

    return 0;
}  // function main
