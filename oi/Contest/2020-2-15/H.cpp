#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 200000
#define INF 100000000000

typedef long long i64;

int fa[NMAX + 10], lch[NMAX + 10], rch[NMAX + 10];
i64 key[NMAX + 10], val[NMAX + 10], mi[NMAX + 10];
int q, n, rt;

void update(int x) {
    mi[x] = min(val[x], min(mi[lch[x]], mi[rch[x]]));
}

void lrot(int x) {
    int y = lch[x];
    lch[x] = rch[y];
    fa[rch[y]] = x;
    rch[y] = x;
    if (fa[x]) {
        if (x == lch[fa[x]]) lch[fa[x]] = y;
        else rch[fa[x]] = y;
    }
    fa[y] = fa[x];
    fa[x] = y;
    update(x);
    update(y);
}

void rrot(int x) {
    int y = rch[x];
    rch[x] = lch[y];
    fa[lch[y]] = x;
    lch[y] = x;
    if (fa[x]) {
        if (x == lch[fa[x]]) lch[fa[x]] = y;
        else rch[fa[x]] = y;
    }
    fa[y] = fa[x];
    fa[x] = y;
    update(x);
    update(y);
}

void splay(int x, int t = 0) {
    while (fa[x] != t) {
        int p = fa[x], p2 = fa[p];
        if (p2 != t) {
            if (p == lch[p2] && x == lch[p])
                lrot(p2);
            else if (p == rch[p2] && x == rch[p])
                rrot(p2);
        }
        if (x == lch[p])
            lrot(p);
        else
            rrot(p);
    }
}

int locate(int x, int v) {
    int y;
    while (x) {
        if (key[x] <= v) {
            y = x;
            x = rch[x];
        } else
            x = lch[x];
    }
    return y;
}

int locatel(int x, int v) {
    int y;
    while (x) {
        if (key[x] < v)
            x = rch[x];
        else {
            y = x;
            x = lch[x];
        }
    }
    return y;
}

int minp(int x) {
    while (lch[x]) x = lch[x];
    return x;
}

int maxp(int x) {
    while (rch[x]) x = rch[x];
    return x;
}

bool answer(int v) {
    rt = locate(rt, v);
    splay(rt);

    int bp;
    i64 a, b;

    if (rch[rt]) {
        bp = minp(rch[rt]);
        splay(bp, rt);
        a = key[rt];
        b = key[bp];
        if (v + a > b)
            return true;
    }

    if (lch[rt]) {
        bp = maxp(lch[rt]);
        splay(bp, rt);
        b = key[bp];
        a = key[rt];
        if (a + b > v)
            return true;
    }

    rt = locatel(rt, v);
    splay(rt);
    if (rch[rt] && mi[rch[rt]] < v)
        return true;
    return false;
}

int main() {
    scanf("%d", &q);
    val[0] = mi[0] = INF;
    n = 2;
    rch[1] = 2;
    fa[2] = 1;
    key[1] = -INF;
    key[2] = INF;
    val[2] = INF;
    val[1] = INF;
    update(2);
    update(1);
    rt = 1;

    while (q--) {
        int op, v;
        scanf("%d%d", &op, &v);

        if (op == 1) {
            rt = locate(rt, v);
            splay(rt);
            int bp = minp(rch[rt]);
            splay(bp, rt);
            rch[rt] = fa[bp] = 0;
            val[bp] = key[bp] - v;
            update(bp);

            n++;
            key[n] = v;
            lch[n] = rt;
            rch[n] = bp;
            fa[rt] = fa[bp] = n;
            val[n] = v - key[rt];
            update(n);
            rt = n;

        } else if (op == 2) {
            rt = locate(rt, v);
            splay(rt);
            int ap = maxp(lch[rt]), bp = minp(rch[rt]);
            splay(ap, rt);
            splay(bp, rt);
            fa[ap] = bp;
            fa[bp] = 0;
            lch[bp] = ap;
            val[bp] = key[bp] - key[ap];
            update(bp);
            rt = bp;
        } else {
            puts(answer(v) ? "Yes" : "No");
        }
    }
    return 0;
}