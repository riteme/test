#include <cstdio>
#include <cstring>
#include <cassert>

#include <array>
#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;
constexpr int PMAX = 32;

using fn_t = array<int, PMAX>;
using cnt_t = array<int, PMAX>;

int n, q, MOD;
int a[NMAX + 10];

int qpow(int a, int k) {
	if (a == 0)
		return k == 0 ? 1 : 0;

	int r = 1;
	a %= MOD;
	for ( ; k; k >>= 1) {
		if (k & 1)
			r = r * a % MOD;
		a = a * a % MOD;
	}
	return r;
}

void reset_fn(fn_t &f) {
	for (int i = 0; i < MOD; i++) {
		f[i] = i;
	}
}

void apply_to(const fn_t &f, fn_t &g) {
	static fn_t h;
	h.fill(0);
	for (int i = 0; i < MOD; i++) {
		h[i] = f[g[i]];
	}
	//swap(h, g);
	g = h;
}

struct Node {
	int l, r;
	bool mark;
	cnt_t cnt;
	fn_t fn;
	Node *lch, *rch;

	void commit() {
		if (!mark)
			return;

		static cnt_t t;
		t.fill(0);
		for (int i = 0; i < MOD; i++) {
			t[fn[i]] += cnt[i];
		}
		//swap(t, cnt);
		cnt = t;

		if (lch) {
			lch->mark = rch->mark = true;
			apply_to(fn, lch->fn);
			apply_to(fn, rch->fn);
		}

		mark = false;
		reset_fn(fn);
	}

	void fetch() {
		if (lch) {
			lch->commit();
			rch->commit();

			for (int i = 0; i < MOD; i++) {
				cnt[i] = lch->cnt[i] + rch->cnt[i];
			}
		}
	}

	Node(int L, int R) : l(L), r(R), mark(false), lch(NULL), rch(NULL) {
		cnt.fill(0);
		reset_fn(fn);

		if (l < r) {
			int m = (l + r) / 2;
			lch = new Node(l, m);
			rch = new Node(m + 1, r);
			fetch();
		} else {
			int k = a[l] % MOD;
			if (k < 0)
				k += MOD;
			cnt[k] = 1;
		}
	}

	void apply(int L, int R, const fn_t &f) {
		if (L <= l && r <= R) {
			mark = true;
			apply_to(f, fn);
		} else {
			commit();

			int m = (l + r) / 2;
			if (L <= m)
				lch->apply(L, R, f);
			if (R > m)
				rch->apply(L, R, f);

			fetch();
		}
	}

	void _query(int L, int R, cnt_t &dst) {
		commit();

		if (L <= l && r <= R) {
			for (int i = 0; i < MOD; i++) {
				dst[i] += cnt[i];
			}
		} else {
			int m = (l + r) / 2;
			if (L <= m)
				lch->_query(L, R, dst);
			if (R > m)
				rch->_query(L, R, dst);
		}

		fetch();
	}

	void query(int L, int R, cnt_t &dst) {
		dst.fill(0);
		_query(L, R, dst);
	}
};

fn_t f;
cnt_t c;

int main() {
	scanf("%d%d", &n, &MOD);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}

	Node *tr = new Node(1, n);

	scanf("%d", &q);
	while (q--) {
		int t, l, r, k;
		scanf("%d%d%d%d", &t, &l, &r, &k);
		assert(k >= 0);

		if (t == 1) {
			k = (k % MOD + MOD) % MOD;
			for (int i = 0; i < MOD; i++) {
				f[i] = (i + k) % MOD;
			}
			tr->apply(l, r, f);
		} else if (t == 2) {
			k %= MOD;
			for (int i = 0; i < MOD; i++) {
				f[i] = i * k % MOD;
				if (f[i] < 0)
					f[i] += MOD;
			}
			tr->apply(l, r, f);
		} else if (t == 3) {
			for (int i = 0; i < MOD; i++) {
				f[i] = qpow(i, k);
			}
			tr->apply(l, r, f);
		} else if (t == 4) {
			tr->query(l, r, c);

			int ans = 0;
			for (int i = 0; i < MOD; i++) {
				ans = (ans + c[i] % MOD * qpow(i, k)) % MOD;
			}

			if (ans < 0)
				ans += MOD;
			printf("%d\n", ans);
		} else if (t == 5) {
			tr->query(l, r, c);

			int ans = 1;
			for (int i = 0; i < MOD; i++) {
				ans = ans * qpow(i, c[i]) % MOD;
			}

			if (ans < 0)
				ans += MOD;
			printf("%d\n", ans);
		}
	}

	return 0;
}
