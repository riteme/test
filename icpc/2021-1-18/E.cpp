#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;

int n, B;
int p[NMAX + 10];

int prep(int x) {
	return x == 1 ? n : x - 1;
}

int nexp(int x) {
	return x == n ? 1 : x + 1;
}

struct Edge {
	int v, w;
};

int s;
vector<Edge> G[NMAX + 10];
int dist[NMAX + 10];

void spfa() {
	static bool in[NMAX + 10];

	memset(in, 0, sizeof(in));
	memset(dist, 0x3f, sizeof(dist));

	queue<int> q;
	q.push(s);
	dist[s] = 0;
	in[s] = true;

	do {
		int u = q.front();
		q.pop();
		in[u] = false;

		for (auto &e : G[u]) {
			int v = e.v;
			if (dist[v] > dist[u] + e.w) {
				dist[v] = dist[u] + e.w;
				if (!in[v]) {
					q.push(v);
					in[v] = true;
				}
			}
		}
	} while (q.size());
}

void link(int u, int v, int w) {
	G[u].push_back({v, w});
}

void connect(int i, int j) {
	if (p[i] == p[j]) {
		link(i, j, 0);
		link(j, i, 0);
	} else if (p[i] > p[j]) {
		link(j, i, -1);
	}
}

int main() {
	scanf("%d%d", &n, &B);
	s = n + 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", p + i);
		if (p[i])
			link(s, i, -1);
		else
			link(s, i, 0);
	}

	for (int i = 1; i <= n; i++) {
		connect(i, prep(i));
		connect(i, nexp(i));
	}

	spfa();

	for (int i = 1; i <= n; i++) {
		i64 ans = i64(abs(dist[i])) * B;
		printf(i < n ? "%lld " : "%lld\n", ans);
	}

	return 0;
}
