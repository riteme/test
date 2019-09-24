#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 50

typedef unsigned char u8;

static int n, m, _, cnt;
static int u[NMAX], v[NMAX];
static u8 s[NMAX];

void dfs(int i) {
    if (i == m) cnt++;
    else if (s[u[i]] < s[v[i]]) {
        dfs(i + 1);
        swap(s[u[i]], s[v[i]]);
        dfs(i + 1);
        swap(s[u[i]], s[v[i]]);
    }
}

inline void reset(int len) {
    for (int i = 0; i < len; i++)
        s[i] = i + 1;
}

int solve() {
    cnt = 0;
    reset(n);
    dfs(0);
    for (int i = 0; i < n; i++) {
        reset(n);
        for (int j = i - 1; j >= 0; j--) {
            swap(s[j], s[j + 1]);
            if (j + 1 != i) dfs(0);
        }
        reset(n);
        for (int j = i + 1; j < n; j++) {
            swap(s[j], s[j - 1]);
            dfs(0);
        }
    }
    return cnt;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &_);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", u + i, v + i);
            u[i]--;
            v[i]--;
        }
        reverse(u, u + m);
        reverse(v, v + m);
        printf("%d\n", solve());
    }

    return 0;
}
