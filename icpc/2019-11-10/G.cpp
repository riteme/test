#include <cassert>
#include <cstdio>

#include <algorithm>

using namespace std;

static int n, m;
static int cnt[512];
static int a[10000000];
static char s[512];

void dfs(int i, int c, int s) {
    if (s > 127) return;
    if (c > 1) cnt[s]--;
    for (int j = 0; j < i; j++)
        dfs(j, c + 1, s + a[j]);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); i++) {
        int v;
        scanf("%d", &v);
        if (v < 1 || v > 127) continue;
        cnt[v]++;
        a[m++] = v;
    }
    for (int i = 0; i < m; i++) dfs(i, 1, a[i]);
    m = 0;
    for (int i = 1; i < 128; i++)
        while (cnt[i]--) s[m++] = i;
    assert(m == n);
    sort(s, s + n);
    puts(s);
    return 0;
}
