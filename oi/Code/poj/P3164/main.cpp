#define NDEBUG
#define NDEBUGINFO

#pragma GCC optimize(3)

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NDEBUGINFO
#define DEBUG(msg, ...) printf(msg, __VA_ARGS__);
#else
#define DEBUG(...)
#endif
#define cls(arr) memset(arr, 0, sizeof(arr));

#define NMAX 200000
#define MMAX 400000
#define INF 1e99
#define HEAP_MEMMAX (MMAX + NMAX + 10)
#define CNTMAX 2 * NMAX

struct Edge {
    Edge(int _u, int _v, double _w) : u(_u), v(_v), w(_w) {}

    int u, v;
    double w;
};

static int n, m;
static double X[NMAX + 10], Y[NMAX + 10];
static vector<Edge *> G[NMAX + 10];

inline double dist(int i, int j) {
    return hypot(X[i] - X[j], Y[i] - Y[j]);
}

void initialize() {
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", X + i, Y + i);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u == v) continue;
        G[u].push_back(new Edge(u, v, dist(u, v)));
    }
}

// Pairing Heap
struct Node {
    Node() : e(NULL), mark(0.0), head(0), nxt(0) {}

    Edge *e;
    double mark;
    int head, nxt;

    double w() const {
        return e->w + mark;
    }
};

static int _pos;
Node hp[HEAP_MEMMAX];

int makehp(Edge *e) {
    int x = ++_pos;
    hp[x].e = e;
    return x;
}

int hp_merge(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    if (hp[x].w() > hp[y].w()) swap(x, y);
    hp[y].mark -= hp[x].mark;
    hp[y].nxt = hp[x].head;
    hp[x].head = y;
    return x;
}

int extract(int h) {
    static int tmp[HEAP_MEMMAX], cnt, last;
    if (!hp[h].head) return 0;

    last = cnt = 0;
    for (int x = hp[h].head, y; x; x = y) {
        hp[x].mark += hp[h].mark;
        y = hp[x].nxt;
        hp[x].nxt = 0;
        if (last) {
            tmp[cnt++] = hp_merge(last, x);
            last = 0;
        } else last = x;
    }
    
    if (last) tmp[cnt++] = last;
    for (int i = 1; i < cnt; i++)
        tmp[i] = hp_merge(tmp[i - 1], tmp[i]);
    return tmp[cnt - 1];
}

// Union-Find DS
static int fn[CNTMAX + 10];

void set(int x, int y) {
    fn[x] = y;
}

int id(int x) {
    return fn[x] ? fn[x] = id(fn[x]) : x;
}

// MAIN ALGO BEGIN

struct Cycle {
    Cycle(int _x) : x(_x), H(0), head(NULL), fa(NULL), nxt(NULL) {}

    int x, H;
    int in, out;
    Cycle *head, *fa, *nxt;
};


bool test(int r) {
    static bool mark[NMAX + 10];
    cls(mark);

    queue<int> q;
    q.push(r);
    mark[r] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;
            if (!mark[v]) {
                mark[v] = true;
                q.push(v);
            }
        }
    }

#ifdef NDEBUG
    return memchr(mark + 1, 0, sizeof(mark)) > mark + n;
#else
    return rawmemchr(mark + 1, 0) > mark + n;
#endif
}

#ifndef NDEBUGINFO
void print_tree(Cycle *x) {
    printf("%d: ", x->x);
    if (x->head) {
        Cycle *t = x->head, *e = x->head;
        do {
            printf("%d ", t->x);
            t = t->nxt;
        } while (t != e);
    }
    puts("");

    if (x->head) {
        Cycle *t = x->head, *e = x->head;
        do {
            print_tree(t);
            t = t->nxt;
        } while (t != e);
    }
}
#else
void print_tree(Cycle *x) {}
#endif

static Cycle *ptr[CNTMAX + 10];
static Edge *in[CNTMAX + 10], *tree[CNTMAX + 10];

