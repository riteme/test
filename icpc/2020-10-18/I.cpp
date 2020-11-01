#include <cstdio>
#include <cassert>
#include <cstring>

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

using i64 = long long;
using i8 = __int128_t;

constexpr int S = 26;
constexpr int NMAX = 200000;

int n;
char s[NMAX + 10];

struct SAM {
	int mcnt;
	struct Node {
		int maxlen, fail;
		int ch[S];
	} m[NMAX + 10];
	SAM() { reset(); }
	void reset() {
		memset(this, 0, sizeof(SAM));
		mcnt = 1;
		m[0].maxlen = -1;
		fill(m[0].ch, m[0].ch + S, 1);
	}
	int append(int x, int c) {
		int y = ++mcnt;
		m[y].maxlen = m[x].maxlen + 1;
		while (!m[x].ch[c]) {
			m[x].ch[c] = y;
			x = m[x].fail;
		}
		int p = m[x].ch[c];
		if (m[x].maxlen + 1 != m[p].maxlen) {
			int q = ++mcnt;
			m[q] = m[p];
			m[q].maxlen = m[x].maxlen + 1;
			m[p].fail = m[y].fail = q;
			while (m[x].ch[c] == p) {
				m[x].ch[c] = q;
				x = m[x].fail;
			}
		} else
			m[y].fail = p;
		return y;
	}
	Node &operator[](int i) {
		return m[i];
	}
};

struct LCT {
	struct Node {
		int fa, lch, rch;
		int rp, rpm;
		bool rev;
	};
	Node m[NMAX + 10];
	Node &operator[](int i) {
		return m[i];
	}
	void push(int x) {
		if (m[x].rev) {
			swap(m[x].lch, m[x].rch);
			m[m[x].lch].rev ^=1;
			m[m[x].rch].rev ^= 1;
			m[x].rev = 0;
		}

		if (m[x].rpm) {
			m[x].rp = m[x].rpm;
			m[m[x].lch].rpm = m[x].rpm;
			m[m[x].rch].rpm = m[x].rpm;
			m[x].rpm = 0;
		}
	}
	void update(int x) {
		/* nothing */
	}
#define ROT(name, lch, rch) \
	void name(int x) { \
		int y = m[x].lch; \
		m[m[y].rch].fa = x; \
		m[x].lch = m[y].rch; \
		m[y].rch = x; \
		if (m[x].fa > 0) { \
			int p = m[x].fa; \
			if (m[p].lch == x) \
				m[p].lch = y; \
			else \
				m[p].rch = y; \
		} \
		m[y].fa = m[x].fa; \
		m[x].fa = y; \
		update(x); \
		update(y); \
	}
	ROT(lrot, lch, rch)
	ROT(rrot, rch, lch)
	void access(int x) {
		if (m[x].fa > 0)
			access(m[x].fa);
		push(x);
	}
	void splay(int x, bool ac = false) {
		if (!ac)
			access(x);
		while (m[x].fa > 0) {
			int p = m[x].fa, p2 = m[p].fa;
			if (p2 > 0) {
				if (m[p].lch == x && m[p2].lch == p)
					lrot(p2);
				else if (m[p].rch == x && m[p2].rch == p)
					rrot(p2);
			}
			if (m[p].lch == x)
				lrot(p);
			else
				rrot(p);
		}
	}

	template <typename TFn>
	int splice(int x, const TFn &fn) {
		int p = -m[x].fa;
		splay(p);
		m[m[p].rch].fa = -p;
		m[p].rch = 0;
		update(p);
		p = fn(p);

		p = tmax(p);
		m[p].rch = x;
		m[x].fa = p;
		update(p);
		return p;
	}

	template <typename TFn>
	void expose(int x, const TFn &fn) {
		splay(x);
		m[m[x].rch].fa = -x;
		m[x].rch = 0;
		update(x);
		x = fn(x);
		while (m[x].fa)
			x = splice(x, fn);
	}

