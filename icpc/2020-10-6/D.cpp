#pragma GCC optimize(3)

#include <cstdio>
#include <cctype>
#include <cstring>

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define BUFSIZE 65536
size_t _pos = BUFSIZE;
char _buf[BUFSIZE];

void _getc(char &c) {
	if (_pos == BUFSIZE) {
		_pos = 0;
		fread(_buf, 1, BUFSIZE, stdin);
	}
	c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
	x = 0;
	char c;
	do _getc(c); while (!isdigit(c));
	do {
		x = x * 10 + (c - '0');
		_getc(c);
	} while (isdigit(c));
}

#define NMAX 200000
#define INF 0x3f3f3f3f

int rsum(struct Node *);

struct Node {
	int sum, val;
	bool cov;
	Node *lch, *rch;

	void commit() {
		if (cov) {
			val = sum = 0;
			if (lch)
				lch->cov = true;
			if (rch)
				rch->cov = true;
			cov = 0;
		}
	}

	void fetch() {
		sum = val + rsum(lch) + rsum(rch);
	}
};

size_t mpos;
Node mem[40 * NMAX];

Node *mnew() {
	Node *p = mem + mpos;
	mpos++;
	memset(p, 0, sizeof(Node));
	return p;
}

Node *insert(Node *x, int l, int r, int p, int v) {
	if (!x)
		x = mnew();

	x->commit();
	if (l == r)
		x->val += v;
	else {
		int m = (l + r) / 2;
		if (p <= m)
			x->lch = insert(x->lch, l, m, p, v);
		else
			x->rch = insert(x->rch, m + 1, r, p, v);
	}

	x->fetch();
	return x;
}

Node *meld(Node *x, Node *y) {
	if (!x)
		return y;
	if (!y)
		return x;

	x->commit();
	y->commit();
	x->sum += y->sum;
	x->val += y->val;
	x->lch = meld(x->lch, y->lch);
	x->rch = meld(x->rch, y->rch);
	x->fetch();
	return x;
}

int query(Node *x, int l, int r, int L, int R) {
	if (!x || r < l)
		return 0;

	x->commit();
	if (L <= l && r <= R)
		return x->sum;
	
	int rax = 0;
	int m = (l + r) / 2;
	if (L <= m)
		rax += query(x->lch, l, m, L, R);
	if (R > m)
		rax += query(x->rch, m + 1, r, L, R);
	
	x->fetch();
	return rax;
}

void cover(Node *x, int l, int r, int L, int R) {
	if (!x || r < l)
		return;

	x->commit();
	if (L <= l && r <= R)
		x->cov = true;
	
	if (l < r) {
		int m = (l + r) / 2;
		if (L <= m)
			cover(x->lch, l, m, L, R);
		if (R > m)
			cover(x->rch, m + 1, r, L, R);
	}

	x->fetch();
}

int rsum(Node *x) {
	return x && !x->cov ? x->sum : 0;
}

int bisearch(Node *x, int l, int r, int v) {
	if (l == r)
		return rsum(x) <= v ? l + 1 : l;
	if (!x)
		return r + 1;

	x->commit();
	int s = rsum(x->lch);
	int m = (l + r) / 2;
	return s <= v ?
		bisearch(x->rch, m + 1, r, v - s) :
		bisearch(x->lch, l, m, v);
}

int n, cnt, w[NMAX + 10];
int seq[NMAX + 10];
vector<int> G[NMAX + 10];

Node *dp(int u) {
	Node *h = NULL;
	for (int v : G[u]) {
		h = meld(h, dp(v));
	}

	int C = 1 + query(h, 1, cnt, 1, w[u]);
	int l = w[u] + 1;
	int r = bisearch(h, 1, cnt, C);
	//printf("u=%d l=%d, r=%d, C=%d\n", u, l, r, C);
	if (l < r) {
		int lv = C - query(h, 1, cnt, 1, l - 1);
		int rv = 0;
		if (r <= cnt)
			rv = query(h, 1, cnt, 1, r) - C;

		cover(h, 1, cnt, l, r);
		h = insert(h, 1, cnt, l, lv);
		if (rv > 0)
			h = insert(h, 1, cnt, r, rv);
	}

	return h;
}

int main() {
	//scanf("%d", &n);
	read(n);
	cnt = 0;
	for (int i = 1; i <= n; i++) {
		int p;
		//scanf("%d%d", w + i, &p);
		read(w[i]); read(p);
		G[p].push_back(i);
		seq[cnt++] = w[i];
		//seq[cnt++] = w[i] + 1;
	}
	seq[cnt++] = INF;

	sort(seq, seq + cnt);
	cnt = unique(seq, seq + cnt) - seq;
	unordered_map<int, int> mp;
	for (int i = 0; i < cnt; i++) {
		mp[seq[i]] = i + 1;
	}
	for (int i = 1; i <= n; i++) {
		w[i] = mp[w[i]];
	}

	auto ans = dp(1);
	printf("%d\n", query(ans, 1, cnt, 1, cnt));
	return 0;
}
