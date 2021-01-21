#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 500000;

int n, m;
vector<int> G[NMAX + 10];
int a[NMAX + 10];
int tm, in[NMAX + 10], out[NMAX + 10];

void dfs(int x) {
	in[x] = ++tm;
	for (int v : G[x]) {
		dfs(v);
	}
	out[x] = tm;
}

struct Node {
	Node(int L, int R)
		: l(L), r(R), lch(NULL), rch(NULL) {
		if (l < r) {
			int m = (l + r) / 2;
			lch = new Node(l, m);
			rch = new Node(m + 1, r);
		}
	}

	int l, r, mx = 1;
	Node *lch, *rch;

	void cover(int L, int R, int v) {
		if (L <= l && r <= R)
			mx = max(mx, v);
		else {
			int m = (l + r) / 2;
			if (L <= m)
				lch->cover(L, R, v);
			if (R > m)
				rch->cover(L, R, v);
		}
	}

	int query(int x) {
		if (l == r)
			return mx;

		int m = (l + r) / 2;
		if (x <= m)
			return max(mx, lch->query(x));
		return max(mx, rch->query(x));
	}
};

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++) {
		int p;
		scanf("%d", &p);
		G[p].push_back(i);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", a + i);
	}
	dfs(1);

	Node *tr = new Node(1, n);
	int ans = 1;
	for (int i = 1; i <= m; i++) {
		int c = a[i];
		int v = tr->query(in[c]);
		ans = max(ans, v);

		if (in[c] < out[c])
			tr->cover(in[c] + 1, out[c], v + 1);
	}

	printf("%d\n", ans);
	return 0;
}
