#include <ctime>
#include <cstdio>
#include <cctype>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

#define MEMSIZE 100000000
static unsigned char mem[MEMSIZE];
static size_t _pos;

inline void clear() {
    //fprintf(stderr, "_pos = %zu\n", _pos);
    _pos = 0;
}

void *operator new(size_t cnt) {
    void *ptr = mem + _pos;
    _pos += cnt;
    return ptr;
}

#define NMAX 100000

#define ACM_BEGIN
#define SIGMA 27
#define EOFC (SIGMA - 1)
struct State {
    struct Trans {
        Trans(int _l, int _r, State *_nxt)
            : l(_l), r(_r), nxt(_nxt) {}
        int l, r; State *nxt;
#define ACM_END
        int p = 0;
#define ACM_BEGIN
        int len() const { return r - l + 1; }
    };
    State() : fail(NULL) { memset(ch, 0, sizeof(ch)); }
    State *fail; Trans *ch[SIGMA];
};
typedef State::Trans Trans;
#define ACM_END

#define ACM_BEGIN
static State *rt;
static char str[NMAX + 10];
static int n;
#define ACM_END
static int K;

#define ACM_BEGIN
namespace _append {
static char dir = -1;
static int len, cnt, cur;
static State *ap;
void reset() {
    dir = -1; ap = rt;
    len = cnt = cur = 0;
}}
inline void append(char c) {
    using namespace _append;
    cnt++; cur++;
    State *x, *y = NULL;
    while (cnt) {
        if (cnt <= len + 1) {
            len = cnt - 1;
            dir = len ? str[cur - len] : -1;
        }
        while (dir >= 0 && len >= ap->ch[dir]->len()) {
            len -= ap->ch[dir]->len();
            ap = ap->ch[dir]->nxt;
            dir = len ? str[cur - len] : -1;
        }
        if ((dir >= 0 && str[ap->ch[dir]->l + len] == c) ||
            (dir < 0 && ap->ch[c])) {
            if (dir < 0) dir = c;
            if (y) y->fail = ap;
            len++; return;
        }
        if (dir < 0) {
            ap->ch[c] = new Trans(cur, n, new State);
            x = ap;
        } else {
            Trans *t = ap->ch[dir];
            x = new State;
            x->ch[c] = new Trans(cur, n, new State);
            x->ch[str[t->l + len]] = new Trans(t->l + len, t->r, t->nxt);
            t->r = t->l + len - 1;
            t->nxt = x;
        }
        if (y) y->fail = x;
        if (ap != rt) ap = ap->fail;
        y = x; cnt--;
}}
#define ACM_END

struct Treap {
    Treap(int _key, int _val)
        : wt(rand()), key(_key), val(_val), sum(_val), lch(NULL), rch(NULL) {}
    int wt, key, val, sum;
    Treap *lch, *rch;

    void update() {
        sum = val + (lch ? lch->sum : 0) + (rch ? rch->sum : 0);
    }
};

inline Treap *lrot(Treap *x) {
    Treap *y = x->lch;
    x->lch = y->rch;
    y->rch = x;
    y->sum = x->sum;
    x->update();
    return y;
}

inline Treap *rrot(Treap *x) {
    Treap *y = x->rch;
    x->rch = y->lch;
    y->lch = x;
    y->sum = x->sum;
    x->update();
    return y;
}

void inc(Treap *&x, int key) {
    if (!x) x = new Treap(key, 1);
    else {
        if (key < x->key) {
            inc(x->lch, key);
            x->sum++;
            if (x->lch->wt < x->wt) x = lrot(x);
        } else if (key > x->key) {
            inc(x->rch, key);
            x->sum++;
            if (x->rch->wt < x->wt) x = rrot(x);
        } else {
            x->val++;
            x->sum++;
        }
    }
}

void dec(Treap *x, int key) {
    if (key < x->key) dec(x->lch, key);
    else if (key > x->key) dec(x->rch, key);
    else x->val--;
    x->sum--;
}

int query(Treap *x, int key) {
    if (!x) return 0;
    if (key < x->key) return query(x->lch, key);
    return (x->lch ? x->lch->sum : 0) + x->val + query(x->rch, key);
}

typedef set<int>::iterator Iterator;

inline Iterator pre(Iterator it) {
    it--;
    return it;
}

inline Iterator nxt(Iterator it) {
    it++;
    return it;
}

Treap* solve(State *x, set<int> *&q, int dep) {
    q = new set<int>;
    Treap *tr = NULL;
    for (char c = 0; c < SIGMA; c++) if (x->ch[c]) {
        Trans *t = x->ch[c];
        set<int> *qv;
        Treap *tv = solve(t->nxt, qv, dep + t->len());
        if (t->r == n) qv->insert(n - dep - t->len() + 1);
        int l = 1, r = t->len();
        while (l < r) {
            int m = (l + r) >> 1;
            if (qv->size() > K + query(tv, dep + m)) l = m + 1;
            else r = m;
        }
        if (qv->size() == K + query(tv, dep + l)) t->p = l;
        if (qv->size() > q->size()) {
            swap(q, qv);
            tr = tv;
        }
        Iterator hint = q->begin();
        for (Iterator it = qv->begin(); it != qv->end(); it++) {
            hint = q->insert(hint, *it);
            Iterator nx = nxt(hint);
            if (hint != q->begin()) {
                Iterator pr = pre(hint);
                if (nx != q->end()) dec(tr, *nx - *pr);
                inc(tr, *hint - *pr);
            }
            if (nx != q->end()) inc(tr, *nx - *hint);
        }
    }
    return tr;
}

static struct { int l, r; } stk[NMAX + 10];
static int cnt;
bool dfs(State *x) {
    for (char c = 0; c < SIGMA; c++) if (x->ch[c]) {
        Trans *t = x->ch[c];
        if (t->p) {
            stk[cnt = 0].l = t->l;
            stk[0].r = t->l + t->p - 1;
            return true;
        } else if (dfs(t->nxt)) {
            stk[++cnt].l = t->l;
            stk[cnt].r = t->r;
            return true;
        }
    }
    return false;
}
#define ACM_BEGIN
inline void initialize() {
#define ACM_END
    scanf("%s%d", str + 1, &K);
#define ACM_BEGIN
    rt = new State;
    _append::reset();
    n = strlen(str + 1) + 1;
    for (int i = 1; i < n; i++) {
        str[i] -= 'a';
        append(str[i]);
    }
    str[n] = EOFC;
    append(EOFC);
}
#define ACM_END

int main() {
    srand(time(NULL));
    int T;
    scanf("%d", &T);
    while (T--) {
        clear();
        initialize();
        set<int> *_;
        solve(rt, _, 0);
        if (dfs(rt)) {
            for (int i = cnt; i >= 0; i--) for (int j = stk[i].l; j <= stk[i].r; j++)
                putchar('a' + str[j]);
            puts("");
        } else puts("-1");
    }
    return 0;
}
