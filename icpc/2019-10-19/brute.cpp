#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 5000

static int n, m;
static struct range {
    int l, r;

    bool has(int i) const {
        return l <= i && i <= r;
    }

    bool operator<(const range &z) const {
        return r < z.r || (r == z.r && l > z.l);
    }
} ran[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &ran[i].l, &ran[i].r);
    }
    sort(ran + 1, ran + n + 1);
    int p = 1;
    for (int i = 2; i <= n; i++) {
        if (ran[p].l < ran[i].l && ran[p].r < ran[i].r)
            ran[++p] = ran[i];
    }
    n = p;
    for (int i = 1; i <= n; i++)
        ran[n + i] = {ran[i].l + m, ran[i].r + m};

    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int cnt = 1, k = ran[i].r;
        for (int j = i + 1; k < ran[i].r + m && j < i + n; j++)
            if (!ran[j].has(k)) {
                cnt++;
                k = ran[j].r;
            }
        ans = min(ans, cnt);
    }
    printf("%d\n", ans);

    return 0;
}
