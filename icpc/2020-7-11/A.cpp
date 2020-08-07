/**
 * 注意 S = 0 的情况
 */

#include <cstdio>
#include <cstring>

int a[1000];
bool mark[1000];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int S = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            S += a[i];
        }

        int m;
        scanf("%d", &m);
        memset(mark + 1, 0, n);
        for (int i = 0; i < m; i++) {
            int v;
            scanf("%d", &v);
            mark[v] = true;
        }

        int cnt = 0;
        double C = 0, Q = 0, P = 0;
        for (int i = 1; i <= n; i++) {
            if (mark[i]) {
                Q += a[i];
                cnt++;
            } else {
                C += a[i];
            }
        }
        P = double(cnt) / n;

        if (S == 0)
            puts("0");
        else if (n == cnt)
            puts("inf");
        else if (cnt == 0)
            printf("%.2lf\n", C / n);
        else {
            Q /= cnt;
            C /= n - cnt;
            double ans = double(S) / (n - m);
            printf("%.2lf\n", ans);
        }
    }
    return 0;
}