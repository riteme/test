//#define NDEBUG

#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 250000
#define RANDMAX 10000
#define INF 0x3f3f3f3f3f3f3f3f

typedef long long i64;

inline int rnd() {
	return rand() % RANDMAX;
}

struct Node {
	Node() : key(0), km(0), size(1), val(0), vm(0),
		lch(NULL), rch(NULL) {}
	int key, km, size;
	i64 val, vm;
	Node *lch, *rch;

    void push() {
        if (lch) lch = new Node(*lch);
        if (rch) rch = new Node(*rch);
        if (km) {
            key += km;
            if (lch) lch->km += km;
            if (rch) rch->km += km;
            km = 0;
        }
        if (vm) {
            val += vm;
            if (lch) lch->vm += vm;
            if (rch) rch->vm += vm;
            vm = 0;
        }
    }

	void update() {
		size = 1 + (lch ? lch->size : 0) + (rch ? rch->size : 0);
	}
};

inline Node *cpy(Node *x) {
	return new Node(*x);
}

void _split(Node *x, int key, Node *&a, Node *&b) {
	if (!x) a = b = NULL;
	else {
        x->push();
		if (key < x->key) {
			_split(x->lch, key, a, b);
			x->lch = b;
			b = x;
		} else {
			_split(x->rch, key, a, b);
			x->rch = a;
			a = x;
		}
		x->update();
	}
}

void split(Node *x, int key, Node *&a, Node *&b) {
    _split(cpy(x), key, a, b);
}

Node *_meld(Node *x, Node *y) {
	if (!x) return cpy(y);
	if (!y) return cpy(x);
	if (rnd() * (x->size + y->size) >= RANDMAX * y->size) {
        x->push();
		x->rch = _meld(x->rch, y);
		x->update();
		return x;
	}
    y->push();
	y->lch = _meld(x, y->lch);
	y->update();
	return y;
}

Node *meld(Node *x, Node *y) {
    if (!x) return cpy(y);
    if (!y) return cpy(x);
    return _meld(cpy(x), cpy(y));
}

struct NodeData {
    int key;
    i64 val;
};

NodeData get(Node *x, int key, int km = 0, i64 vm = 0) {
    if (!x) return NodeData{-1, 0};
    km += x->km;
    vm += x->vm;
	if (key < x->key + km) return get(x->lch, key, km, vm);
	if (key > x->key + km) return get(x->rch, key, km, vm);
	return NodeData{x->key + km, x->val + vm};
}

i64 f(Node *x, Node *y, int key) {
	return get(x, key).val - get(y, key).val;
}

Node *rconmax(Node *x, Node *y, int l, int r) {
    if (f(y, x, r) < 0) swap(x, y);
    while (l < r) {
        int m = (l + r) >> 1;
        if (f(y, x, m) > 0) r = m;
        else l = m + 1;
    }
    if (l == r && f(y, x, r) == 0) return x;
    Node *ret, *_;
    split(x, l - 1, ret, _);
    split(y, l - 1, _, y);
    return meld(ret, y);
}

Node *conmax(Node *x, Node *y, int ykey = 0, i64 yval = 0, int xpad = 0, int ypad = 0, int lmar = 0) {
    if (!y) return cpy(x);
    y = cpy(y);
	y->km += ykey;
	y->vm += yval;
    if (!x) return y;
    x = cpy(x);
	int l = lmar + ypad + ykey, r = min(xpad + x->size, ypad + y->size + ykey) - 1;
	if (l > r) return meld(x, y);
	Node *x1, *x2, *x3, *y1, *y2, *y3;
	split(x, l - 1, x1, x2);
	split(x2, r, x2, x3);
    split(y, l - 1, y1, y2);
	split(y2, r, y2, y3);
	return meld(x1, meld(rconmax(x2, y2, l, r), y3 ? y3 : x3));
}

Node *conmeld(Node *x, Node *y, int km = 0, i64 vm = 0) {
	if (!x) return NULL;
    km += x->km;
    vm += x->vm;
	Node *ret = conmax(conmeld(x->lch, y, km, vm), y, x->key + km, x->val + vm, x->key + km - (x->lch ? x->lch->size : 0));
	return conmax(ret, conmeld(x->rch, y, km, vm), 0, 0, x->key + km - (x->lch ? x->lch->size : 0), x->key + km + 1);
}

void _print(Node *x, int km = 0, i64 vm = 0) {
    if (!x) return;
    km += x->km;
    vm += x->vm;
    _print(x->lch, km, vm);
    if (x->val <= -INF/2) printf("[%d: -INF] ", x->key + km);
    else printf("[%d: %lld] ", x->key + km, x->val + vm);
    _print(x->rch, km, vm);
}

void print(Node *x) {
    _print(x);
    putchar('\n');
}

struct Edge {
	int v, w;
};

static int n, K, sz[NMAX + 10];
static vector<Edge *> T[NMAX + 10];
static Node *dp[NMAX + 10][3];

void dfs1(int x, int f) {
	sz[x] = 1;
	for (auto e : T[x]) {
		int v = e->v;
		if (v == f) continue;
		dfs1(v, x);
		sz[x] += sz[v];
	}
}

void dfs2(int x, int f) {
	int u = 0;
	Edge *ue;
	for (auto e : T[x]) {
		int v = e->v;
		if (v != f && sz[v] > sz[u]) {
			u = v;
			ue = e;
		}
	}
	if (u) {
        dfs2(u, x);
		dp[x][0] = dp[u][2];
		dp[x][1] = cpy(dp[u][0]);
        Node *inv = new Node;
        inv->val = -INF;
		dp[x][1]->km++;
		dp[x][1]->vm += ue->w;
        dp[x][1] = meld(inv, dp[x][1]);
	} else {
		dp[x][0] = dp[x][1] = dp[x][2] = new Node;
		return;
	}

	for (auto e : T[x]) {
		int v = e->v;
		if (v == f || v == u) continue;
        dfs2(v, x);
		Node *ve = cpy(dp[v][0]), *inv = new Node;  // no copy?
		ve->km++;
		ve->vm += e->w;
        inv->val = -INF;
        ve = meld(inv, ve);
		dp[x][1] = conmax(conmeld(dp[v][2], dp[x][1]), conmeld(ve, dp[x][0]), 0, 0, 0, 0, 1);
		dp[x][0] = conmeld(dp[v][2], dp[x][0]);
	}
	dp[x][2] = conmax(dp[x][0], dp[x][1]);
#ifndef NDEBUG
    printf("x = %d\n", x);
    print(dp[x][0]);
    print(dp[x][1]);
    print(dp[x][2]);
#endif
}

int main() {
	srand(1547880015);
    //printf("%ld\n", time(NULL));
	scanf("%d%d", &n, &K);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		T[u].push_back(new Edge{v, w});
		T[v].push_back(new Edge{u, w});
	}

	dfs1(1, 0);
	dfs2(1, 0);
	NodeData ret = get(dp[1][2], K);
	if (ret.key < 0 || ret.val <= -INF/2) puts("Impossible");
	else printf("%lld\n", ret.val);

	return 0;
}
#include <vector>
