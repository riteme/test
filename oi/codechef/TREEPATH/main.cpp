#define NDEBUG

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 1000000007

typedef long long i64;

inline void add(i64 &a, i64 b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

struct Node {
    Node(int _key, i64 _val)
        : key(_key), km(0), weight(rand()), size(1),
          val(_val), sum(_val), vm(1), lch(NULL), rch(NULL) {}

    int key, km, weight, size;
    i64 val, sum, vm;
    Node *lch, *rch;

    i64 rsum() const {
        return sum * vm;  // no mod
    }

    void push() {
        if (km) {
            key += km;
            if (lch) lch->km += km;
            if (rch) rch->km += km;
            km = 0;
        }
        if (vm != 1) {
            val = val * vm % MOD;
            sum = sum * vm % MOD;
            if (lch) lch->vm = lch->vm * vm % MOD;
            if (rch) rch->vm = rch->vm * vm % MOD;
            vm = 1;
        }
    }

    void update() {
        size = 1 + (lch ? lch->size : 0) + (rch ? rch->size : 0);
        sum = (val + (lch ? lch->rsum() : 0) + (rch ? rch->rsum() : 0)) % MOD;
    }
};

typedef pair<Node*, Node*> NodePair;

#ifndef NDEBUG
#define DEBUG(str, ...) fprintf(stderr, str, __VA_ARGS__)
inline void print(Node *x, int km = 0, i64 vm = 1) {
    if (!x) return;
    km += x->km;
    vm = vm * x->vm % MOD;
    print(x->lch, km, vm);
    DEBUG("%3d: %3lld, %3lld\n", x->key + km, x->val * vm % MOD, x->sum * vm % MOD);
    print(x->rch, km, vm);
}
#else
#define DEBUG(...)
#define print(...)
#endif

NodePair split(Node *x, int key) {
    if (!x) return {NULL, NULL};
    x->push();
    NodePair ret;
    if (x->key >= key) {
        ret = split(x->lch, key);
        x->lch = ret.second;
        ret.second = x;
    } else {
        ret = split(x->rch, key);
        x->rch = ret.first;
        ret.first = x;
    }
    x->update();
    return ret;
}

Node *zip(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;
    if (x->weight < y->weight) {
        x->push();
        x->rch = zip(x->rch, y);
        x->update();
        return x;
    } else {
        y->push();
        y->lch = zip(x, y->lch);
        y->update();
        return y;
    }
}

template <typename ... TNodes>
Node *zip(Node *x, Node *y, TNodes* ... nodes) {
    return zip(zip(x, y), nodes...);
}

Node *zip(const NodePair &xs) {
    return zip(xs.first, xs.second);
}

Node *meld(Node *x, Node *y) {
    if (!x) return y;
    if (!y) return x;
    if (x->size > y->size) swap(x, y);
    x->push();
    auto lch = x->lch, rch = x->rch;
    x->lch = x->rch = NULL;
    x->update();
    auto ys = split(y, x->key);
    return zip(meld(lch, ys.first), x, meld(rch, ys.second));
}

static int n, A[NMAX + 10];
static vector<int> T[NMAX + 10];

inline i64 query(Node *&x, int key = 0) {
    if (!x) return 1;
    auto xs = split(x, key);
    i64 ret = xs.second ? xs.second->sum : 0;  // rsum?
    x = zip(xs);
    return ret;
}

struct State {
    Node *tr = NULL;
    i64 val = 0;
};

i64 eval(Node *x, Node *&y, int w) {
    if (!x) return 0;
    x->push();
    auto ys = split(y, -(w + x->key));
    i64 ret = x->val * (ys.second ? ys.second->sum : 0) % MOD;
    y = zip(ys);
    return (ret + eval(x->lch, y, w) + eval(x->rch, y, w)) % MOD;
}

State dp(int x, int fa = 0) {
    State ret;
    i64 pr = 1;
    for (int v : T[x]) {
        if (v == fa) continue;
        auto dat = dp(v, x);
        i64 a = query(dat.tr) + dat.val;
        if (ret.tr) {
            ret.val = ret.val * a % MOD;
            add(ret.val, ret.tr->size < dat.tr->size ?
                eval(ret.tr, dat.tr, A[x]) : eval(dat.tr, ret.tr, A[x]));
            ret.tr->vm = ret.tr->vm * a % MOD;
        }
        dat.tr->vm = dat.tr->vm * pr % MOD;
        pr = pr * a % MOD;
        ret.tr = meld(dat.tr, ret.tr);
    }
    if (ret.tr) ret.tr->km += A[x];
    ret.tr = meld(new Node(A[x], pr), ret.tr);
    DEBUG("x = %d [%2d], val = %lld\n", x, A[x], ret.val);
    print(ret.tr);
    return ret;
}

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        T[i].clear();
        scanf("%d", A + i);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        T[u].push_back(v);
        T[v].push_back(u);
    }
}

int main() {
    srand(1550127079);
    DEBUG("seed = %ld\n", time(NULL));
    int T;
    scanf("%d", &T);
    while (T--) {
        initialize();
        auto x = dp(1);
        printf("%lld\n", (query(x.tr) + x.val) % MOD);
    }
    return 0;
}
