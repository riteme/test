#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define M 1000000 + 5

int Case, n, m, tot, id, sz, cnt, Dfn[M], Low[M], Id[M], Sum[M], Stack[M], Dp[M][2];
bool Flag[M];
vector<int> Vec[M];

struct ACAM
{
	int fail, flag, son[2];
}h[M];

int NewNode()
{
	tot ++;
	h[tot].fail = h[tot].flag = h[tot].son[0] = h[tot].son[1] = 0;
	Dfn[tot] = Low[tot] = Id[tot] = 0;
	return tot;
}

int NewScc()
{
	cnt ++;
	Sum[cnt] = Dp[cnt][0] = Dp[cnt][1] = 0;
	Vec[cnt].clear();
	return cnt;
}

inline int Merge(int op1, int op2)
{
	if (!op1)
		return op2;
	if (!op2)
		return op1;
	if (op1 == -1 || op2 == -1)
		return -1;
	if (op1 == op2)
		return op1;
	return n + 1;
}

void Read(int op)
{
	static char s[M];
	scanf("%s", s);
	int u = 0;
	for (int i = 0; s[i]; i ++)
	{
		int j = s[i] - '0';
		if (!h[u].son[j])
			h[u].son[j] = NewNode();
		u = h[u].son[j];
	}
	h[u].flag = Merge(h[u].flag, op);
}

void BuildFail()
{
	static int q[M];
	int l = 1, r = 0;
	for (int i = 0; i < 2; i ++)
		if (h[0].son[i])
			q[++ r] = h[0].son[i], h[h[0].son[i]].fail = 0;
	while (l <= r)
	{
		int z = q[l ++];
		h[z].flag = Merge(h[z].flag, h[h[z].fail].flag);
		for (int i = 0; i < 2; i ++)
		{
			if (!h[z].son[i])
				h[z].son[i] = h[h[z].fail].son[i];
			else
			{
				h[h[z].son[i]].fail = h[h[z].fail].son[i];
				q[++ r] = h[z].son[i];
			}
		}
	}
}

void dfs(int z)
{
	Dfn[z] = Low[z] = ++ id;
	Stack[++ sz] = z;
	Flag[z] = true;
	for (int i = 0; i < 2; i ++)
	{
		int d = h[z].son[i];
		if (h[d].flag == -1)
			continue ;
		if (!Dfn[d])
			dfs(d), Low[z] = min(Low[z], Low[d]);
		else if (Flag[d])
			Low[z] = min(Low[z], Dfn[d]);
	}
	if (Low[z] == Dfn[z])
	{
		NewScc();
		int j;
		do
		{
			j = Stack[sz --];
			Id[j] = cnt;
			Sum[cnt] = Merge(Sum[cnt], h[j].flag);
			Flag[j] = false;
		} while (j != z);
	}
}

inline void Update(int z, int val)
{
	if (val > Dp[z][1] && val != Dp[z][0])
	{
		Dp[z][1] = val;
		if (Dp[z][1] > Dp[z][0])
			swap(Dp[z][1], Dp[z][0]);
	}
}

void DFS(int z)
{
	if (Flag[z])
		return ;
	Flag[z] = true;
	Dp[z][0] = Sum[z], Dp[z][1] = 0;
	for (int d : Vec[z])
	{
		DFS(d);
		int cur_1 = Merge(Dp[d][0], Sum[z]);
		int cur_2 = Merge(Dp[d][1], Sum[z]);
		Update(z, cur_1);
		Update(z, cur_2);
	}
}

int main()
{
	for (scanf("%d", &Case); Case; Case --)
	{
		tot = -1, id = sz = cnt = 0, NewNode();
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i ++)
			Read(i);
		for (int i = 1; i <= m; i ++)
			Read(-1);
		BuildFail();
		for (int i = 0; i <= tot; i ++)
			if (!Dfn[i] && h[i].flag != -1)
				dfs(i);
		for (int i = 0; i <= tot; i ++)
			if (h[i].flag != -1)
				for (int j = 0; j < 2; j ++)
				{
					int d = h[i].son[j];
					if (h[d].flag != -1 && Id[i] != Id[d])
						Vec[Id[i]].push_back(Id[d]);
				}
		for (int i = 1; i <= cnt; i ++)
			Flag[i] = false;
		DFS(Id[0]);
		puts(Dp[Id[0]][0] == n + 1 ? "Yes" : "No");
	}
	return 0;
}
