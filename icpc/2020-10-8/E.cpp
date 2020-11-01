#include <cstdio>
#include <cstring>

#include <random>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

constexpr int NMAX = 1000000;
constexpr int INF = 0x3f3f3f3f;

int n;
int a[NMAX + 10], s[NMAX + 10], t[NMAX + 10];
int f[NMAX + 10];

struct Node {
	int i, wt;
	int mina, minf;
	Node *lch, *rch;

	void reset() {
		lch = NULL;
		rch = NULL;
		update();
	}

	void update(Node *y) {
		mina = min(mina, y->mina);
		minf = min(minf, y->minf);
	}

	void update() {
		mina = a[i];
		minf = f[i];

		if (lch)
			update(lch);
		if (rch)
			update(rch);
	}
} e[NMAX + 10];

struct NodePair {
	Node *a, *b;
};

/**
 * for each node x, pred(x) determines whether x is
 * put into NodePair.b (true) or NodePair.a (false).
 */
template <typename TPred>
auto split(Node *x, const TPred &pred) -> NodePair {
	if (!x)
		return {NULL, NULL};
	
	NodePair rax;
	if (pred(x->i)) {
		rax = split(x->lch, pred);
		x->lch = rax.b;
		x->update();
		rax.b = x;
	} else {
		rax = split(x->rch, pred);
		x->rch = rax.a;
		x->update();
		rax.a = x;
	}

	return rax;
}

auto join(Node *x, Node *y) -> Node* {
	if (!x)
		return y;
	if (!y)
		return x;
	
	if (x->wt < y->wt) {
		x->rch = join(x->rch, y);
		x->update();
		return x;
	} else {
		y->lch = join(x, y->lch);
		y->update();
		return y;
	}
}

const auto cmp = [](int i, int j) {
	return a[i] > a[j] || (a[i] == a[j] && i > j);
};

void split(int l, int m, int r) {
	int pl = l, pr = m + 1;
	for (int _i = l; _i <= r; _i++) {
		int i = s[_i];

		if (i <= m)
			t[pl++] = i;
		else
			t[pr++] = i;
	}

	memcpy(s + l, t + l, sizeof(int) * (m - l + 1));
	memcpy(s + m + 1, t + m + 1, sizeof(int) * (r - m));
}

void join(int l, int m, int r) {
	inplace_merge(s + l, s + m + 1, s + r + 1, cmp);
}

void solve(int l, int r) {
	if (l >= r)
		return;
	
	// phase 1: calculate f[(m + 1)..r]
	int m = (l + r) / 2;
	split(l, m, r);
	solve(m + 1, r);
	join(l, m, r);

	// phase 2: update f[l]..f[m]
	Node *seq = NULL;  // a[l..m]
	Node *con = NULL;  // the convex hull on the right
	for (int _i = l; _i <= r; _i++) {
		int i = s[_i];
		e[i].reset();

		if (i > m) {
			auto p = split(con, [i](int j) {
				return i < j;
			});
			con = join(p.a, e + i);
		} else {
			auto p = split(seq, [i](int j) {
				return i < j;
			});

			int b = p.b ? p.b->mina : INF;
			auto q = split(con, [b](int j) {
				return a[j] < b;
			});

			int v = q.b ? q.b->minf + 1 : INF;
			f[i] = min(f[i], v);
			e[i].update();

			seq = join(p.a, join(e + i, p.b));
			con = join(q.a, q.b);
		}
	}

	// phase 3: calculate f[l..m] and restore s[l..r]
	split(l, m, r);
	solve(l, m);
	join(l, m, r);
}

void _main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	memset(f + 1, INF, sizeof(int) * n);

	int mx = -INF;
	for (int i = n; i >= 1; i--) {
		if (a[i] > mx)
			f[i] = 1;
		mx = max(mx, a[i]);
	}

	iota(s + 1, s + n + 1, 1);
	sort(s + 1, s + n + 1, cmp);
	solve(1, n);

	int ans = INF, mi = INF;
	for (int i = 1; i <= n; i++) {
		if (a[i] < mi)
			ans = min(ans, f[i]);
		mi = min(mi, a[i]);
	}

	printf("%d\n", ans);
}

int main() {
	static random_device rd;
	static mt19937 gen(rd());
	for (int i = 1; i <= NMAX; i++) {
		e[i].i = i;
		e[i].wt = gen();
	}

	int T;
	scanf("%d", &T);
	while (T--) {
		_main();
	}
	return 0;
}
