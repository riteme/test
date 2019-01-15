#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000
#define INF NMAX + 10
#define MMAX 1000000

static int n, m;
static int L[NMAX + 10], R[NMAX + 10], dp[NMAX + 10];
static int in[NMAX + 10], out[NMAX + 10];
static vector<int> G[NMAX + 10], rev[NMAX + 10];

bool istopo() {
	queue<int> q;
	for (int i = 1; i <= n; i++) if (!in[i]) q.push(i);
	memcpy(dp, R, sizeof(dp));
	for (int i = 1; i <= n && !q.empty(); i++) {
		int u = q.front();
		q.pop();
		for (int v : G[u]) {
			in[v]--;
			dp[v] = min(dp[v], dp[u]);
			if (!in[v]) q.push(v);
		}
	}
	return q.empty();
}

struct Node {
	Node(int i) : w(rand()), key(L[i]), val(dp[i]), minv(dp[i]), id(i),
		lch(nullptr), rch(nullptr), fa(nullptr), minp(this) {}
	int w, key, val, minv, id;
	Node *lch, *rch, *fa, *minp;

	void update() {
		int lv = lch ? lch->minv : INF, rv = rch ? rch->minv : INF;
		if (val <= lv && val <= rv) {
			minv = val;
			minp = this;
		} else if (lv <= val && lv <= rv) {
			minv = lv;
			minp = lch->minp;
		} else {
			minv = rv;
			minp = rch->minp;
		}
	}
};

typedef pair<Node *, Node *> NPair;

NPair split(Node *x, int key) {
	if (!x) return NPair(NULL, NULL);
	NPair ret;
	if (key < x->key) {
		ret = split(x->lch, key);
		x->lch = ret.second;
		if (ret.first) ret.first->fa = NULL;
		if (ret.second) ret.second->fa = x;
		ret.second = x;
	} else {
		ret = split(x->rch, key);
		x->rch = ret.first;
		if (ret.first) ret.first->fa = x;
		if (ret.second) ret.second->fa = NULL;
		ret.first = x;
	}
	x->update();
	return ret;
}

Node *meld(Node *x, Node *y) {
	if (!x) return y;
	if (!y) return x;
	if (x->w < y->w) {
		x->rch = meld(x->rch, y);
		if (x->rch) x->rch->fa = x;
		x->update();
		return x;
	} else {
		y->lch = meld(x, y->lch);
		if (y->lch) y->lch->fa = y;
		y->update();
		return y;
	}
}

Node *insert(Node *x, int p) {
    auto q = split(x, L[p]);
    return meld(meld(q.first, new Node(p)), q.second);
}

void del(Node *x) {
	x->val = INF;
	x->update();
	for (x = x->fa; x; x = x->fa) x->update();
}

static int seq[NMAX + 10];

int main() {
	srand(time(NULL));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", L + i, R + i);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[v].push_back(u);
		rev[u].push_back(v);
		in[u]++;
		out[v]++;
	}
	if (!istopo()) {
		puts("-1");
		return 0;
	}

	Node *tr = NULL;
	for (int i = 1; i <= n; i++) if (!out[i])
		tr = insert(tr, i);
	for (int i = 1; i <= n; i++) {
		auto p1 = split(tr, i);
		if (!p1.first) {
			puts("-1");
			return 0;
		}
		Node *t = p1.first->minp;
        //printf("i = %d\n", i);
        //printf("t: id = %d, key = %d, val = %d, minv = %d\n", t->id, t->key, t->val, t->minv);
		if (t->minv == INF || R[t->id] < i) {
			puts("-1");
			return 0;
		}
		int u = seq[i] = t->id;
		tr = meld(p1.first, p1.second);
		del(t);
		for (int v : rev[u]) {
			out[v]--;
			if (!out[v]) tr = insert(tr, v);
		}
	}
	for (int i = 1; i <= n; i++) printf("%d\n", seq[i]);

	return 0;
}
