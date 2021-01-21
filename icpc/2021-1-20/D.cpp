#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 1000000;
constexpr int LOGN = 19;

int q;
int pr[NMAX + 10], pcnt;
bool ok[NMAX + 10];
int S[NMAX + 10], D[NMAX + 10], P[NMAX + 10], dpos = 1;

struct req_t {
	int k;
	int x;
} R[NMAX + 10];
vector<req_t*> rq[2][NMAX + 10];

constexpr int WMAX = 2 * NMAX;

int w[WMAX + 10];

void modify(int x, int v) {
	for ( ; x <= WMAX; x += x & -x) {
		w[x] += v;
	}
}

int query(int r) {
	int rax = 0;
	for ( ; r; r -= r & -r) {
		rax += w[r];
	}
	return rax;
}

int kth(int k) {
	int p = 0, s = 0;
	for (int i = LOGN; i >= 0; i--) {
		int np = p + (1 << i);
		if (s + w[np] < k) {
			s += w[np];
			p = np;
		}
	}
	return p + 1;
}

void resolve0(req_t *r) {
	r->x = query(P[r->k]);
}

void resolve1(req_t *r) {
	r->x = D[kth(r->k)];
}

void solve() {
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		auto &r = R[i];
		int t, n;
		scanf("%d%d%d", &t, &n, &r.k);
		rq[t - 1][n].push_back(&r);
	}

	for (int i = 1; i <= NMAX; i++) {
		modify(P[i], +1);

		for (auto r : rq[0][i]) {
			resolve0(r);
		}
		for (auto r : rq[1][i]) {
			resolve1(r);
		}
	}

	for (int i = 1; i <= q; i++) {
		printf("%d\n", R[i].x);
	}
}

int main() {
	for (int i = 1; i <= NMAX; i++) {
		ok[i] = 1;
	}
	for (int i = 2; i <= NMAX; i++) {
		if (ok[i])
			pr[pcnt++] = i;
		for (int j = 0; pr[j] * i <= NMAX; j++) {
			ok[pr[j] * i] = 0;
			if (i % pr[j] == 0)
				break;
		}
	}

	int n = NMAX;
	for (int i = 1; i <= n; i++) {
		S[i] = i;
	}
	while (n) {
		int pos = 1;
		for (int i = 1; i <= n; i++) {
			if (ok[i])
				D[dpos++] = S[i];
			else
				S[pos++] = S[i];
		}
		n = pos - 1;
	}

	for (int i = 1; i <= NMAX; i++) {
		P[D[i]] = i;
	}

	solve();

	return 0;
}
