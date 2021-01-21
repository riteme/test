#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 500000;
constexpr int INF = 0x3f3f3f3f;

using i64 = long long;

int n, q;
char s[NMAX + 10];
int a[NMAX + 10];

struct Node {
	Node(int L, int R)
		: l(L), r(R),
		  maxv(-INF), minv(INF), sumv(0),
		  mi(0), mv(0),
          lch(NULL), rch(NULL)
	{
		if (l < r) {
			int m = (l + r) / 2;
			lch = new Node(l, m);
			rch = new Node(m + 1, r);
			fetch();
		} else {
			minv = maxv = sumv = a[l];
		}
	}

	void fetch() {
		if (lch) {
            assert(rch);
			lch->commit();
			rch->commit();
			maxv = max(lch->maxv, rch->maxv);
			minv = min(lch->minv, rch->minv);
			sumv = lch->sumv + rch->sumv;
		}
	}

	void commit() {
		int b = mi & 1;

		if (b || mv) {
			if (b) {
				swap(maxv, minv);
				maxv = -maxv;
				minv = -minv;
				sumv = -sumv;

				if (lch) {
                    assert(rch);
					lch->add_mi();
					rch->add_mi();
				}
			}

			maxv += mv;
			minv += mv;
			sumv += mv * (r - l + 1);

			if (lch) {
                assert(rch);
				lch->add_mv(mv);
				rch->add_mv(mv);
			}
		}

		mi = mv = 0;
	}

	void add_mi() {
		mi ^= 1;
		mv = -mv;
	}

	void add_mv(int v) {
		mv += v;
	}

	void add(int L, int R, int v) {
		if (R < L || R < l || L > r)
			return;
		if (L <= l && r <= R)
			add_mv(v);
		else {
			commit();

			int m = (l + r) / 2;
			if (L <= m)
				lch->add(L, R, v);
			if (R > m)
				rch->add(L, R, v);

			fetch();
		}
	}

	void negate(int L, int R) {
		if (R < L || R < l || L > r)
			return;

        static int dep = 0;
        dep++;
        assert(dep < 100);
		if (L <= l && r <= R)
			add_mi();
		else {
			commit();

			int m = (l + r) / 2;
			if (L <= m)
				lch->negate(L, R);
			if (R > m)
				rch->negate(L, R);

			fetch();
		}
        dep--;
	}

	int qsum(int L, int R) {
		if (R < L || R < l || L > r)
			return 0;

		commit();
		if (L <= l && r <= R)
			return sumv;

		int m = (l + r) / 2;
		int rax = 0;
		if (L <= m)
			rax += lch->qsum(L, R);
		if (R > m)
			rax += rch->qsum(L, R);

		return rax;
	}

	int qmin(int L, int R) {
		if (R < L || R < l || L > r)
			return INF;

		commit();
		if (L <= l && r <= R)
			return minv;

		int m = (l + r) / 2;
		int rax = INF;
		if (L <= m)
			rax = min(rax, lch->qmin(L, R));
		if (R > m)
			rax = min(rax, rch->qmin(L, R));

		return rax;
	}

	int qval(int x) {
		if (x < l)
			return qsum(l, l);
		if (x > r)
			return qsum(r, r);
		return qsum(x, x);
	}

	int l, r;
	i64 maxv, minv, sumv;
	i64 mi, mv;
	Node *lch, *rch;
};

int main() {
	scanf("%d%d%s", &n, &q, s + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = a[i - 1] + (s[i] == '(' ? +1 : -1);
	}

	Node *tr = new Node(0, n);
	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r);

		int s0 = tr->qval(l - 1);
		int s1 = tr->qval(r);
		tr->add(l, r, -s0);
		tr->add(r + 1, n, -s1);
        tr->negate(l, r);
		tr->add(l, r, s0);
		s1 = tr->qval(r);
		tr->add(r + 1, n, s1);

		int S = tr->qval(n);
		int mi = tr->qmin(0, n);
		//printf("[%d,%d]: mi=%d\n", l, r, mi);
		puts(S == 0 && mi >= 0 ? "YES" : "NO");
	}

	return 0;
}
