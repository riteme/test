#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

struct Heap {
    priority_queue<i64> q, q0;

    void push(i64 x) {
        q.push(x);
    }

    i64 top() {
        update();
        return q.top();
    }

    void pop(i64 x) {
        q0.push(x);
    }

    void clear() {
        while (!q.empty()) {
            q.pop();
        }
        while (!q0.empty()) {
            q0.pop();
        }
    }

    void update() {
        while (!q.empty() && !q0.empty() && q.top() == q0.top()) {
            q.pop();
            q0.pop();
        }
    }

    bool empty() {
        update();
        return q.empty();
    }
};

extern struct Node *null;

struct Node {
    Node()
    : wt(INT_MIN), key(0), key0(0),
      cnt(0), dp(0), dp0(0), maxv(0),
      lch(null), rch(null) {}

    int wt, key, key0, cnt;
    i64 dp, dp0, maxv;
    Node *lch, *rch;

    i64 rdp() {
        return this == null ? 0 : dp + dp0;
    }

    i64 rmaxv() {
        return this == null ? 0 : maxv + dp0;
    }

    void commit() {
        if (this == null)
            return;

        if (key0) {
            key += key0;
            lch->key0 += key0;
            rch->key0 += key0;
            key0 = 0;
        }

        if (dp0) {
            dp += dp0;
            maxv += dp0;
            lch->dp0 += dp0;
            rch->dp0 += dp0;
            dp0 = 0;
        }
    }

    void fetch() {
        cnt = 1 + lch->cnt + rch->cnt;
        maxv = max(dp, max(lch->rmaxv(), rch->rmaxv()));
    }
};

Node *null = new Node;

struct NodePair {
    NodePair() {}
    NodePair(Node *l, Node *r)
        : left(l), right(r) {}

    Node *left;
    Node *right;
};

NodePair split(Node *x, int key) {
    if (x == null)
        return NodePair(null, null);

    NodePair rax;
    x->commit();
    if (key <= x->key) {
        rax = split(x->lch, key);
        x->lch = rax.right;
        rax.right = x;
    } else {
        rax = split(x->rch, key);
        x->rch = rax.left;
        rax.left = x;
    }

    x->fetch();
    return rax;
}

Node *join(Node *x, Node *y) {
    if (x == null)
        return y;
    if (y == null)
        return x;

    if (x->wt < y->wt) {
        x->commit();
        x->rch = join(x->rch, y);
        x->fetch();
        return x;
    } else {
        y->commit();
        y->lch = join(x, y->lch);
        y->fetch();
        return y;
    }
}

Node *insert(Node *x, Node *y) {
    y->commit();
    NodePair p = split(x, y->key);
    return join(p.left, join(y, p.right));
}

Node *cover(Node *x, int l, int r, i64 v) {
    NodePair p1 = split(x, l);
    NodePair p2 = split(p1.right, r + 1);
    p2.left->dp0 += v;
    return join(p1.left, join(p2.left, p2.right));
}

Node mem[NMAX + 10];
int mempos;

Node *allocate(int key, i64 val) {
    Node *p = mem + mempos;
    mempos++;
    p->wt = rand();
    p->key = key;
    p->dp = val;
    p->maxv = val;
    p->cnt = 1;
    p->key0 = p->dp0 = 0;
    p->lch = p->rch = null;
    return p;
}

struct Bloom {
    Bloom(int _r, int _w)
        : r(_r), w(_w) {}

    int r, w;
};

struct Event {
    Event() {}
    Event(int _op, int _pos, i64 _val)
        : op(_op), pos(_pos), val(_val) {}

    int op;
    int pos;
    i64 val;

    bool operator<(const Event &z) const {
        return pos < z.pos || (pos == z.pos && op < z.op);
    }
};

int n, m, cnt;
vector<int> G[NMAX + 10];
vector<Bloom> B[NMAX + 10];
Event ev[NMAX * 2 + 10];

Node *dfs1(Node *x, Node *y) {
    if (y == null)
        return x;

    y->commit();
    int l = y->key + 1;
    int r = -l;
    NodePair p1 = split(x, r + 1);
    NodePair p2 = split(p1.left, l);
    y->dp0 = p2.left->rmaxv();
    x = join(join(p2.left, p2.right), p1.right);
    if (l <= r) {
        ev[cnt++] = Event(+1, l, y->dp);
        ev[cnt++] = Event(-1, r + 1, y->dp);
    }

    x = dfs1(x, y->lch);
    x = dfs1(x, y->rch);
    return x;
}

Node *dfs3(Node *x, Node *y) {
    if (y == null)
        return x;

    Node *lch = y->lch;
    Node *rch = y->rch;
    y->lch = y->rch = null;
    y->dp += y->dp0;
    y->dp0 = 0;
    y->fetch();
    x = insert(x, y);

    x = dfs3(x, lch);
    x = dfs3(x, rch);
    return x;
}

Node *meld(Node *x, Node *y) {
    if (x->cnt < y->cnt)
        swap(x, y);

    cnt = 0;
    x = dfs1(x, y);

    //x = dfs2(x, y);
    sort(ev, ev + cnt);
    Heap q;
    for (int i = 0; i < cnt - 1; i++) {
        if (ev[i].op > 0)
            q.push(ev[i].val);
        else
            q.pop(ev[i].val);

        int l = ev[i].pos, r = ev[i + 1].pos - 1;
        if (l <= r && !q.empty())
            cover(x, l, r, q.top());
    }

    x = dfs3(x, y);
    return x;
}

Node *dp(int x, int pa) {
    Node *tr = null;

    for (int i = 0; i < B[x].size(); i++) {
        Bloom &b = B[x][i];
        tr = insert(tr, allocate(b.r, b.w));
    }

    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == pa)
            continue;

        Node *ret = dp(v, x);
        ret->key0 -= 1;
        tr = meld(tr, ret);
    }

    return tr;
}

void _main() {
    srand(0x19260817);
    mempos = 0;

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        G[i].clear();
        B[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 0; i < m; i++) {
        int u, r, w;
        scanf("%d%d%d", &u, &r, &w);
        B[u].push_back(Bloom(r, w));
    }

    Node *ret = dp(1, 0);
    printf("%lld\n", ret->rmaxv());
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
