#pragma GCC optimize("O3,no-stack-protector")
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
//#define MUL 500000

typedef long long i64;

struct UnionFind {
	UnionFind() { memset(fa, 0, sizeof(fa)); }
	int fa[2 * NMAX + 10];
	void clear(int n) { memset(fa + 1, 0, sizeof(int) * n); }
	int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
	int operator[](int x) { return find(x); }
};

#define ACM_BEGIN
#define INF 10000000000
struct Edge {
    int u, v;
    i64 w, w0;
};
struct Heap {
	void init(Edge *_e) {
        e = _e;
        rk = 1;
        sum = 0;
        lch = NULL;
        rch = NULL;
    }
	Edge *e; int rk;
    i64 sum;
	Heap *lch, *rch;
	void push() {
		if (lch) lch->sum += sum;
		if (rch) rch->sum += sum;
		e->w += sum; sum = 0;
}};

#define MEMSIZE 5000000
static Heap mem[MEMSIZE];
static int mempos;
Heap *alloc(Edge *_e) {
    Heap *p = mem + mempos;
    mempos++;
    p->init(_e);
    return p;
}

inline Heap *meld(Heap *x, Heap *y) {
	if (!x) return y;
	if (!y) return x;
	if (x->e->w + x->sum > y->e->w + y->sum)
		swap(x, y);
	x->push();
	x->rch = meld(x->rch, y);
	if (!x->lch || x->lch->rk < x->rch->rk)
		swap(x->lch, x->rch);
	x->rk = x->rch ? x->rch->rk + 1 : 1;
	return x;
}
inline Edge *extract(Heap *&x) {
	Edge *r = x->e;
	x->push();
	x = meld(x->lch, x->rch);
	return r;
}
static vector<Edge> in[NMAX + 10];
static int n, m, fa[2 * NMAX + 10], nxt[2 * NMAX + 10];
static Edge *ed[2 * NMAX + 10];
static Heap *Q[2 * NMAX + 10];
static UnionFind id; // id[] & id.faa
void contract() {
	static bool mark[2 * NMAX + 10];
	memset(mark + 1, 0, 2 * n);
    memset(fa + 1, 0, sizeof(int) * 2 * n);
    memset(nxt + 1, 0, sizeof(int) * 2 * n);
    memset(Q + 1, 0, sizeof(Heap*) * 2 * n);
	id.clear(2 * n);
	for (int i = 1; i <= n; i++) {
		queue<Heap*> q;
		for (int j = 0; j < in[i].size(); j++)
			q.push(alloc(&in[i][j]));
		while (q.size() > 1) {
			Heap *u = q.front(); q.pop();
			Heap *v = q.front(); q.pop();
			q.push(meld(u, v));
		} Q[i] = q.front();
	} mark[1] = true;
	for (int u = 1, u0 = 1, p; Q[u]; mark[u0 = u] = true) {
		do u = id[(ed[u] = extract(Q[u]))->u];
		while (u == u0 && Q[u]);
		if (u == u0) break;
		if (!mark[u]) continue;
		for (u0 = u, n++; u != n; u = p) {
			id.fa[u] = fa[u] = n;
			if (Q[u]) Q[u]->sum -= ed[u]->w;
			Q[n] = meld(Q[n], Q[u]);
			p = id[ed[u]->u];
			nxt[p == n ? u0 : p] = u;
}}}

static i64 ocnt;
static int rt;
i64 expand(int, int);
i64 _expand(int x) {
	i64 r = 0;
	for (int u = nxt[x]; u != x; u = nxt[u]) {
        r += expand(ed[u]->v, u);
        if (ed[u]->u == rt)
            ocnt++;
        else
            r += ed[u]->w0;
    }
	return r;
}
i64 expand(int x, int t) {
	i64 r = 0;
	for ( ; x != t; x = fa[x])
		r += _expand(x);
	return r;
}
#define ACM_END

inline void link(int u, int v, i64 w) {
	in[v].push_back({u, v, w, w});
}

int main() {
    int K;
    scanf("%d%d%d", &n, &m, &K);
	for (int i = 0; i < m; i++) {
		int u, v;
        i64 w;
		scanf("%d%d%lld", &u, &v, &w);
        //w = (w << 19) + rand() % 10;
		link(u, v, w);
	}

    n++;
    int n0 = n;
	rt = n;
    for (int i = 1; i < n; i++)
        /*if (id[i] == rp)*/ link(rt, i, INF);
	for (int i = 1; i <= n; i++)  // ensure strong connectivity
		link(i > 1 ? i - 1 : n, i, INF);

    i64 l = 0, r = INF;
    while (l < r) {
        i64 mi = (l + r) / 2;
        n = n0;
        for (int v = 1; v < n; v++)
        for (auto &e : in[v]) {
            if (e.u == rt) e.w0 = mi;
            e.w = e.w0;
        }

        mempos = 0;
        contract();

        ocnt = 0;
        i64 sum = expand(rt, n);
        //printf("cnt = %lld\n", ocnt);
        if (ocnt == K) {
            printf("%lld\n", sum);
            break;
        } else if (ocnt < K) r = mi - 1;
        else l = mi + 1;
    }

	return 0;
}
