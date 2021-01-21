#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 100000;
constexpr int KMAX = 200;

struct Edge {
	Edge(int _v, int _w)
		: v(_v), w(_w), f(NULL), g(NULL) {}

	void init() {
		f = new int[KMAX + 10];
		g = new int[KMAX + 10];
		memset(f, 0, sizeof(int) * (KMAX + 10));
		memset(g, 0, sizeof(int) * (KMAX + 10));
	}

	int v, w;
	int *f, *g;
};

int n, K;
vector<Edge> G[NMAX + 10];
int sf[KMAX + 10], sg[KMAX + 10];
int pa[NMAX + 10];
int f[NMAX + 10][KMAX + 10];
int g[NMAX + 10][KMAX + 10];

void dp(int x, int p) {
	f[x][0] = g[x][0] = 1;

	for (auto &e : G[x]) if (e.v != p) {
		int v = e.v;
		pa[v] = x;
		dp(v, x);

		e.init();
		for (int k = 0; k <= K; k++) {
			if (k < K && e.w == sf[k])
				e.f[k + 1] += f[v][k];
			else
				e.f[k] += f[v][k];
		}
		for (int k = 0; k <= K; k++) {
			if (k < K && e.w == sg[k])
				e.g[k + 1] += g[v][k];
			else
				e.g[k] += g[v][k];
		}

		for (int k = 0; k <= K; k++) {
			f[x][k] += e.f[k];
			g[x][k] += e.g[k];
		}
	}
}

int main() {
	scanf("%d%d", &n, &K);
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	for (int i = 0; i < K; i++) {
		scanf("%d", sf + i);
	}
	memcpy(sg, sf, sizeof(sg));
	reverse(sg, sg + K);

	dp(1, 0);

	i64 ans = 0;
	for (int x = 1; x <= n; x++) {
		//printf("x=%d, f+%lld, g+%lld\n", x, f[x][K], g[x][K]);
		//ans += f[x][K];
		ans += g[x][K];

		for (int b = K - 1; b >= 0; b--) {
			g[x][b] += g[x][b + 1];
		}

		for (auto &e : G[x]) if (e.g) {
			for (int b = K - 1; b >= 0; b--) {
				e.g[b] += e.g[b + 1];
			}
		}
	}

	for (int x = 1; x <= n; x++) {
		for (auto &e : G[x]) if (pa[e.v] == x)
		for (int a = 0; a <= K; a++) {
			int b = K - a;
			//printf("x=%d, a=%d, b=%d, e.f[a]=%lld, g[x][b]=%lld, e.g[b]=%lld\n",
			//	x, a, b, e.f[a], g[x][b], e.g[b]);
			ans += i64(e.f[a]) * (g[x][b] - e.g[b]);
		}
	}

	printf("%lld\n", ans);
	return 0;
}
