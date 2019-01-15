#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <random>
#include <algorithm>

using namespace std;

static unsigned short g_seed;

// Used to seed the generator.
inline void fast_srand(short seed) {
    g_seed = seed;
}

// Compute a pseudorandom integer.
// Output value in range [0, 32767]
inline short fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>8)&0x7FFF;
}

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline void getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c;
    do {
        getc(c);
    } while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        getc(c);
    } while (isdigit(c));
}

#define NMAX 10000

inline void chkmax(short &a, short b) {
    if (b > a) a = b;
}

static int n;

struct Treap {
    Treap(short _x, short _v)
        : w(fast_rand()), x(_x), v(_v), m(_v), lch(NULL), rch(NULL) {}

    short w, x, v, m;
    Treap *lch, *rch;

    void update() {
        m = min(v, min(lch ? lch->m : static_cast<short>(0), rch ? rch->m : static_cast<short>(0)));
    }
};

inline Treap *lrotate(Treap *x) {
    Treap *y = x->lch;
    x->lch = y->rch;
    y->rch = x;
    y->m = x->m;
    x->update();
    return y;
}

inline Treap *rrotate(Treap *x) {
    Treap *y = x->rch;
    x->rch = y->lch;
    y->lch = x;
    y->m = x->m;
    x->update();
    return y;
}

Treap *insert(Treap *u, short x, short v) {
    if (!u) return new Treap(x, v);
    chkmax(u->m, v);
    if (x > u->x) {
        u->rch = insert(u->rch, x, v);
        if (u->rch->w < u->w) return rrotate(u);
    } else if (x < u->x) {
        u->lch = insert(u->lch, x, v);
        if (u->lch->w < u->w) return lrotate(u);
    } else chkmax(u->v, v);
    return u;
}

short query(Treap *u, short x) {
    if (!u) return 0;
    if (x < u->x) return query(u->lch, x);
    short ret = max(u->lch ? u->lch->m : static_cast<short>(0), u->v);
    if (x > u->x) chkmax(ret, query(u->rch, x));
    return ret;
}

struct Node {
    Node() : dat(NULL), lch(NULL), rch(NULL) {}
    Treap *dat;
    Node *lch, *rch;
};

static short x, y, v;

Node *insert(Node *u, short ul, short ur) {
    if (!u) u = new Node;
    u->dat = insert(u->dat, y, v);
    if (ul != ur) {
        short m = (ul + ur) >> 1;
        if (x <= m) u->lch = insert(u->lch, ul, m);
        else u->rch = insert(u->rch, m + 1, ur);
    }
    return u;
}

short query(Node *u, short ul, short ur) {
    if (!u) return 0;
    if (ur <= x) return query(u->dat, y);
    short m = (ul + ur) >> 1;
    short ret = query(u->lch, ul, m);
    if (x > m) chkmax(ret, query(u->rch, m + 1, ur));
    return ret;
}

Node *bit[NMAX + 10];

void insert(short X, short Y, short Z, short V) {
    for (; X <= n; X += X & -X) {
        x = Y;
        y = Z;
        v = V;
        bit[X] = insert(bit[X], 1, n);
    }
}

short query(short X, short Y, short Z) {
    short ret = 0;
    for (; X; X -= X & -X) {
        x = Y;
        y = Z;
        chkmax(ret, query(bit[X], 1, n));
    }
    return ret;
}

static short pos[NMAX + 10][4][4];
static short dp[8];

void readseq(int k) {
    for (int i = 1; i <= n; i++) {
        int x;
        // scanf("%d", &x);
        read(x);
        if (!pos[x][k][0]) pos[x][k][0] = i;
        else pos[x][k][1] = i;
    }
}

int main() {
    fast_srand(19260817);
    // scanf("%d", &n);
    read(n);
    readseq(0); readseq(1); readseq(2);

    short ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        // scanf("%d", &x);
        read(x);
        for (int s = 0; s < 8; s++) {
            int a = pos[x][0][s & 1];
            int b = pos[x][1][(s & 2) >> 1];
            int c = pos[x][2][(s & 4) >> 2];
            if (!a || !b || !c) continue;
            dp[s] = query(a - 1, b - 1, c - 1) + 1;
            chkmax(ans, dp[s]);
        }

        for (int s = 0; s < 8; s++) {
            int a = pos[x][0][s & 1];
            int b = pos[x][1][(s & 2) >> 1];
            int c = pos[x][2][(s & 4) >> 2];
            if (!a || !b || !c) continue;
            insert(a, b, c, dp[s]);
        }
    }

    printf("%d\n", static_cast<int>(ans));
    return 0;
}
