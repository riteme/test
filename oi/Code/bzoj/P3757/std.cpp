#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<ctime>
#include<queue>
#include<cmath>
#include<algorithm>
#define inf 1000000000
#define ll long long
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int bin[20];
int n,m,cnt,ans;
int top,ind,blo,blonum,root;
int res[100005],p[50005];
int fa[50005][17],deep[50005];
int c[50005],st[50005],dfn[50005],belong[50005];
bool vis[50005];
struct data{int to,next;}e[100005];int last[50005];
struct query{int u,v,a,b,id;}q[100005];
bool operator<(query a,query b)
{
	if(belong[a.u]==belong[b.u])return dfn[a.v]<dfn[b.v];
	else return belong[a.u]<belong[b.u];
}
void insert(int u,int v)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;
}
int dfs(int x)
{
	int size=0;
    dfn[x]=++ind;
	for(int i=1;i<=16;i++)
		if(deep[x]>=bin[i])
			fa[x][i]=fa[fa[x][i-1]][i-1];
		else break;
	for(int i=last[x];i;i=e[i].next)
	    if(e[i].to!=fa[x][0])
		{
			deep[e[i].to]=deep[x]+1;
			fa[e[i].to][0]=x;
			size+=dfs(e[i].to);
			if(size>=blo)
			{
				blonum++;
				for(int k=1;k<=size;k++)
					belong[st[top--]]=blonum;
				size=0;
			}
		}
	st[++top]=x;
	return size+1;
}
int lca(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	int t=deep[x]-deep[y];
	for(int i=0;bin[i]<=t;i++)
		if(t&bin[i])x=fa[x][i];
	for(int i=16;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	if(x==y)return x;
	return fa[x][0];
}
void reverse(int x)
{
	if(!vis[x]){vis[x]=1;p[c[x]]++;if(p[c[x]]==1)ans++;}
	else {vis[x]=0;p[c[x]]--;if(p[c[x]]==0)ans--;}
}
void solve(int u,int v)
{
	while(u!=v)
		if(deep[u]>deep[v])reverse(u),u=fa[u][0];
		else reverse(v),v=fa[v][0];
}
int main()
{
	bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
	n=read();m=read();
	blo=sqrt(n);
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++)
	{
		int u=read(),v=read();
		if(!u)root=v;
		else if(!v)root=u;
		else insert(u,v);
	}
	dfs(root);
	blonum++;
	while(top)belong[st[top--]]=blonum;
	for(int i=1;i<=m;i++)
	{
		q[i].u=read();q[i].v=read();
		if(dfn[q[i].u]>dfn[q[i].v])swap(q[i].u,q[i].v);
		q[i].a=read();q[i].b=read();
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	int t=lca(q[1].u,q[1].v);
	solve(q[1].u,q[1].v);
	reverse(t);
	res[q[1].id]=ans;
	if(p[q[1].a]&&p[q[1].b]&&q[1].a!=q[1].b)res[q[1].id]--;
	reverse(t);
	for(int i=2;i<=m;i++)
	{
		solve(q[i-1].u,q[i].u);
		solve(q[i-1].v,q[i].v);
		t=lca(q[i].u,q[i].v);
		reverse(t);
		res[q[i].id]=ans;
		if(p[q[i].a]&&p[q[i].b]&&q[i].a!=q[i].b)res[q[i].id]--;
		reverse(t);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",res[i]);
	return 0;
}
