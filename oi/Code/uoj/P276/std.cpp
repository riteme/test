#include <bits/stdc++.h>
#define M 100010
#define mxN 2000010

using namespace std;

typedef long long ll;

struct node
{
	ll F; int S; 
	node(){} node(ll a, int b) {F = a, S = b;} 
	bool operator < (const node& X) const {return F < X.F;}
};

int H[M], N[M], G[M], Cnt = 0, n;

ll k, V[M], ans = 1e18;

node Lis[M];

int cnt = 0, cnt1 =0;

struct Splay
{
	int C[mxN][2], F[mxN], Rt[M], Sz[M], nodcnt;
	
	node V[mxN];
	
	void init() {memset(Sz, 0, sizeof Sz), memset(Rt, 0, sizeof Rt), nodcnt = 0;}
	
	void rot(int x)
	{
		int f = F[x], s = C[f][1] == x;
		C[F[f]][C[F[f]][1] == f] = x;
		C[f][s] = C[x][!s], C[x][!s] = f;
		F[C[f][s]] = f, F[x] = F[f], F[f] = x;
	}
	
	void splay(int x)
	{
		for(int f; F[x]; rot(x))
			if(F[f = F[x]]) rot(C[f][0] == x ^ C[F[f]][0] == f ? x : f);
	}
	
	int find(int r, ll s, bool b)
	{
		int ans = -1;
		for(int x = Rt[r]; x; )
			if((V[x].F < s) == b) ans = x, x = C[x][b]; else x = C[x][!b];
		if(ans != -1) splay(Rt[r] = ans);
		return ans;
	}
	
	int nxt(int r, ll s) {return find(r, s, 0);}
	int pre(int r, ll s) {return find(r, s, 1);}
	
	void insert(int r, node s)
	{
		Sz[r]++;
		if(!Rt[r]) {V[++nodcnt] = s, Rt[r] = nodcnt; return;}
		int p = pre(r, s.F), x = nxt(r, s.F);
		if(x == -1) splay(p), V[C[p][1] = ++nodcnt] = s, Rt[r] = p, F[nodcnt] = p; else {
			splay(x), Rt[r] = x;
			if(p != -1) splay(p), Rt[r] = p;
			if(V[x].F == s.F) V[x].S = max(V[x].S, s.S), Sz[r]--; else V[C[x][0] = ++nodcnt] = s, F[nodcnt] = x;
		}
	}
	
	node nxtv(int r, ll x) {int s = nxt(r, x); return s == -1 ? node(0, -1) : V[nxt(r, x)];}
	node prev(int r, ll x) {int s = pre(r, x); return s == -1 ? node(0, -1) : V[pre(r, x)];}
	int size(int r) {return Sz[r];}
	
	void get(int x, node* X, int& t)
	{
		if(C[x][0]) get(C[x][0], X, t);
		X[++t] = V[x];
		if(C[x][1]) get(C[x][1], X, t);
	}
	
	int getlis(int r, node* X) {int t = 0; get(Rt[r], X, t); return t;}
} X;

inline void addedge(int x, int y, ll z) {G[++Cnt] = y, N[Cnt] = H[x], H[x] = Cnt, V[Cnt] = z;}

void merge(int x, int y, ll dis, int dep)
{
	int t = X.getlis(x, Lis);
	for(int i = 1; i <= t; i++) {
		node s = X.nxtv(y, dis * 2 - Lis[i].F);
		if(s.S != -1) ans = min(ans, (Lis[i].F + s.F - dis * 2) / (Lis[i].S + s.S - dep * 2));
		s = X.prev(y, dis * 2 - Lis[i].F);
		if(s.S != -1) ans = min(ans, -(Lis[i].F + s.F - dis * 2) / (Lis[i].S + s.S - dep * 2));
	}
	for(int i = 1; i <= t; i++) X.insert(y, Lis[i]);
}

int DFS(int x, int f = 0, ll dis = 0, int dep = 0)
{
	int tar = x;
	X.insert(x, node(dis, dep));
	for(int tmp, T = H[x]; T; T = N[T]) if(G[T] != f) {
		if(X.size(tmp = DFS(G[T], x, dis + V[T], dep + 1)) > X.size(tar)) swap(tmp, tar);
		merge(tmp, tar, dis, dep);
	}
	return tar;
}

template <class T> inline void Read(T& x)
{
	x = 0;
	char ch = getchar();
	while(ch < '0') ch = getchar();
	while(ch >= '0') x = x * 10 + ch - '0', ch = getchar();
}

int main()
{
	scanf("%d%lld", &n, &k);
	X.init();
	for(int i = 1, a, b; i < n; i++) {
		ll c;
		Read(a), Read(b), Read(c);
		addedge(a, b, c - k), addedge(b, a, c - k);
	}
	DFS(1);
	return printf("%lld\n", ans), 0;
}
