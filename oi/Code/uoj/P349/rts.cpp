#define NDEBUG

#include "rts.h"

#include <cassert>
#include <cstring>

#define NMAX 300000
#define SIZEMAX (NMAX + 10)

#define CLEAR(arr) memset(arr, 0, sizeof(arr))

struct LCT {
    LCT() {
        CLEAR(fa);
        CLEAR(ch);
        CLEAR(pre);
        CLEAR(nxt);

        for (int i = 1; i <= NMAX; i++) {
            top[i] = rot[i] = i;
        }
    }

    int fa[SIZEMAX], ch[SIZEMAX][2];
    int pre[SIZEMAX], nxt[SIZEMAX];
    int top[SIZEMAX], rot[SIZEMAX];

    void rotate(int x, int c) {
        int y = ch[x][c];
        ch[x][c] = ch[y][c ^ 1];
        ch[y][c ^ 1] = x;

        if (fa[x] > 0)
            ch[fa[x]][x != ch[fa[x]][0]] = y;
        else
            top[y] = top[x], rot[top[x]] = y;

        fa[y] = fa[x];
        fa[x] = y;
        fa[ch[x][c]] = x;
    }

    void splay(int x) {
        while (fa[x] > 0) {
            int f = fa[x];

            if (fa[f] > 0) {
                int pf = fa[f];
                if (f == ch[pf][0] && x == ch[f][0])
                    rotate(pf, 0);
                if (f == ch[pf][1] && x == ch[f][1])
                    rotate(pf, 1);
            }

            rotate(f, x != ch[f][0]);
        }
    }

    int first(int x) {
        assert(fa[x] <= 0);
        while (ch[x][0])
            x = ch[x][0];
        splay(x);
        return x;
    }

    void access(int x) {
        splay(x);
        x = first(x);
        while (fa[x]) {
            int t = -fa[x];
            splay(t);

            top[ch[t][1]] = nxt[t];
            rot[nxt[t]] = ch[t][1];

            pre[nxt[t]] = 0;
            nxt[t] = x;
            pre[x] = t;

            fa[ch[t][1]] = -t;
            ch[t][1] = x;
            fa[x] = t;

            x = first(t);
        }
    }

    void link(int x, int y) {
        assert(fa[y] == 0);
        fa[y] = -x;
    }
};

static LCT lct;
static bool marked[SIZEMAX];

int approach(int t) {
    int x = 1;
    while (true) {
        int u = explore(x, t);
        if (!marked[u]) {
            lct.link(x, u);
            return u;
        }

        if (lct.pre[x] == u)
            x = lct.ch[x][0];
        else if (lct.nxt[x] == u)
            x = lct.ch[x][1];
        else
            x = lct.rot[u];
    }
}

void open(int s, int t) {
    marked[s] = true;
    while (s != t) {
        s = explore(s, t);
        marked[s] = true;
    }
}

void fuckwys(int n) {
    int l = 1, r = 1;
    for (int t = 1; t <= n; t++) {
        if (marked[t])
            continue;

        int x = explore(l, t);
        if (!marked[x])
            open(x, t), l = t;
        else {
            x = explore(r, t);
            open(x, t);
            r = t;
        }
    }
}

void play(int n, int T, int dataType) {
    marked[1] = true;

    if (dataType == 3)
        fuckwys(n);
    else {
        for (int t = 2; t <= n; t++) {
            if (!marked[t]) {
                int x = approach(t);
                marked[x] = true;

                int last = x;
                while (x != t) {
                    x = explore(x, t);
                    marked[x] = true;
                    lct.link(last, x);
                    last = x;
                }

                lct.access(t);
            }
        }
    }
}