#include <cstdio>

const int MaxN = 100005;
const int MaxM = 200005;
const int MaxNE = MaxM << 1;

const int BufSize = 3100000;

char buf[BufSize], *ins = buf, *outs = buf;

inline int getint()
{
	while (*ins < '0' || *ins > '9')
		++ins;

	int res = 0;
	while (*ins >= '0' && *ins <= '9')
		res = res * 10 + *ins++ - '0';
	return res;
}
inline void putint(int x)
{
	if (!x)
		*outs++ = '0';
	else
	{
		if (x < 0)
			*outs++ = '-', x = -x;

		char s_pool[6], *s = s_pool;
		for (; x; x /= 10)
			*s++ = x % 10 + '0';

		while (s-- != s_pool)
			*outs++ = *s;
	}
	*outs++ = ' ';
}

int n, m;
int adj[MaxN];

int nE = 1;
int next[MaxNE], go[MaxNE];
bool used[MaxNE];

int tour_n;
int tour[MaxM];

inline void addEdge(const int &u, const int &v)
{
	next[++nE] = adj[u], go[adj[u] = nE] = v;
}

int deg[MaxN];

namespace DirectedGraph
{
	void dfs(const int &u)
	{
		int &e = adj[u];
		while (e)
		{
			if (used[e])
				e = next[e];
			else
			{
				int id = e - 1;
				used[e] = true;
				dfs(go[e]);
				tour[++tour_n] = id;
			}
		}
	}

	inline bool solve()
	{
		n = getint(), m = getint();
		while (m--)
		{
			int u = getint(), v = getint();
			addEdge(u, v);
			--deg[u], ++deg[v];
		}

		for (int u = 1; u <= n; ++u)
			if (deg[u])
				return false;
		for (int u = 1; u <= n; ++u)
			if (adj[u])
			{
				dfs(u);
				break;
			}
		for (int u = 1; u <= n; ++u)
			if (adj[u])
				return false;
		return true;
	}
}

namespace UndirectedGraph
{
	inline int edgeId(const int &e)
	{
		int id = e >> 1;
		return e & 1 ? -id : id;
	}

	void dfs(const int &u)
	{
		int &e = adj[u];
		while (e)
		{
			if (used[e])
				e = next[e];
			else
			{
				int id = edgeId(e);
				used[e] = used[e ^ 1] = true;
				dfs(go[e]);
				tour[++tour_n] = id;
			}
		}
	}

	inline bool solve()
	{
		n = getint(), m = getint();
		while (m--)
		{
			int u = getint(), v = getint();
			addEdge(u, v), addEdge(v, u);
			++deg[u], ++deg[v];
		}

		for (int u = 1; u <= n; ++u)
			if (deg[u] & 1)
				return false;
		for (int u = 1; u <= n; ++u)
			if (adj[u])
			{
				dfs(u);
				break;
			}
		for (int u = 1; u <= n; ++u)
			if (adj[u])
				return false;
		return true;
	}
}

int main()
{
	fread(buf, 1, BufSize, stdin);

	if (getint() == 1 ? UndirectedGraph::solve() : DirectedGraph::solve())
	{
		puts("YES");
		for (int i = tour_n; i; --i)
			putint(tour[i]);
	}
	else
		puts("NO");

	fwrite(buf, 1, outs - buf, stdout);
	return 0;
}
