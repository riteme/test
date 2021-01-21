#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 500;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
	Edge(int _u, int _v, i64 _c, i64 _w)
		: u(_u), v(_v), c(_c), w(_w), rev(NULL) {}

	int u, v;
	i64 c, w;
	Edge *rev;
};

int n, m, s, t;
i64 w[NMAX + 10];
vector<Edge*> G[NMAX + 10];

void link(int u, int v, i64 c, i64 w) {
	Edge *e1 = new Edge(u, v, c, w);
	Edge *e2 = new Edge(v, u, 0, -w);
	e1->rev = e2;
	e2->rev = e1;
	G[u].push_back(e1);
	G[v].push_back(e2);
}

i64 dist[NMAX + 10];
Edge *ep[NMAX + 10];
bool in[NMAX + 10];

void spfa() {
	memset(in, 0, sizeof(in));
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	in[s] = true;
	queue<int> q;
	q.push(s);
	do {
		int u = q.front();
		q.pop();
		in[u] = false;
		for (auto e : G[u]) if (e->c) {
			int v = e->v;
			if (dist[v] > dist[u] + e->w) {
				dist[v] = dist[u] + e->w;
				ep[v] = e;
				if (!in[v]) {
					in[v] = true;
					q.push(v);
				}
			}
		}
	} while (q.size());
}

i64 mcmf() {
	i64 ans = 0;
	while (true) {
		spfa();
		if (dist[t] >= 0)
			break;

		i64 minc = INF;
		int x = t;
		do {
			minc = min(minc, ep[x]->c);
			x = ep[x]->u;
		} while (x != s);

		x = t;
		do {
			ep[x]->c -= minc;
			ep[x]->rev->c += minc;
			x = ep[x]->u;
		} while (x != s);
		
		ans += minc * dist[t];
	}
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", w + i);
	}

	s = 2 * n + 1;
	t = 2 * n + 2;

	link(s, 1, INF, 0);
	link(n + n, t, INF, 0);

	for (int i = 1; i <= n; i++) {
		link(i, n + i, INF, -w[i]);
	}

	for (int i = 0; i < m; i++) {
		int u, v, t;
		scanf("%d%d%d", &u, &v, &t);
		link(n + u, v, t, 0);
	}

	i64 ans = -mcmf();
	printf("%lld\n", ans);

	return 0;
}
