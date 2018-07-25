#include <cstdio>
#include <algorithm>
using namespace std;
#define N 30 + 5
#define D 1000 + 5
#define M 100000 + 5
#define INF 593119681

int n, m, s, Min, Max, S, T, tot, Id[N][N], C_1[N][N], W_1[N][N], C_2[N][N], W_2[N][N], Head[D], Dfn[D], q[D];

struct Edge
{
	int next, node, flow;
}h[M];

inline void addedge(int u, int v, int fl)
{
	h[++ tot].next = Head[u], Head[u] = tot;
	h[tot].node = v, h[tot].flow = fl;
	h[++ tot].next = Head[v], Head[v] = tot;
	h[tot].node = u, h[tot].flow = 0;
}

inline void Flip_1()
{
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j * 2 < m; j ++)
		{
			swap(C_1[i][j], C_1[i][m - j]);
			swap(W_1[i][j], W_1[i][m - j]);
		}
	for (int i = 1; i < n; i ++)
		for (int j = 1; j * 2 <= m; j ++)
		{
			swap(C_2[i][j], C_2[i][m - j + 1]);
			swap(W_2[i][j], W_2[i][m - j + 1]);
		}
}

inline void Flip_2()
{
	for (int j = 1; j < m; j ++)
		for (int i = 1; i * 2 <= n; i ++)
		{
			swap(C_1[i][j], C_1[n - i + 1][j]);
			swap(W_1[i][j], W_1[n - i + 1][j]);
		}
	for (int j = 1; j <= m; j ++)
		for (int i = 1; i * 2 < n; i ++)
		{
			swap(C_2[i][j], C_2[n - i][j]);
			swap(W_2[i][j], W_2[n - i][j]);
		}
}

inline bool BFS(int st)
{
	for (int i = 0; i <= n * m; i ++)
		Dfn[i] = 0;
	int l = 1, r = 0;
	q[++ r] = st, Dfn[st] = 1;
	while (l <= r)
	{
		int z = q[l ++];
		for (int i = Head[z]; i; i = h[i].next)
		{
			int d = h[i].node, p = h[i].flow;
			if (Dfn[d] || !p) continue ;
			Dfn[d] = Dfn[z] + 1;
			q[++ r] = d;
			if (d == T) return 1;
		}
	}
	return 0;
}

int Dinic(int z, int inflow)
{
	if (z == T || !inflow) return inflow;
	int ret = inflow, flow;
	for (int i = Head[z]; i; i = h[i].next)
	{
		int d = h[i].node, p = h[i].flow;
		if (Dfn[d] != Dfn[z] + 1) continue ;
		flow = Dinic(d, min(ret, p));
		ret -= flow, h[i].flow -= flow, h[i ^ 1].flow += flow;
		if (!ret) break ;
	}
	if (ret == inflow) Dfn[z] = -1;
	return inflow - ret;
}

void dfs(int z)
{
	Dfn[z] = 1;
	for (int i = Head[z]; i; i = h[i].next)
	{
		int d = h[i].node, p = h[i].flow;
		if (p && !Dfn[d]) dfs(d);
	}
}

bool Handle(int k)
{
	for (S = 0, T = 2; T <= n * m; T ++)
	{
		tot = 1;
		for (int i = 0; i <= n * m; i ++)
			Head[i] = 0;
		addedge(S, 1, s);
		for (int i = 1; i <= n; i ++)
			for (int j = 1; j < m; j ++)
			{
				if (C_1[i][j] > k) continue ;
				addedge(Id[i][j], Id[i][j + 1], W_1[i][j]);
				addedge(Id[i][j + 1], Id[i][j], W_1[i][j]);
			}
		for (int i = 1; i < n; i ++)
			for (int j = 1; j <= m; j ++)
			{
				if (C_2[i][j] > k) continue ;
				addedge(Id[i][j], Id[i + 1][j], W_2[i][j]);
				addedge(Id[i + 1][j], Id[i][j], W_2[i][j]);
			}
		int res = 0;
		while (BFS(S)) res += Dinic(S, INF);
		for (int i = 1; i <= n * m; i ++) Dfn[i] = 0;
		dfs(1);
		for (int i = 1; i <= n * m; i ++)
			if (!Dfn[i]) return 0;
	}
	return 1;
}

bool Check(int k)
{
	bool ok = 0;
	for (int i = 0; i < 4; i ++)
	{
		if (!ok && Handle(k)) ok = 1;
		if (i & 1) Flip_1();
			else Flip_2();
	}
	return ok;
}

int main()
{
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 1, id = 0; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			Id[i][j] = ++ id;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j < m; j ++)
		{
			scanf("%d%d", C_1[i] + j, W_1[i] + j);
			Max = max(Max, C_1[i][j]);
		}
	for (int i = 1; i < n; i ++)
		for (int j = 1; j <= m; j ++)
		{
			scanf("%d%d", C_2[i] + j, W_2[i] + j);
			Max = max(Max, C_2[i][j]);
		}
	int l = 1, r = Max + 1;
	while (l < r)
	{
		int mid = l + r >> 1;
		if (Check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l == Max + 1 ? -1 : l);
	return 0;
}
