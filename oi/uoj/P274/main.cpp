#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 400000
#define L 0
#define R 1

class LCT {
 public:
    LCT() {
        memset(this, 0, sizeof(LCT));

        key[0] = INT_MAX;
        for (int i = 1; i <= NMAX; i++) {
            mink[i] = i;
        }
    }

    void access(int x) {
        splay(x);
        fa[ch[x][R]] = -x;
        ch[x][R] = 0;
        update(x);

        while (fa[x]) {
            int t = -fa[x];
            splay(t);
            fa[ch[t][R]] = -t;
            ch[t][R] = x;
            fa[x] = t;
            update(t);
            x = t;
        }
    }

    int root(int x) {
        access(x);
        splay(x);
        while (ch[x][L]) {
            x = ch[x][L];
            pushdown(x);
        }
        splay(x);

        return x;
    }

    void make_root(int x) {
        access(x);
        splay(x);
        rev[x] ^= 1;
    }

    void link(int u, int v) {
        make_root(v);
        splay(v);
        fa[v] = -u;
        access(v);
    }

    void cut(int x) {
        access(x);
        access(prev(x));
        splay(x);
        fa[x] = 0;
    }

    void select(int u, int v) {
        make_root(u);
        access(v);
        splay(u);
    }

    int query_mink(int u, int v) {
        select(u, v);
        return mink[u];
    }

    int query_sum(int u, int v) {
        select(u, v);
        return sum[u];
    }

    int get_key(int u) {
        return key[u];
    }

    void modify_key(int u, int k) {
        splay(u);
        key[u] = k;
        update(u);
    }

    void modify_val(int u, int v) {
        splay(u);
        val[u] = v;
        update(u);
    }

 private:
    int fa[NMAX + 10];
    int ch[NMAX + 10][2];
    int key[NMAX + 10], mink[NMAX + 10];
    int val[NMAX + 10], sum[NMAX + 10];
    bool rev[NMAX + 10];

    void update(int x) {
        mink[x] = x;
        if (key[mink[ch[x][L]]] < key[mink[x]])
            mink[x] = mink[ch[x][L]];
        if (key[mink[ch[x][R]]] < key[mink[x]])
            mink[x] = mink[ch[x][R]];
        sum[x] = val[x] + sum[ch[x][L]] + sum[ch[x][R]];
    }

    void pushdown(int x) {
        if (rev[x]) {
            rev[x] = 0;
            rev[ch[x][L]] ^= 1;
            rev[ch[x][R]] ^= 1;
            swap(ch[x][L], ch[x][R]);
        }
    }

    void rotate(int x, int c) {
        int y = ch[x][c];
        ch[x][c] = ch[y][c ^ 1];
        if (ch[x][c])
            fa[ch[x][c]] = x;
        ch[y][c ^ 1] = x;

        fa[y] = fa[x];
        fa[x] = y;
        if (fa[y] > 0) {
            if (ch[fa[y]][L] == x)
                ch[fa[y]][L] = y;
            else
                ch[fa[y]][R] = y;
        }

        mink[y] = mink[x];
        sum[y] = sum[x];
        update(x);
    }

    void clear(int x) {
        if (fa[x] > 0)
            clear(fa[x]);
        pushdown(x);
    }

    void splay(int x) {
        clear(x);
        while (fa[x] > 0) {
            int f = fa[x];
            if (fa[f] > 0) {
                int p = fa[f];
                if (x == ch[f][L] && f == ch[p][L])
                    rotate(p, L);
                else if (x == ch[f][R] && f == ch[p][R])
                    rotate(p, R);
            }

            if (x == ch[f][L])
                rotate(f, L);
            else
                rotate(f, R);
        }
    }

    int prev(int x) {
        splay(x);
        x = ch[x][L];
        pushdown(x);
        while (ch[x][R]) {
            x = ch[x][R];
            pushdown(x);
        }
        splay(x);

        return x;
    }
};

static int n, q;
static struct Edge {
    int u, v;
} e[NMAX + 10];
static LCT lct;

int main() {
    scanf("%d%d", &n, &q);

    for (int i = 1; i <= n; i++) {
        lct.modify_key(i, INT_MAX);
    }

    char buf[64];
    while (q--) {
        scanf("%s", buf);

        switch (buf[0]) {
            case 'c': {
                int id, l;
                scanf("%d%d", &id, &l);
                lct.modify_val(n + id + 1, l);
            } break;

            case 'f': {
                int id, u, v, t, l;
                scanf("%d%d%d%d%d", &id, &u, &v, &t, &l);
                u++; v++;

                int p;
                bool ok = true;
                if (lct.root(u) == lct.root(v)) {
                    p = lct.query_mink(u, v);

                    if (lct.get_key(p) < t) {
                        lct.make_root(p);
                        lct.cut(e[p].u);
                        lct.cut(e[p].v);
                    } else
                        ok = false;
                }

                if (ok) {
                    p = n + id + 1;
                    e[p] = {u, v};
                    lct.modify_key(p, t);
                    lct.modify_val(p, l);
                    lct.link(u, p);
                    lct.link(v, p);
                }
            } break;

            case 'm': {
                int u, v;
                scanf("%d%d", &u, &v);
                u++; v++;

                if (lct.root(u) == lct.root(v))
                    printf("%d\n", lct.query_sum(u, v));
                else
                    puts("-1");
            } break;
        }
    }

    return 0;
}
