#include <cstdio>
#include <cctype>
#include <cstring>

#include <algorithm>

using namespace std;

char buf[65536];
int pos = 65536;

char _getchar() {
    if (pos == sizeof(buf)) {
        pos = 0;
        fread(buf, 1, sizeof(buf), stdin);
    }
    return buf[pos++];
}

int readi() {
    int x = 0;
    char c;
    do {
        c = _getchar();
    } while (!isalnum(c));
    do {
        x = x * 10 + c - '0';
        c = _getchar();
    } while (isalnum(c));
    return x;
}

constexpr int NMAX = 300000;
constexpr int QMAX = 300000;
constexpr int DMAX = 1000000;

struct Node {
    int size;
    int pos;
    int lc, rc;

    void reset() {
        size = 1;
        pos = 0;
        lc = 0;
        rc = 0;
    }

    void fetch();
};

int memcnt = 1;
Node mem[50001000];
Node *nalloc() {
    Node *x = mem + memcnt;
    memcnt++;
    return x;
}

void Node::fetch()  {
        size = 1;
        if (lc)
            size += mem[lc].size;
        if (rc)
            size += mem[rc].size;
    }

struct NPair {
    Node *a, *b;
};

NPair split(Node *x, int k) {
    if (x == mem)
        return {mem + 0, mem + 0};
    x = (Node *)memcpy(nalloc(), x, sizeof(*x));
    NPair ret;
    int ls = x->lc ? mem[x->lc].size : 0;
    if (ls + 1 <= k) {
        ret = split(mem + x->rc, k - ls - 1);
        x->rc = ret.a - mem;
        ret.a = x;
    } else {
        ret = split(mem + x->lc, k);
        x->lc = ret.b - mem;
        ret.b = x;
    }
    x->fetch();
    return ret;
}

unsigned xorshift32() {
	static unsigned int x = 0x19260817;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

bool fuck_mode = false;
int maxd = 0;
Node *join(Node *x, Node *y, int d) {
    maxd = max(maxd, d);
    if (x == mem)
        return y;
    if (y == mem)
        return x;
    bool xtop;
    if (!fuck_mode) {
        int k = xorshift32() % (x->size + y->size);
        xtop = k < x->size;
    } else {
        xtop = abs(mem[x->lc].size - mem[x->rc].size - y->size) <
               abs(mem[y->lc].size + x->size - mem[y->rc].size);
    }
    if (xtop) {
        x = (Node *)memcpy(nalloc(), x, sizeof(*x));
        x->rc = join(mem + x->rc, y, d + 1) - mem;
        x->fetch();
        return x;
    } else {
        y = (Node *)memcpy(nalloc(), y, sizeof(*y));
        y->lc = join(x, mem + y->lc, d + 1) - mem;
        y->fetch();
        return y;
    }
}

Node *search(Node *x, int k) {
    if (x == mem)
        return mem + 0;
    int ls = x->lc ? mem[x->lc].size : 0;
    if (k < ls + 1) {
        return search(mem + x->lc, k);
    } else if (k > ls + 1) {
        return search(mem + x->rc, k - ls - 1);
    } else {
        return x;
    }
}

int v[DMAX * 2 + 10];

Node *build(int l, int r) {
    if (r < l)
        return mem + 0;

    Node *x = nalloc();
    x->reset();
    int m = (l + r) / 2;
    x->pos = v[m];
    x->lc = build(l, m - 1) - mem;
    x->rc = build(m + 1, r) - mem;
    x->fetch();
    return x;
}

int n, q;
int X[NMAX + 10];
int D[QMAX + 10];

Node *cut(Node *x, int l, int r) {
    l += DMAX + 1;
    r += DMAX + 1;
    NPair p = split(x, l - 1);
    NPair q = split(p.b, r - l + 1);
    return q.a;
}

int last;
void scan(Node *x) {
    if (x == mem)
        return;
    scan(mem + x->lc);
    v[++last] = x->pos;
    scan(mem + x->rc);
}

int main() {
    srand(0x19260817);
    mem[0].reset();

    // scanf("%d%d", &n, &q);
    n = readi();
    q = readi();
    for (int i = 1; i <= n; i++) {
        // scanf("%d", X + i);
        X[i] = readi();
    }
    for (int i = 1; i <= q; i++) {
        // scanf("%d", D + i);
        D[i] = readi();
        maxd = max(maxd, D[i]);
    }

    for (int i = 1; i <= 2 * DMAX + 1; i++) {
        v[i] = i - DMAX - 1;
    }
    Node *t = build(1, 2 * DMAX + 1);
    for (int i = q; i >= 1; i--) {
        int d = D[i];
        Node *l = cut(t, -DMAX + d, -1 + d);
        Node *z = nalloc();
        z->reset();
        z->pos = -DMAX - i;
        Node *r = cut(t, 1 - d, DMAX - d);
        maxd = 0;
        t = join(l, join(z, r, 0), 0);
        if (maxd > 100)
            fuck_mode = true;

        if (memcnt > 50000000) {
            last = 0;
            scan(t);
            memcnt = 1;
            t = build(1, 2 * DMAX + 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        int x = X[i];
        Node *y = search(t, DMAX + 1 + x);
        if (y->pos < -DMAX)
            printf("Yes %d\n", -(DMAX + y->pos) - 1);
        else
            printf("No %d\n", y->pos);
    }

    fprintf(stderr, "%d\n", memcnt);

    return 0;
}
