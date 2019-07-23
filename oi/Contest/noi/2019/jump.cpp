// 300MB MLE
#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cctype>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

inline void read(int &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

#define NMAX 70000
#define NODEMAX 2400000
#define SEGMAX 270000

#define L(x) (x << 1)
#define R(x) ((x << 1) | 1)

static int cnt;

struct Node {
    //Node() : id(++cnt), lch(NULL), rch(NULL) {
    //    assert(cnt < NODEMAX);
    //}

    int id;
    Node *lch, *rch;
};

static size_t mempos;
static Node *mem;

inline Node *alloc() {
    Node *r = &mem[mempos++];
    r->id = ++cnt;
    r->lch = r->rch = NULL;
    return r;
}

struct Edge {
    int v, w;
};

struct State {
    State(int _u, int _s) : u(_u), s(_s) {}

    int u, s;

    bool operator<(const State &z) const {
        return s > z.s;
    }
};

static int n, m, W, H;
static int pos[NMAX + 10];
static Node **tr;
static vector<Edge> G[NODEMAX];

inline void link(int u, int v, int w = 0) {
    G[u].push_back({v, w});
}

static void insert(Node *x, int p, int xl, int xr) {
    if (xl == xr) return;
    int m = (xl + xr) >> 1;
    if (p <= m) {
        if (!x->lch) {
            x->lch = alloc();
            link(x->id, x->lch->id);
        }
        insert(x->lch, p, xl, m);
    } else {
        if (!x->rch) {
            x->rch = alloc();
            link(x->id, x->rch->id);
        }
        insert(x->rch, p, m + 1, xr);
    }
}

static void insert(int i, int x, int y) {
    int rt = 1, l = 1, r = W;
    while (l < r) {
        int m = (l + r) >> 1;
        if (x <= m) r = m, rt = L(rt);
        else l = m + 1, rt = R(rt);
    }
    if (!tr[rt]) tr[rt] = alloc();
    insert(tr[rt], y, 1, H);
    pos[i] = cnt;
}

static Node *meld(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;
    Node *z = alloc();
    z->lch = meld(x->lch, y->lch);
    z->rch = meld(x->rch, y->rch);
    if (z->lch) link(z->id, z->lch->id);
    if (z->rch) link(z->id, z->rch->id);
    if (!z->lch && !z->rch) {
        link(z->id, x->id);
        link(z->id, y->id);
    }
    return z;
}

static void setup(int x, int xl, int xr) {
    assert(x <= 300000);
    if (xl == xr) return;
    int m = (xl + xr) >> 1;
    setup(L(x), xl, m);
    setup(R(x), m + 1, xr);
    tr[x] = meld(tr[L(x)], tr[R(x)]);
}

static int t, Li, Ri, Di, Ui;
static bool mark[NODEMAX];
static int stk[1024], tail;
static void cover(Node *x, int p, int xl, int xr) {
    if (!x) return;
    if (Di <= xl && xr <= Ui && !mark[x->id]) {
        link(p, x->id, t);
        mark[x->id] = true;
        stk[tail++] = x->id;
    } else {
        int m = (xl + xr) >> 1;
        if (Di <= m) cover(x->lch, p, xl, m);
        if (Ui > m) cover(x->rch, p, m + 1, xr);
    }
}

static void _cover(int x, int p, int xl, int xr) {
    if (Li <= xl && xr <= Ri) cover(tr[x], p, 1, H);
    else {
        int m = (xl + xr) >> 1;
        if (Li <= m) _cover(L(x), p, xl, m);
        if (Ri > m) _cover(R(x), p, m + 1, xr);
    }
}

static void cover(int x, int p, int xl, int xr) {
    _cover(x, p, xl, xr);
    while (tail) mark[stk[--tail]] = false;
}

inline void initialize() {
    mem = new Node[NODEMAX];
    tr = new Node*[SEGMAX];
    //scanf("%d%d%d%d", &n, &m, &W, &H);
    read(n); read(m); read(W); read(H);
    for (int i = 1; i <= n; i++) {
        int x, y;
        //scanf("%d%d", &x, &y);
        read(x); read(y);
        insert(i, x, y);
    }
    setup(1, 1, W);
    for (int i = 0; i < m; i++) {
        int p;
        //scanf("%d%d%d%d%d%d", &p, &t, &Li, &Ri, &Di, &Ui);
        read(p); read(t); read(Li); read(Ri); read(Di); read(Ui);
        cover(1, pos[p], 1, W);
    }
    delete[] mem;
    delete[] tr;
}

static int dist[NODEMAX];

int main() {
#ifdef NDEBUG
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
#endif
    initialize();

    memset(dist, 0x3f, sizeof(dist));
    dist[pos[1]] = 0;
    priority_queue<State> q;
    q.push(State(pos[1], 0));
    while (!q.empty()) {
        State s = q.top();
        q.pop();
        if (s.s != dist[s.u]) continue;
        int u = s.u;
        for (auto &e : G[u]) {
            int v = e.v;
            if (dist[v] > dist[u] + e.w) {
                dist[v] = dist[u] + e.w;
                q.push(State(v, dist[v]));
            }
        }
    }

    for (int i = 2; i <= n; i++) printf("%d\n", dist[pos[i]]);
    //fprintf(stderr, "cnt = %d\n", cnt);
    return 0;
}