	void link(int x, int y) {
		splay(y);
		m[y].fa = -x;
	}
	int tmin(int x) {
		while (m[x].lch)
			x = m[x].lch;
		splay(x);
		return x;
	}
	int tmax(int x) {
		while (m[x].rch)
			x = m[x].rch;
		splay(x);
		return x;
	}
};

struct Segment {
	int l, r;
	i64 v, vi, vm;
	Segment *lch, *rch;

	Segment(int L, int R)
		: l(L), r(R), v(0), vi(0), vm(0), lch(NULL), rch(NULL) {
		if (l < r) {
			int m = (l + r) / 2;
			lch = new Segment(l, m);
			rch = new Segment(m + 1, r);
		}
	}

	i64 rv() {
		return v + vm * (r - l + 1);
	}

	i64 rvi() {
		return vi + vm * (r + l) * (r - l + 1) / 2;
	}

	void push() {
		if (vm) {
			v = rv();
			vi = rvi();
			lch->vm += vm;
			rch->vm += vm;
			vm = 0;
		}
	}

	void pull() {
		v = lch->rv() + rch->rv();
		vi = lch->rvi() + rch->rvi();
	}

	void modify(int L, int R, i64 v) {
		if (L <= l && r <= R)
			vm += v;
		else {
			push();
			int m = (l + r) / 2;
			if (L <= m)
				lch->modify(L, R, v);
			if (R > m)
				rch->modify(L, R, v);
			pull();
		}
	}

	template <typename TFn>
	i64 query(int L, int R, const TFn &fn) {
		if (L > R)
			return 0;
		if (L <= l && r <= R)
			return fn(this);

		push();
		int m = (l + r) / 2;
		i64 rax = 0;
		if (L <= m)
			rax += lch->query(L, R, fn);
		if (R > m)
			rax += rch->query(L, R, fn);
		return rax;
	}
};

SAM sam;
LCT lct;
Segment *tr;
int pos[NMAX + 10];

i8 solve() {
	int x = 1;
	for (int i = 1; i <= n; i++) {
		x = sam.append(x, s[i] - 'a');
		pos[i] = i - sam[sam[x].fail].maxlen;
	}
	for (int v = 2; v <= sam.mcnt; v++) {
		int u = sam[v].fail;
		lct.link(u, v);
	}
	tr = new Segment(1, n);

	auto qv = [](Segment *s) -> i64 {
		return s->rv();
	};
	auto qvi = [](Segment *s) -> i64 {
		return s->rvi();
	};

	x = 1;
	i8 ans = 0;
	for (int r = 1; r <= n; r++) {
		x = sam[x].ch[s[r] - 'a'];
		lct.expose(x, [r](int z) -> int {
			lct.push(z);
			int r0 = lct[z].rp;
			z = lct.tmax(z);
			int maxlen = sam[z].maxlen;
			z = lct.tmin(z);
			int minlen = max(1, sam[sam[z].fail].maxlen + 1);

			if (maxlen > 0) {
				if (r0)
					tr->modify(r0 - maxlen + 1, r0 - minlen + 1, -1);
				assert(r >= maxlen);
				tr->modify(r - maxlen + 1, r - minlen + 1, +1);
			}

			lct[z].rpm = r;
			return z;
		});

		int j = pos[r];
		ans += tr->query(1, j, qvi);
		ans += j * tr->query(j + 1, r, qv);
	}

	i8 s = tr->query(1, n, qv);
	return s * (s + 1) / 2 - ans;
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);

	i8 ans = solve();
	if (!ans) {
		puts("0");
		return 0;
	}
	string stk;
	while (ans) {
		char c = ans % 10 + '0';
		stk.push_back(c);
		ans /= 10;
	}
	reverse(stk.begin(), stk.end());
	printf("%s\n", stk.c_str());

	return 0;
}
