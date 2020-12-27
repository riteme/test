/**
 * NOTE: 0x3f3f3f3f < (1 << 30)
 */

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;
constexpr int SMAX = 31;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MEMSIZE = 33 * NMAX;

struct Node {
    Node *ch[2];
    vector<i64> f;

    int size() {
        return f.size();
    }
} mem[MEMSIZE];

Node *null = mem + 0;
size_t mempos = 1;

Node *nalloc() {
    auto p = mem + (mempos++);
    p->ch[0] = p->ch[1] = null;
    return p;
}

int n, q;
Node *tr = nalloc();

void insert(Node *x, i64 v) {
    for (int i = SMAX - 1; i >= 0; i--) {
        x->f.push_back(INF);

        int b = (v >> i) & 1;
        auto &y = x->ch[b];
        if (y == null) y = nalloc();
        x = y;
    }

    x->f.push_back(0);
}

void chkmin(i64 &a, i64 b) {
    if (a > b)
        a = b;
}

void dp(Node *x, int d) {
    if (x == null || d == 0)
        return;

    i64 p = 1ll << (d - 1);

    for (int b = 0; b < 2; b++) {
        dp(x->ch[b], d - 1);
    }

    for (int b = 0; b < 2; b++)
    for (int i = 0; i < x->ch[b]->size(); i++) {
        auto y = x->ch[b];
        auto z = x->ch[b ^ 1];

        chkmin(x->f[i], y->f[i]);
        chkmin(x->f[i + z->size()], y->f[i] + p);
    }
}

i64 query(Node *x, i64 l, i64 r, int k, i64 s, int d) {
    i64 xl = l >> d, xr = r >> d, xs = s >> d;
    if (x == null || xs < xl || xs > xr)
        return INF;
    if (d == 0 || (xl < xs && xs < xr))
        return x->f[k];

    int i = d - 1;
    i64 p = 1ll << i;
    i64 rax = INF;
    for (int b = 0; b < 2; b++) {
        i64 ns = s | (i64(b) << i);
        int nk = k;
        if (nk >= x->ch[b]->size()) {
            nk -= x->ch[b]->size();
            chkmin(rax, p + query(x->ch[b ^ 1], l, r, nk, ns, d - 1));
        } else
            chkmin(rax, query(x->ch[b], l, r, nk, ns, d - 1));
    }

    return rax;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        i64 v;
        scanf("%lld", &v);
        insert(tr, v);
    }

    dp(tr, SMAX);

    while (q--) {
        i64 l, r;
        int k;
        scanf("%lld%lld%d", &l, &r, &k);
        k--;
        i64 v = query(tr, l, r, k, 0, SMAX);
        printf("%lld\n", v);
    }

    return 0;
}
