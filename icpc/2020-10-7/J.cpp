#include <cstdio>
#include <cstring>
#include <cassert>

#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;

constexpr int SIGMA = 26;
constexpr int NMAX = 1000000;

int n, cnt;

struct Node {
	bool rev;
	int pa;
	int ch[SIGMA];
} m[NMAX + 100];

void insert(int x, char *s, vi &stk, bool rev) {
	stk.clear();
	stk.push_back(x);
	for (int i = 0; s[i]; i++) {
		int c = s[i] - 'a';
		if (!m[x].ch[c])
			m[x].ch[c] = ++cnt;
        int y = x;
		x = m[x].ch[c];
		m[x].pa = y;
		stk.push_back(x);
	}

	for (int i : stk) {
		m[i].rev = rev;
	}
}

void print(int x) {
	bool rev = m[x].rev;
	vi stk;
	for (int y; m[x].pa; x = y) {
		y = m[x].pa;
		for (int c = 0; c < SIGMA; c++) {
			if (m[y].ch[c] == x) {
				stk.push_back(c + 'a');
				break;
			}
		}
	}

	if (rev) {
		for (int c : stk) {
			putchar(c);
		}
	} else {
		for (int i = stk.size() - 1; i >= 0; i--) {
			putchar(stk[i]);
		}
	}
}

char s[NMAX + 10];
int tr1, tr2;
int deg[NMAX + 10];
int mark[NMAX + 10];
vi stk1, stk2;
vi G[NMAX + 10];

void link(int u, int v) {
	G[u].push_back(v);
	G[v].push_back(u);
	deg[u]++;
	deg[v]++;
}

bool cmp(int u, int v) {
	return deg[u] < deg[v] || (deg[u] == deg[v] && u < v);
}

void initialize() {
	tr1 = 1, tr2 = 2;
	cnt = 2;
	scanf("%d", &n);
	for (int _ = 0; _ < n; _++) {
		scanf("%s", s);
		int len = strlen(s);

		insert(tr1, s, stk1, false);
		reverse(s, s + len);
		insert(tr2, s, stk2, true);

		for (int i = 1; i < len; i++) {
			//link(stk1[i], stk2[len - i]);
            G[stk1[i]].push_back(stk2[len - i]);
            G[stk2[i]].push_back(stk1[len - i]);
		}
	}

	for (int i = 1; i <= cnt; i++) {
		sort(G[i].begin(), G[i].end(), cmp);
	}
}

void search(int &a, int &b, int &c, int &d) {
	a = -1;

    for (int u = 1; u <= cnt; u++)
    for (int v : G[u]) if (v != u)
    for (int w : G[v]) if (w != v && w != u)
    for (int x : G[w]) if (x != v && x != u && x != w) {
        for (int y : G[x]) {
            if (y == u) {
                a = u;
                b = v;
                c = w;
                d = x;
                return;
            }
        }
    }

    return;

	for (int u = 1; u <= cnt; u++) {
		for (int v : G[u]) {
			//if (!cmp(v, u))
			//	break;

			for (int w : G[v])
			if (w != u) {
				mark[w] = 0;
			}
		}

		for (int v : G[u]) {
			//if (!cmp(v, u))
			//	break;

			for (int w : G[v])
			if (w != u) {
				if (mark[w]) {
					a = u;
					b = v;
					c = w;
					d = mark[w];
					return;
				} else
					mark[w] = v;
			}
		}
	}
}

void reset() {
	memset(m + 1, 0, sizeof(Node) * cnt);
	memset(deg + 1, 0, sizeof(int) * cnt);
	for (int i = 1; i <= cnt; i++) {
		G[i].clear();
	}
	cnt = 0;
}

void _main() {
	initialize();

	int a, b, c, d;
	search(a, b, c, d);

	puts(a > 0 ? "YES" : "NO");
	if (a > 0) {
        assert(m[a].rev == m[c].rev);
        assert(m[b].rev == m[d].rev);
        assert(a != b && a != c && a != d);
        assert(b != c && b != d && c != d);

		//printf("%d %d %d %d\n", a, b, c, d);
		print(a);
        //putchar('_');
		print(d);
		putchar(' ');
		print(c);
        //putchar('_');
		print(b);
		puts("");

		print(a);
        //putchar('_');
		print(b);
		putchar(' ');
		print(c);
        //putchar('_');
		print(d);
		puts("");
	}

	reset();
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		_main();
	}
	return 0;
}
