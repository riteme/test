#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 201000
#define M (N<<1)
using namespace std;
struct msns
{
	int v,n,f;
}e[M];
int head[N],cnt;
inline void add(int u,int v)
{
	e[cnt].n=head[u];
	head[u]=cnt;
	e[cnt++].v=v;
}
int n,m;
struct DSLTFL
{
	int low[N],dfn[N],stk[N],belong[N];
	int index,top,block;
	bool in[N];
	
	int vis[N],deep[N];
	int col[N];
	bool flag;
	void dfs1(int x,int p,int fail)
	{
		vis[x]=block;
		col[x]=col[p]^1;
		if(x==fail)return ;
		int i,v;
		for(i=head[x];i+1;i=e[i].n)
		{
			v=e[i].v;
			if(v==p||belong[v]!=belong[x])continue;
			if(vis[v]==block)
			{
				if(col[x]==col[v])flag=1;
				continue;
			}
			e[i].f=1;
			dfs1(v,x,fail);
		}
	}
	void dfs3(int x,int p,int fail)
	{
		if(x==fail)return ;
		int i,v;
		for(i=head[x];i+1;i=e[i].n)if(e[i].f==1)
		{
			e[i].f=2,e[i^1].f=2;
			dfs3(e[i].v,x,fail);
		}
	}
	void tarjan(int u,int pre)
	{
		int i,v;
		low[u]=dfn[u]=++index;
		stk[top++]=u;
		in[u]=true;
		for(i=head[u];i+1;i=e[i].n)
		{
			v=e[i].v;
			if(v==pre)continue;
			if(!dfn[v])
			{
				tarjan(v,u);
				if(low[u]>low[v])low[u]=low[v];
				if(low[v]>=dfn[u])
				{
					block++;
					int vn;
					do{
						vn=stk[--top];
						belong[vn]=block;
						in[vn]=false;
					}while(vn!=v);
					belong[u]=block;
					
					flag=0;
					dfs1(v,0,u);
					if(!flag)dfs3(v,0,u);
				}
			}
			else if(in[v]&&low[u]>dfn[v])
				low[u]=dfn[v];
		}
	}
}tj;
ll f[N],g[N];
ll ans0,ans1;
int cot[N];
void dfs1(int x,int p)
{
	cot[x]=1;
	f[x]=1,g[x]=0;
	//f 0 g 1
	int i,v;
	for(i=head[x];i+1;i=e[i].n)if(e[i].f==2)
	{
		v=e[i].v;
		if(v==p)continue;
		dfs1(v,x);
		f[x]+=g[v],g[x]+=f[v];
	}
	ans0+=f[x]-1,ans1+=g[x];
}
void dfs2(int x,int p)
{
	int i,v;
	for(i=head[x];i+1;i=e[i].n)if(e[i].f==2)
	{
		v=e[i].v;
		if(v==p)continue;
		
		ans0+=g[x]-f[v];
		ans1+=f[x]-g[v];		
		f[v]=g[x],g[v]=f[x];
		dfs2(v,x);
	}
}
int main()
{
//	freopen("C.in","r",stdin);
	
	int i,j,k;
	int a,b,c;
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b),add(b,a);
	}
	tj.tarjan(1,0);
	
	for(i=1;i<=n;i++)if(!cot[i])
	{
		dfs1(i,0);
		dfs2(i,0);
	}
	
	cout<<ans0/2<<' '<<ans1/2<<endl;
	
	return 0;
}
