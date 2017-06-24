#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 300000 + 5;
const int maxm = 500000 + 5;

struct Edge{
    int u,v;
    Edge(int u=0,int v=0):u(u),v(v){}
}e[maxm];
int Case,n,m,w,q,stamp,dfn[maxn],low[maxn],iscut[maxn],bccno[maxn];
int scnt,stack[maxm],bcc_cnt;
int Col[maxn << 1], An[maxn << 1][19], Dep[maxn << 1], Log[maxn << 1];
vector <int> vec[maxn << 1],bcc[maxn],Belong[maxn];
vector <int> :: iterator it;

void tarjan(int index,int fa)
{
    int child=0,tmp;
    dfn[index]=low[index]=++stamp;
    for(int i=0;i<vec[index].size();i++)
    {
        tmp=e[vec[index][i]].v;
        if(!dfn[tmp])
        {
            stack[++scnt]=vec[index][i],child++;
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);
            if(low[tmp]>=dfn[index])
            {
                iscut[index]=1;
                bcc[++bcc_cnt].clear();
                while(1)
                {
                    int num=stack[scnt--];
                    if(bccno[e[num].u]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].u);
                        bccno[e[num].u]=bcc_cnt;
                    }
                    if(bccno[e[num].v]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].v);
                        bccno[e[num].v]=bcc_cnt;
                    }
                    if(e[num].u==index && e[num].v==tmp)
                        break;
                }
            }
        }
        else if(dfn[tmp]<dfn[index] && tmp!=fa)
        {
            stack[++scnt]=vec[index][i];
            low[index]=min(low[index], dfn[tmp]);
        }
    }
    if(fa<0 && child==1)
        iscut[index]=0;
}

void find_bcc()
{
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    stamp=scnt=bcc_cnt=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
}

void dfs(int z, int fa, int col)
{
	Col[z] = col;
	for (int i = 0; i < vec[z].size(); i ++)
	{
		int d = vec[z][i];
		if (d == fa) continue ;
		An[d][0] = z, Dep[d] = Dep[z] + 1;
		for (int j = 1, x = An[z][0]; x; x = An[x][j ++])
			An[d][j] = x;
		dfs(d, z, col);
	}
}

int LCA(int u, int v)
{
	if (Dep[u] < Dep[v]) swap(u, v);
	for (int t = Dep[u] - Dep[v]; t; t -= (t & -t))
		u = An[u][Log[t & -t]];
	if (u == v) return u;
	for (int i = 18; An[u][0] != An[v][0]; i --)
		if (An[u][i] != An[v][i])
			u = An[u][i], v = An[v][i];
	return An[u][0];
}

int main()
{
	for (scanf("%d", &Case); Case; Case --)
	{
		scanf("%d%d%d", &n, &m, &w);
		for (int i = 1; i <= n; i ++)
		{
			Dep[i] = Col[i] = 0;
			for (int j = 0; j < 19; j ++)
				An[i][j] = 0;
			Belong[i].clear();
			vec[i].clear();
		}
		for (int i = 1, u, v; i <= m; i ++)
		{
			scanf("%d%d", &u, &v);
			vec[u].push_back(i);
			e[i] = Edge(u, v);
			vec[v].push_back(i + m);
			e[i + m] = Edge(v, u);
		}
		find_bcc();
		for (int i = 1; i <= n + bcc_cnt; i ++)
		{
			vec[i].clear();
			Log[i + 1] = Log[i + 1 >> 1] + 1;
		}
		for (int d = 1; d <= bcc_cnt; d ++)
			for (int i = 0; i < bcc[d].size(); i ++)
			{
				int x = bcc[d][i];
				Belong[x].push_back(d);
				vec[x].push_back(n + d);
				vec[n + d].push_back(x);
			}
		for (int i = 1; i <= n; i ++)
			sort(Belong[i].begin(), Belong[i].end());
		for (int i = 1; i <= m; i ++)
		{
			int u = e[i].u, v = e[i].v;
			if (Belong[u].size() > Belong[v].size())
				swap(u, v);
			bool ok = 1;
			for (int j = 0; ok && j < Belong[u].size(); j ++)
			{
				int x = Belong[u][j];
				it = lower_bound(Belong[v].begin(), Belong[v].end(), x);
				if (it != Belong[v].end() && *it == x) ok = 0;
			}
			if (!ok) continue ;
			vec[u].push_back(v);
			vec[v].push_back(u);
		}
		for (int i = 1, col = 0; i <= n; i ++)
			if (!Dep[i])
				dfs(i, 0, ++ col);
		int u = 1, v = n;
		if (Col[u] != Col[v] || Col[u] != Col[w])
		{
			puts("NO");
			continue ;
		}
		int lca = LCA(u, v);
		int _lca = LCA(lca, w);
		bool ok = 0;
		if (_lca == lca)
		{
			int _u = LCA(u, w), _v = LCA(v, w);
			if (_u == w || (_u == An[w][0] && _u > n)) ok = 1;
			if (_v == w || (_v == An[w][0] && _v > n)) ok = 1;
		}
		else ok = (An[lca][0] == _lca && _lca == w && lca > n);
		puts(ok ? "YES" : "NO");
	}
	return 0;
}
