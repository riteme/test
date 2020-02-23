#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 200000
#define LOGN 30


static int n;
static int w[NMAX + 10], fa[NMAX + 10];
static int nxt[NMAX + 10];
static bool mark[NMAX + 10];

static struct Trie {
    Trie() {
        memset(this, 0, sizeof(Trie));
    }

    int cnt, p;
    Trie *ch[2];
} *tr;

void modify(Trie *x, int p, int d) {
    int v = w[p];
    for (int i = LOGN - 1; i >= 0; i--) {
        x->cnt += d;
        int b = (v >> i) & 1;
        if (!x->ch[b])
            x->ch[b] = new Trie;
        x = x->ch[b];
    }
    x->cnt += d;
    x->p = p;
}

int query(Trie *x, int v) {
    for (int i = LOGN - 1; i >= 0; i--) {
        int b = (v >> i) & 1;
        if (x->ch[b] && x->ch[b]->cnt)
            x = x->ch[b];
        else
            x = x->ch[b ^ 1];
    }
    return x->p;
}

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

static int ed[NMAX + 10], len[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", w + i);

    sort(w + 1, w + n + 1);
    n = unique(w + 1, w + n + 1) - w - 1;
    tr = new Trie;
    for (int i = 1; i <= n; i++) {
        nxt[i] = i;
        modify(tr, i, +1);
    }

    i64 ans = 0, cnt = 0;
    while (cnt < n - 1) {
        memset(mark + 1, 0, n);
        for (int u = 1; u <= n; u++) if (!mark[u]) {
            int x = u;
            do {
                modify(tr, x, -1);
                mark[x] = true;
                x = nxt[x];
            } while (x != u);

            x = u;
            len[u] = INT_MAX;
            do {
                int v = query(tr, w[x]);
                int l = w[x] ^ w[v];
                if (len[u] > l) {
                    len[u] = l;
                    ed[u] = v;
                }
                x = nxt[x];
            } while (x != u);

            x = u;
            do {
                modify(tr, x, +1);
                x = nxt[x];
            } while (x != u);

            mark[u] = false;
        }

        for (int u = 1; u <= n; u++) if (!mark[u]) {
            int x = find(u);
            int y = find(ed[u]);
            if (x == y)
                continue;

            cnt++;
            ans += len[u];
            fa[x] = y;

            int t = nxt[u];
            nxt[u] = nxt[ed[u]];
            nxt[ed[u]] = t;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
