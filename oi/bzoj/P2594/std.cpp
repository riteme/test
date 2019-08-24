#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m, Q, top;
int f[1500005];
int fa[1500005], c[1500005][2], s[1500005];
int mx[1500005], val[1500005];
bool rev[1500005];
struct edge {
    int u, v, w, id;
    bool d;
} e[1000005];
struct que {
    int f, x, y, ans, id;
} q[100005];
bool operator<(edge a, edge b) {
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}
bool cmp(edge a, edge b) {
    return a.w < b.w;
}
bool cmp2(edge a, edge b) {
    return a.id < b.id;
}
int getf(int x) {
    return x == f[x] ? x : f[x] = getf(f[x]);
}
int find(int u, int v) {
    int l = 1, r = m;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (e[mid].u < u || (e[mid].u == u && e[mid].v < v))
            l = mid + 1;
        else if (e[mid].u == u && e[mid].v == v)
            return mid;
        else
            r = mid - 1;
    }
}
bool isroot(int x) {
    return c[fa[x]][0] != x && c[fa[x]][1] != x;
}
void update(int x) {
    int l = c[x][0], r = c[x][1];
    mx[x] = x;
    if (val[mx[l]] > val[mx[x]])
        mx[x] = mx[l];
    if (val[mx[r]] > val[mx[x]])
        mx[x] = mx[r];
}
void rotate(int x) {
    int y = fa[x], z = fa[y], l, r;
    if (c[y][0] == x)
        l = 0;
    else
        l = 1;
    r = l ^ 1;
    if (!isroot(y)) {
        if (c[z][0] == y)
            c[z][0] = x;
        else
            c[z][1] = x;
    }
    fa[x] = z;
    fa[y] = x;
    fa[c[x][r]] = y;
    c[y][l] = c[x][r];
    c[x][r] = y;
    update(y);
    update(x);
}
void pushdown(int x) {
    int l = c[x][0], r = c[x][1];
    if (rev[x]) {
        rev[x] ^= 1;
        rev[l] ^= 1;
        rev[r] ^= 1;
        swap(c[x][0], c[x][1]);
    }
}
void splay(int x) {
    top = 0;
    s[++top] = x;
    for (int i = x; !isroot(i); i = fa[i])
        s[++top] = fa[i];
    for (int i = top; i; i--)
        pushdown(s[i]);
    while (!isroot(x)) {
        int y = fa[x], z = fa[y];
        if (!isroot(y)) {
            if (c[y][0] == x ^ c[z][0] == y)
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}
void access(int x) {
    int t = 0;
    while (x) {
        splay(x);
        c[x][1] = t;
        update(x);
        t = x;
        x = fa[x];
    }
}
void makeroot(int x) {
    access(x);
    splay(x);
    rev[x] ^= 1;
}
void link(int x, int y) {
    makeroot(x);
    fa[x] = y;
}
void cut(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
    c[y][0] = fa[x] = 0;
}
int query(int x, int y) {
    makeroot(x);
    access(y);
    splay(y);
    return mx[y];
}
int main() {
    n = read();
    m = read();
    Q = read();
    for (int i = 1; i <= n; i++)
        f[i] = i;
    for (int i = 1; i <= m; i++) {
        e[i].u = read(), e[i].v = read(), e[i].w = read();
        if (e[i].u > e[i].v)
            swap(e[i].u, e[i].v);
    }
    sort(e + 1, e + m + 1, cmp);
    for (int i = 1; i <= m; i++) {
        e[i].id = i;
        val[n + i] = e[i].w;
        mx[n + i] = n + i;
    }
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= Q; i++) {
        q[i].f = read(), q[i].x = read(), q[i].y = read();
        if (q[i].f == 2) {
            if (q[i].x > q[i].y)
                swap(q[i].x, q[i].y);
            int t = find(q[i].x, q[i].y);
            e[t].d = 1;
            q[i].id = e[t].id;
        }
    }
    sort(e + 1, e + m + 1, cmp2);
    int tot = 0;
    for (int i = 1; i <= m; i++)
        if (!e[i].d) {
            int u = e[i].u, v = e[i].v, x = getf(u), y = getf(v);
            if (x != y) {
                f[x] = y;
                link(u, i + n);
                link(v, i + n);
                tot++;
                if (tot == n - 1)
                    break;
            }
        }
    for (int i = Q; i; i--) {
        if (q[i].f == 1)
            q[i].ans = val[query(q[i].x, q[i].y)];
        else {
            int u = q[i].x, v = q[i].y, k = q[i].id;
            int t = query(u, v);
            if (e[k].w < val[t]) {
                cut(e[t - n].u, t);
                cut(e[t - n].v, t);
                link(u, k + n);
                link(v, k + n);
            }
        }
    }
    for (int i = 1; i <= Q; i++)
        if (q[i].f == 1)
            printf("%d\n", q[i].ans);
    return 0;
}
