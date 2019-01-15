#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define NMAX 250000
#define RANDMAX 10000

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

	int gkey() {
		return key + km;
	}

	i64 gval() {
		return val + vm;
	}

	void push() {
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

void split(Node *x, int key, Node *&a, Node *&b) {
	if (!x) a = b = NULL;
	else {
		x = cpy(x);
		x->push();
		if (key < x->key) {
			split(x->lch, key, a, b);
			x->lch = b;
			b = x;
		} else {
			split(x->rch, key, a, b);
			x->rch = a;
			a = x;
		}
		x->update();
	}
}

Node *meld(Node *x, Node *y) {
	if (!x) return cpy(y);
	if (!y) return cpy(x);
	x = cpy(x);
	y = cpy(y);
	if (rnd() * (x->size + y->size) >= RANDMAX * y->size) {
		x->push();
		x->rch = meld(x->rch, y);
		x->update();
		return x;
	}
	y->push();
	y->lch = meld(x, y->lch);
	y->update();
	return y;
}

Node *get(Node *x, int key) {
	if (!x) return NULL;
	x->push();
	if (key < x->key) return get(x->lch, key);
	if (key > x->key) return get(x->rch, key);
	return x;
}

i64 f(Node *x, Node *y, int key) {
	return get(x, key)->gval() - get(y, key)->gval();
}

Node *conmax(Node *x, Node *y, int l, int r) {
	int xl = l, xr = r;
	while (xl + 2 < xr) {
		int m = (xl + xr) >> 1;
		i64 v1 = f(x, y, m), v2 = f(x, y, m + 1);
		if (v1 < v2) xl = m;
		else if (v1 > v2) xr = m + 1;
		else xl = xr = m;
	}
	i64 v = f(x, y, xl);
	for (int i = xl + 1; i <= xr; i++) {
		i64 u = f(x, y, i);
		if (u > v) {
			v = u;
			xl = i;
		}
	}
	if (v <= 0) return y;
	int xm = xl;
	Node *ret = NULL, *_;
	if (f(x, y, l) <= 0) {
		xl = l;
		xr = xm;
		while (xl < xr) {
			int m = ((xl + xr) >> 1) + 1;
			if (f(x, y, m) > 0) xr = m - 1;
			else xl = m;
		}
		split(y, xl, ret, y);
		split(x, xl, _, x);
		split(x, xm, _, x);
		ret = meld(ret, _);
	} else {
		split(x, xm, ret, x);
		split(y, xm, _, y);
	}
	if (xm == xr) return ret;
	if (f(x, y, r) <= 0) {
		xl = xm + 1;
		xr = r;
		while (xl < xr) {
			int m = ((xl + xr) >> 1) + 1;
			if (f(x, y, m) > 0) xl = m;
			else xr = m - 1;
		}
		split(x, xl, _, x);
		ret = meld(ret, _);
		split(y, xl, _, y);
		ret = meld(ret, y);
	} else ret = meld(ret, x);
	return ret;
}

Node *conmax(Node *x, Node *y, int ykey, i64 yval) {
	int l = ykey, r = min(x->size, y->size + ykey) - 1;
	y->km += ykey;
	y->vm += yval;
	if (l > r) return meld(x, y);
	Node *x1, *x2, *x3, *y1, *y2;
	split(x, l - 1, x1, x2);
	split(x2, r, x2, x3);
	split(y, r, y1, y2);
	return meld(x1, meld(conmax(x2, y1, l, r), y2));
}

Node *conmeld(Node *x, Node *y) {
	if (!x) return new Node;
	x->push();
	Node *ret = conmax(conmeld(x->lch, y), conmeld(x->rch, y), 0, 0);
	return conmax(ret, cpy(y), x->key, x->val);
}

struct Edge {
	Edge(int _v, int _w) : v(_v), w(_w) {}
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
		dp[x][0] = dp[u][2];
		dp[x][1] = dp[u][0];
		dp[x][1]->km++;
		dp[x][1]->vm += ue->w;
	} else {
		dp[x][0] = dp[x][1] = dp[x][2] = new Node;
		return;
	}

	for (auto e : T[x]) {
		int v = e->v;
		if (v == f || v == u) continue;
		Node *ve = dp[v][0];
		ve->km += 1;
		ve->val += e->w;
		dp[x][0] = conmeld(dp[v][2], dp[x][0]);
		dp[x][1] = conmax(conmeld(dp[v][2], dp[x][1]), conmeld(ve, dp[x][0]), 0, 0);
	}
	dp[x][2] = conmax(dp[x][0], dp[x][1], 0, 0);
}

int main() {
	srand(time(NULL));
	scanf("%d%d", &n, &K);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		T[u].push_back(new Edge(v, w));
		T[v].push_back(new Edge(u, w));
	}

	dfs1(1, 0);
	dfs2(1, 0);
	Node *ret = get(dp[1][2], K);
	if (!ret) puts("Impossible");
	else printf("%lld\n", ret->val);

	return 0;
}