Cycle* contract() {
    int cnt = n;
    stack<int> stk;
    stk.push(1);
    for (int i = 1; i < n || stk.size() > 1;) {
        int x = stk.top(), &H = ptr[x]->H, u;
        double w;
        Edge *e;
        do {
            assert(H);
            e = hp[H].e;
            w = hp[H].w();
            H = extract(H);
            u = id(e->u);
        } while (u == x);
        DEBUG("edge: %d (%d) -> %d (%d) (%6lf)\n", e->u, id(e->u), e->v, id(e->v), e->w);
        in[x] = new Edge(*e);
        in[x]->w = w;

        if (in[u]) {
            cnt++;
            ptr[cnt] = new Cycle(cnt);
            ptr[cnt]->head = ptr[x];
            DEBUG("new: %d\n", cnt);

#define ADD(x) \
            set(x, cnt); \
            hp[ptr[x]->H].mark -= in[x]->w; \
            ptr[cnt]->H = hp_merge(ptr[cnt]->H, ptr[x]->H);

            do {
                ADD(x);
                DEBUG("%d ", x);
                stk.pop();
                ptr[x]->nxt = ptr[stk.top()];
                ptr[x]->fa = ptr[cnt];
                x = stk.top();
            } while (x != u);
            stk.pop();
            ADD(u);
            DEBUG("%d\n", u);
            ptr[u]->nxt = ptr[cnt]->head;
            ptr[u]->fa = ptr[cnt];
            stk.push(cnt);
        } else {
            DEBUG("add: %d\n", u);
            i++;
            stk.push(u);
        }
    }

    print_tree(ptr[cnt]);
    return ptr[cnt];
}

static int tm;

void dfs(Cycle *r) {
    r->in = ++tm;

    if (r->head) {
        Cycle *y = r->head;
        do {
            dfs(y);
            y = y->nxt;
        } while (y != r->head);
    }

    r->out = tm;
}

#define rep(r) for (Cycle *p = r->nxt; p != r; p = p->nxt) \
        expand(p, in[p->x]);

void expand(Cycle *r, Edge *e) {
    DEBUG("expand: %d\n", r->x);
    if (r->x <= n) tree[r->x] = e;
    else {
        int t = e->v;
        if (r->head) {
            Cycle *y = r->head;
            for (; ptr[t]->in < y->in || ptr[t]->in > y->out; y = y->nxt) ;
            expand(y, e);
            rep(y);
        }
    }
}

void expand(Cycle *r) {
    if (!r->fa) return;

    rep(r);
    expand(r->fa);
}

double mdst(int r) {
    if (!test(r)) return INF;

    for (int u = 1; u <= n; u++) {
        ptr[u] = new Cycle(u);
        G[u].push_back(new Edge(u, u < n ? u + 1 : 1, INF));
    }

    for (int u = 1; u <= n; u++) for (size_t i = 0; i < G[u].size(); i++) {
        Edge *e = G[u][i];
        int v = e->v;
        ptr[v]->H = hp_merge(ptr[v]->H, makehp(e));
    }

    Cycle *ds = contract();
    dfs(ds);
    expand(ptr[r]);

    double ret = 0.0;
    for (int u = 1; u <= n; u++) {
        if (u != r)
            ret += dist(tree[u]->u, tree[u]->v);
    }
    return ret;
}

// MAIN ALGO END

void finalize() {
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < G[u].size(); i++)
            delete G[u][i];
        G[u].clear();
    }

    _pos = 0;
    cls(hp);

    cls(fn);

    for (int i = 1; ptr[i]; i++)
        delete ptr[i];
    tm = 0;
    cls(ptr) cls(in) cls(tree);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        initialize();

        double ans = mdst(1);
        if (ans >= INF) puts("poor snoopy");
        else printf("%.2f\n", ans);

        finalize();
    }

    return 0;
}
