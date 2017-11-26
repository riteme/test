#pragma GCC optimize(3)

#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t pos = BUFFERSIZE;
static char buffer[BUFFERSIZE];

inline char _getchar() {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buffer, 1, BUFFERSIZE, stdin);
    }
    return buffer[pos++];
}

inline void read(int &x) {
    x = 0;
    int f = 1;
    char c = _getchar();
    for (; !isalnum(c); c = _getchar())
        if (c == '-')
            f = -1;
    for (; isalnum(c); c = _getchar())
        x = x * 10 + (c - '0');
    x *= f;
}

inline void read(char *s) {
    size_t pos = 0;
    char c = _getchar();
    for (; !isalnum(c); c = _getchar())
        ;
    for (; isalnum(c); c = _getchar())
        s[pos++] = c;
    s[pos] = 0;
}

#define NMAX 100000
#define L(x) (x << 1)
#define R(x) ((x << 1) | 1)
#define P(x) (x >> 1)

inline void chkmax(int &a, int b) {
    if (b > a)
        a = b;
}

inline int nxtp(int x) {
    int k;
    for (k = 1; k < x; k <<= 1)
        ;
    return k;
}

struct SegmentTree {
    SegmentTree() {
        memset(sum, 0, sizeof(sum));
        memset(maxv, 0, sizeof(maxv));
        memset(pos, 0, sizeof(pos));
    }

    int sum[NMAX + 10], maxv[NMAX + 10], pos[NMAX + 10];

    void update(int x) {
        int l = x << 1;
        sum[x] = sum[l] + sum[l | 1];
        maxv[x] = max(maxv[l], maxv[l | 1]);
    }

    void build(int x, int l, int r, int *a) {
        if (l == r) {
            pos[l] = x;
            sum[x] = maxv[x] = a[l];
        } else {
            int m = (l + r) >> 1;
            build(L(x), l, m, a);
            build(R(x), m + 1, r, a);
            update(x);
        }
    }

    void modify(int x, int v) {
        x = pos[x];
        sum[x] = maxv[x] = v;
        for (x >>= 1; x; x >>= 1) {
            update(x);
        }  // for
    }

    int query_sum(int l, int r) {
        int ret = 0;

        for (l = pos[l] - 1, r = pos[r] + 1; (l ^ r) != 1; l >>= 1, r >>= 1) {
            if (~l & 1)
                ret += sum[l | 1];
            if (r & 1)
                ret += sum[r ^ 1];
        }  // for

        return ret;
    }

    int query_max(int l, int r) {
        int ret = INT_MIN;

        for (l = pos[l] - 1, r = pos[r] + 1; (l ^ r) != 1; l >>= 1, r >>= 1) {
            if (~l & 1)
                chkmax(ret, maxv[l | 1]);
            if (r & 1)
                chkmax(ret, maxv[r ^ 1]);
        }  // for

        return ret;
    }
};  // struct SegmentTree

static int n, q, cnt;
static int seq[NMAX + 10];
static vector<int> G[NMAX + 10];
static int size[NMAX + 10], father[NMAX + 10], depth[NMAX + 10];
static int top[NMAX + 10], id[NMAX + 10];
static char buf[16];
static SegmentTree tree;

void dfs(int x, int f) {
    size[x] = 1;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == f)
            continue;

        father[v] = x;
        depth[v] = depth[x] + 1;
        dfs(v, x);
        size[x] += size[v];
    }  // for
}

void decompose(int x, int f) {
    int nxt = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == f)
            continue;
        if (size[v] > size[nxt])
            nxt = v;
    }  // for

    if (nxt) {
        top[nxt] = top[x];
        id[nxt] = ++cnt;
        decompose(nxt, x);
    }

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == f || v == nxt)
            continue;

        top[v] = v;
        id[v] = ++cnt;
        decompose(v, x);
    }  // for
}

void initialize() {
    // scanf("%d", &n);
    read(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        read(u);
        read(v);
        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    dfs(1, 0);
    top[1] = id[1] = ++cnt;
    decompose(1, 0);

    for (int i = 1; i <= n; i++) {
        int v;
        // scanf("%d", &v);
        read(v);
        seq[id[i]] = v;
    }  // for

    tree.build(1, 0, nxtp(n + 2) - 1, seq);

    // scanf("%d", &q);
    read(q);
}

int main() {
    initialize();

    while (q--) {
        int x, y;
        // scanf("%s%d%d", buf, &x, &y);
        read(buf);
        read(x);
        read(y);

        if (buf[0] == 'C')  // CHANGE
            tree.modify(id[x], y);
        else if (buf[1] == 'M') {  // QMAX
            int ret = INT_MIN;

            while (top[x] != top[y]) {
                if (depth[top[x]] > depth[top[y]]) {
                    chkmax(ret, tree.query_max(id[top[x]], id[x]));
                    x = father[top[x]];
                } else {
                    chkmax(ret, tree.query_max(id[top[y]], id[y]));
                    y = father[top[y]];
                }
            }  // while

            if (depth[x] > depth[y])
                swap(x, y);

            chkmax(ret, tree.query_max(id[x], id[y]));

            printf("%d\n", ret);
        } else {  // QSUM
            int ret = 0;

            while (top[x] != top[y]) {
                if (depth[top[x]] > depth[top[y]]) {
                    ret += tree.query_sum(id[top[x]], id[x]);
                    x = father[top[x]];
                } else {
                    ret += tree.query_sum(id[top[y]], id[y]);
                    y = father[top[y]];
                }
            }  // while

            if (depth[x] > depth[y])
                swap(x, y);

            ret += tree.query_sum(id[x], id[y]);

            printf("%d\n", ret);
        }
    }  // while

    return 0;
}  // function main
