#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000

struct Range {
    int l, r;

    bool has(int i) const {
        return l <= i && i <= r;
    }

    bool operator<(const Range &z) const {
        return r < z.r || (r == z.r && l > z.l);
    }
};

static int n, m;
static Range ran[NMAX + 10];
static int nxt[NMAX + 10], dep[NMAX + 10];
static int fa[NMAX + 10], out[NMAX + 10];

void setup() {
    sort(ran + 1, ran + n + 1);
    int p = 1;
    for (int i = 2; i <= n; i++)
        if (ran[p].l < ran[i].l && ran[p].r < ran[i].r)
            ran[++p] = ran[i];
    n = p;
    for (int i = 1; i <= n; i++)
        ran[i + n] = {ran[i].l + m, ran[i].r + m};
}

void dual() {
    static Range tmp[NMAX + 10];
    int p = 0;
    for (int i = 1, k = 2; i <= n; i++) {
        for (k = max(i + 1, k); k <= 2 * n && ran[k].has(ran[i].r + 1); )
            k++;
        if (i + 1 < k) {
            tmp[++p] = {i + 1, k - 1};
            if (tmp[p].r > n)
                tmp[p] = {tmp[p].l - n, tmp[p].r - n};
        }
    }
    for (int i = 1, k = 2; i <= n; i++) {
        while (k <= 2 * n && ran[k].has(ran[i].r)) k++;
        tmp[++p] = {i, k - 1};
        if (tmp[p].r > n)
            tmp[p] = {tmp[p].l - n, tmp[p].r - n};
    }
    m = n;
    n = p;
    memcpy(ran + 1, tmp + 1, sizeof(Range) * n);
}

static vector<int> G[NMAX + 10];

static int stk[NMAX + 10], t;
void dfs(int x) {
    stk[t++] = x;
    if (fa[x]) {
        nxt[x] = nxt[fa[x]];
        while (nxt[x] < t && ran[stk[nxt[x] + 1]].r - ran[x].r >= m)
            nxt[x]++;
        out[ran[x].r] = dep[x] - dep[stk[nxt[x]]];
    } else nxt[x] = 0;
    for (int v : G[x])
        dfs(v);
    t--;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &ran[i].l, &ran[i].r);
        ran[i].r--;
        if (ran[i].r == 0) ran[i].r = m;
        if (ran[i].r < ran[i].l)
            ran[i] = {ran[i].l - m, ran[i].r};
    }
    setup();
    dual();
    for (int i = 1; i <= n; i++)
        printf("[%d, %d]\n", ran[i].l, ran[i].r);
    setup();

    for (int i = 1, j, k = 1; i < 2 * n; i++) {
        j = ran[i].r;
        for ( ; k <= 2 * n && ran[k].has(j); k++) ;
        if (k <= 2 * n) {
            nxt[i] = k;
            G[k].push_back(i);
        }
    }

    memcpy(fa, nxt, sizeof(fa));

#define ACM_BEGIN
    int ans = INT_MAX;
    for (int i = 2 * n; i >= 1; i--) {
        dep[i] = dep[nxt[i]] + 1;
        nxt[i] = nxt[i] ? nxt[nxt[i]] : i;
        if (ran[nxt[i]].r - ran[i].r >= m)
            ans = min(ans, dep[i] - 1);
    }
#define ACM_END

    for (int i = 1; i <= 2 * n; i++)
        if (!fa[i]) dfs(i);
    for (int i = m; i >= 1; i--)
        if (!out[i]) out[i] = out[i + 1];

    for (int i = 1; i <= m; i++)
        printf("%d ", out[i]);
    puts("");
    printf("%d\n", ans);
    return 0;
}

