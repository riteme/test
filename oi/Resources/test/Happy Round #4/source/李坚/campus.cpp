#include<iostream>
#include<cstdio>
using namespace std;
int f[3001];
int m[2001][2001];
int map[2001][2001];
int dis[3001];
int N,M;
inline int read()
{
	int x=0;
	int f=1;
	char ch=getchar();
	while (ch<'0'|| ch>'9')
	{
		if (ch=='-')
			f=-1;
		ch=getchar();
	}
	while (ch<='9' && ch>='0')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void Dfs(int x)
{
  if (m[x][0]==0) return ;
  for (int i=1;i<=m[x][0];i++)
  {
  	int k=m[x][i];
  	if (f[k]==k)
  	{
  		f[k]=x;
  		dis[k]=dis[x]+1;
  		Dfs(k);
  	}
  }
}
void Init()
{
	scanf("%d%d",&N,&M);
    for (int i=1;i<=N;i++)
    f[i]=i;
    f[1]=1;
	for (int i=1;i<=N-1;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
        m[u][0]++;
        m[u][m[u][0]]=v;
        m[v][0]++;
        m[v][m[v][0]]=u;
        map[u][v]=w;
        map[v][u]=w;
	}
}
int LCA(int x,int y)
{
	int Load1[10000];
	int Load2[10000];
	int t1=0;
	int t2=0;
	int v;
	int u;
    if (x==y) return 0;
    if (dis[x]>dis[y])
    {
    	v=x;
    	u=y;
    }
    else 
    {
    	v=y;
    	u=x;
    }
	while (dis[u]!=dis[v])
		v=f[v];
	while (u!=v)
	{
		u=f[u];
		v=f[v];
	}
	t1++;
	Load1[t1]=x;
	while (x!=u)
	{
		x=f[x];
        t1++;
        Load1[t1]=x;
	}
	t2++;
	Load2[t2]=y;
	while (y!=u)
	{
       y=f[y];
       t2++;
       Load2[t2]=y;
	}
	int p[10001];
	p[0]=0;
	for (int i=1;i<=t1-1;i++)
    {
    	p[0]++;
    	p[p[0]]=map[Load1[i]][Load1[i+1]];
    }
    for (int i=t2;i>=2;i--)
    {
    	p[0]++;
    	p[p[0]]=map[Load2[i]][Load2[i-1]];
    }
	int ans=0;
	for (int i=1;i<=p[0];i++)
	{
		if (ans+p[i]<p[i])
			ans=p[i];
			else ans+=p[i];
	}
	return ans;
}
int main()
{
	freopen("campus.in","r",stdin);
	freopen("campus.out","w",stdout);
	Init();
	Dfs(1);
	for (int i=1;i<=M;i++)
	{
      int x,y;
      scanf("%d%d",&x,&y);
      printf("%d\n",LCA(x,y));
	}
}