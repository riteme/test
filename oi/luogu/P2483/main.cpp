#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 5000
#define MMAX 200000
#define INF 1e99

#define ACM_BEGIN
struct Edge {
	int v, nxt;
	double w;
};
int n, m, cnt;
double E;
Edge e[2 * MMAX + 10];
int G[NMAX + 10], G0[NMAX + 10];
void link(int u, int v, double w) {
	cnt += 2;
	e[cnt] = {v, G0[u], w};
	e[cnt - 1] = {u, G[v], w};
	G0[u] = cnt;
	G[v] = cnt - 1;
}
#define ACM_END

void initialize() {
	scanf("%d%d%lf", &n, &m, &E);
	cnt = 1;
	for (int i = 0; i < m; i++) {
		int u, v;
		double w;
		scanf("%d%d%lf", &u, &v, &w);
		link(u, v, w);
	}
}

#define ACM_BEGIN
int fa[NMAX + 10];
vector<int> T[NMAX + 10];
double dist[NMAX + 20];
bool used[2 * MMAX + 10];
void shortest(int s) {
	struct State {
		int u; double t;
		bool operator<(const State &z) const {
			return t > z.t;
	}};
	for (int i = 1; i <= n; i++) dist[i] = INF;
	dist[s] = 0;
	priority_queue<State> q;
	q.push({s, 0.0});
	do {
		auto _ = q.top();
		q.pop();
		if (_.t > dist[_.u]) continue;
		int u = _.u;
		for (int i = G[u]; i; i = e[i].nxt)
		if (dist[e[i].v] > dist[u] + e[i].w) {
			dist[e[i].v] = dist[u] + e[i].w;
			fa[e[i].v] = i;
			q.push({e[i].v, dist[e[i].v]});
		}
	} while (!q.empty());
	for (int i = 1; i <= n; i++) if (fa[i]) {
		int j = fa[i];
		used[j] = used[j ^ 1] = true;
		T[e[j ^ 1].v].push_back(i);
}}
struct Node {
	Node(double _val, int _ed) :
		val(_val), ed(_ed), len(0),
		lch(NULL), rch(NULL) {}
	double val;
	int ed, len;
	Node *lch, *rch;
};
Node *meld(Node *x, Node *y, bool cpy = false) {
	if (!x) return y;
	if (!y) return x;
	if (x->val > y->val) swap(x, y);
	Node *z = cpy ? new Node(*x) : x;
	z->rch = meld(z->rch, y, cpy);
	if (z->rch->len >= z->len) {
		z->len = z->rch->len + 1;
		swap(z->lch, z->rch);
	} return z;
}
Node *tr[NMAX + 10];
void build(int x) {
	Node *tmp = NULL;
	for (int i = G0[x]; i; i = e[i].nxt) if (!used[i])
		tmp = meld(tmp, new Node(dist[e[i].v] + e[i].w - dist[x], e[i].v));
	tr[x] = meld(tr[x], tmp, true);
	for (int v : T[x]) {
		tr[v] = tr[x];
		build(v);
}}
int solve() {
	struct State {
		double sum;
		Node *cur;
		bool operator<(const State &z) const {
			return sum > z.sum;
	}};
	if (E < dist[1]) return 0;
	E -= dist[1];
	priority_queue<State> q;
	if (tr[1]) q.push({tr[1]->val, tr[1]});
	int K = 1;
	while (!q.empty()) {
		auto _ = q.top();
		q.pop();
		E -= dist[1] + _.sum;
		if (E < 0) break;
		K++;
		auto u = _.cur;
		if (tr[u->ed]) q.push({_.sum + tr[u->ed]->val, tr[u->ed]});
		if (u->lch) q.push({_.sum - u->val + u->lch->val, u->lch});
		if (u->rch) q.push({_.sum - u->val + u->rch->val, u->rch});
	} return K;
}
#define ACM_END

int main() {
	initialize();
	shortest(n);
	build(n);
	printf("%d\n", solve());

	return 0;
}