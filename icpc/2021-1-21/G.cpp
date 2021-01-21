#include <cstdio>
#include <cstring>

#include <numeric>
#include <algorithm>

using namespace std;

constexpr int S = 28;
constexpr int S0 = 26;
constexpr int INT0 = 26;
constexpr int INT1 = 27;
constexpr int NMAX = 700000;

struct Node {
	Node() {
		memset(this, 0, sizeof(Node));
	}

	int cnt;
	Node *ch[S0];
};

void insert(Node *x, const char *s) {
	for (int i = 0; s[i]; i++) {
		int c = s[i] - 'a';
		if (!x->ch[c])
			x->ch[c] = new Node;
		x = x->ch[c];
	}
	x->cnt++;
}

int query(Node *x, const char *s) {
	for (int i = 0; s[i]; i++) {
		int c = s[i] - 'a';
		if (!x->ch[c])
			return 0;
		x = x->ch[c];
	}
	return x->cnt;
}

void dfs(Node *x) {
	for (int c = 0; c < S0; c++) {
		auto y = x->ch[c];
		if (y) {
			dfs(y);
			x->cnt += y->cnt;
		}
	}
}

struct SAM {
	int mcnt;
	struct Node {
		int maxlen, fail;
		int cnt;
		int ch[S];
	} m[NMAX + 10];
	void reset() {
		memset(this, 0, sizeof(SAM));
		mcnt = 1;
		m[0].maxlen = -1;
		fill(m[0].ch, m[0].ch + S, 1);
	}

	int append(int x, int c) {
		int y = ++mcnt;
		m[y].cnt = 1;
		m[y].maxlen = m[x].maxlen + 1;
		while (!m[x].ch[c]) {
			m[x].ch[c] = y;
			x = m[x].fail;
		}
		int p = m[x].ch[c];
		if (m[x].maxlen + 1 != m[p].maxlen) {
			int q = ++mcnt;
			m[q] = m[p];
			m[q].cnt = 0;
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

	int seq[NMAX + 10], scnt[NMAX + 10];
	void tsort() {
		memset(scnt, 0, sizeof(int) * mcnt);
		for (int i = 1; i <= mcnt; i++)
			scnt[m[i].maxlen]++;
		partial_sum(scnt, scnt + mcnt, scnt);
		for (int i = 1; i <= mcnt; i++)
			seq[scnt[m[i].maxlen]--] = i;
	}
	void subsum() {
		tsort();
		for (int i = mcnt; i > 1; i--) {
			int x = seq[i];
			m[m[x].fail].cnt += m[x].cnt;
		}
	}

	struct State {
		int x, l;
	};

	auto go(State s, int c) -> State {
		while (!m[s.x].ch[c]) {
			s.x = m[s.x].fail;
			s.l = m[s.x].maxlen;
		}
		return {m[s.x].ch[c], s.l + 1};
	}
};

int n, q;
char s[NMAX + 10], t[NMAX + 10];
Node *t1, *t2;
SAM sam;

int main() {
	scanf("%d", &n);
	t1 = new Node;
	t2 = new Node;

	sam.reset();
	int x = 1;
	for (int i = 0; i < n; i++) {
		scanf("%s", s);

		int len = strlen(s);

		insert(t1, s);
		for (int i = 0; i < len; i++) {
			x = sam.append(x, s[i] - 'a');
		}
		x = sam.append(x, INT0);
		for (int i = 0; i < len; i++) {
			x = sam.append(x, s[i] - 'a');
		}
		x = sam.append(x, INT1);

		reverse(s, s + len);
		insert(t2, s);
	}

	sam.subsum();
	dfs(t1);
	dfs(t2);

	scanf("%d", &q);
	while (q--) {
		scanf("%s%s", s, t);

		int ans = query(t1, s);

		SAM::State x = {1, 0};
		int len = 0;
		for (int i = 0; t[i]; i++) {
			x = sam.go(x, t[i] - 'a');
			len++;
		}
		x = sam.go(x, INT0);
		len++;
		for (int i = 0; s[i]; i++) {
			x = sam.go(x, s[i] - 'a');
			len++;
		}

		if (x.l == len)
			ans -= sam.m[x.x].cnt;

		int lent = strlen(t);
		reverse(t, t + lent);
		ans += query(t2, t);

		printf("%d\n", ans);
	}

	return 0;
}
