#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 1000000;
constexpr int INF = 10000000;

int n, q, K;
int a[NMAX + 10];
int ch[NMAX + 10][2];
int stk[NMAX + 10], t;
int len[NMAX + 10];
int ans;

int dfs(int x) {
    if (!x)
        return -INF;

    len[x] = 1;
    int mx = a[x];
    mx = max(mx, dfs(ch[x][0]));
    mx = max(mx, dfs(ch[x][1]));
    len[x] += len[ch[x][0]] + len[ch[x][1]];

    ans = max(ans, min(len[x], mx + a[x] - 1));

    return mx;
}

int eval() {
    memset(ch, 0, sizeof(ch));
    t = 0;
    for (int i = 1; i <= n; i++) {
        while (t && a[stk[t]] >= a[i]) {
            ch[stk[t]][1] = ch[i][0];
            ch[i][0] = stk[t];
            t--;
        }
        stk[++t] = i;
    }

    while (t > 1) {
        ch[stk[t - 1]][1] = stk[t];
        t--;
    }

    ans = 0;
    dfs(stk[1]);
    return ans;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    printf("%d\n", eval());
    while (q--) {
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            swap(a[x], a[y]);
        }
        printf("%d\n", eval());
    }
    return 0;
}