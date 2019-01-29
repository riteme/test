#include <cstdio>
#include <cctype>
#include <set>
#include <map>
#include <algorithm>
#define V_MAX 200000
#define E_MAX 400000
#define lld "%llu"
typedef unsigned long long lnt;
typedef bool bnt;
typedef void vnt;
struct buf
{
	operator int()
	{
		register int c = getchar(), x = 0;
		for (;!isdigit(c); c = getchar());
		for (; isdigit(c); c = getchar()) x = x * 10 - '0' + c;
		return x;
	}
} fio;
struct edg
{
	int v, c; edg * e, * f;
} ES[E_MAX * 10], * ER = ES, * EQ, * EA[V_MAX + 1], * EC[V_MAX + 1], * ED[V_MAX + 1];
inline vnt edg_ins(edg * EA[], int u, int v, int c = 1)
{
	*ER = (edg) {v, c, EA[u], ER + 1}, EA[u] = ER++;
	*ER = (edg) {u, c, EA[v], ER - 1}, EA[v] = ER++;
}
inline vnt edg_ins(edg * EA[], int u, int v, edg * f)
{
	*ER = (edg) {v, 1, EA[u], f}, EA[u] = ER++;
}
int p, bcc, vis[V_MAX + 1];
lnt ans, g, f[V_MAX + 1];
lnt dfs(int u, int x, int & y, lnt dwn = 0) // dp
{
	std::set<int> U;
	int v = 0, c = 1;
	lnt sum = 0, tmp = 0;
	vis[u] = bcc;
	if (u == p) g += dwn; else dwn += f[u];
	for (edg * e = ED[u]; e; e = e->e)
		if (e->c)
		{
			U.insert(e->v);
			if (vis[e->v] == bcc)
				e->c = -++c, y = e->v;
			else
				e->c = ++c, vis[e->v] = bcc;
		}
	for (edg * e = ED[u]; e; e = e->e)
		if (e->c)
		{
			e->f->c = 0;
			if (e->c < 0)
			{
				sum += f[v = e->v];
				if (v == p) g += dwn - f[x];
			}
			else if (e->c < c)
				tmp += dfs(e->v, u, v, f[u]);
			else
				sum += dfs(e->v, x, v, dwn), y = v;
			U.erase(e->v);
			if (U.find(v) != U.end()) tmp -= f[v];
		}
	ans += f[u] * (sum + tmp), sum += f[u];
	if (u == p) g += sum + tmp - f[u];
	return sum;
}
struct dat { int u, v; } S[E_MAX + 1];
std::map<int, bnt> EB[V_MAX + 1];
std::map<int, edg *> EF[V_MAX + 1];
int E, Sm, Sn, dfn[V_MAX + 1], low[V_MAX + 1], Ql, Qr, Q[V_MAX + 1];
struct res
{
	int v, c;
	inline bnt operator < (const res & e) const { return c > e.c; }
} ET[V_MAX];
inline vnt sol() // parse, solve
{
	static int s, t, x, u, v, c = 0, a[E_MAX * 2];
	int m = 0;
	for (int i = Sn; i >= Sm; --i)
		a[m++] = S[i].u, a[m++] = S[i].v, EB[S[i].u][S[i].v] = EB[S[i].v][S[i].u] = true;
	std::sort(a, a + m);
	int n = int(std::unique(a, a + m) - a);
	Ql = Qr = E = 0;
	for (int i = 0; i < n; E += int(EB[a[i++]].size()))
		if (EB[a[i]].size() == 2) Q[++Qr] = a[i];
	if (E == n * 2)
	{
		for (int i = 0; i < n; ++i)
			ans += g * f[a[i]], g += f[a[i]], EB[a[i]].clear();
		f[p] = g, g = 0;
	}
	else
	{
		m = n, EQ = ER;
		while (Ql < Qr && m > 2)
		{
			x = Q[++Ql], --m;
			u = (EB[x].begin())->first;
			for (std::map<int, bnt>::iterator i = EB[x].begin(); i != EB[x].end(); ++i)
			{
				v = i->first;
				if (i->second) edg_ins(EC, v, x, ++c);
			}
			EB[u].erase(x), EB[v].erase(x);
			if (EB[u].find(v) == EB[u].end())
				EB[u][v] = EB[v][u] = false;
			else
			{
				EB[u][v] = EB[v][u] = true;
				if (EB[u].size() == 2) Q[++Qr] = u;
				if (EB[v].size() == 2) Q[++Qr] = v;
			}
		}
		if (m > 2)
			for (int i = 0; i < n; ++i)
				EB[a[i]].clear(), EC[a[i]] = NULL;
		else
		{
			if (n > 2) s = u, t = v;
			else s = a[0], t = a[1];
			if (EB[s][t]) edg_ins(EC, s, t, ++c);
			for (int i = 0; i < n; ++i)
			{
				E = 0;
				for (edg * e = EC[a[i]]; e; e = e->e)
					ET[E++] = (res) {e->v, e->c};
				std::sort(ET, ET + E);
				for (int j = 0; j < E; ++j)
				{
					edg * f = ET[j].v > a[i] ? NULL : EF[ET[j].v][a[i]];
					if (ET[j].v > a[i])
						EF[a[i]][ET[j].v] = ER;
					else
						f->f = ER;
					edg_ins(ED, a[i], ET[j].v, f);
				}
			}
			++bcc, dfs(s, s, t), f[p] += g, g = 0;
			for (int i = 0; i < n; ++i)
				EB[a[i]].clear(), EC[a[i]] = NULL, ED[a[i]] = NULL, EF[a[i]].clear();
		}
		ER = EQ;
	}
}
vnt dft(int u, int a = 0) // tarjan v-bcc
{
	static int dfc;
	dfn[u] = low[u] = ++dfc;
	for (edg * e = EA[u]; e; e = e->e)
		if (e->c)
		{
			e->f->c = 0;
			if (!dfn[e->v])
				S[++Sn] = (dat) {u, e->v}, dft(e->v, u), low[u] = std::min(low[u], low[e->v]);
			else if (e->v != a)
			{
				low[u] = std::min(low[u], dfn[e->v]);
				if (dfn[u] > dfn[e->v]) S[++Sn] = (dat) {e->v, u};
			}
			if (dfn[u] <= low[e->v])
			{
				for (Sm = Sn; S[Sm].u != u || S[Sm].v != e->v; --Sm);
				p = u, sol(), Sn = Sm - 1;
			}
		}
}
int V, u, v;
int main()
{
	V = fio, E = fio;
	while (E--)
		if ((u = fio) != (v = fio))
			edg_ins(EA, u, v);
	for (u = 1; u <= V; ++u)
		f[u] = 1;
	for (u = 1; u <= V; ++u)
		if (!dfn[u]) dft(u);
	printf(lld "\n", ans);
	return 0;
}
