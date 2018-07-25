#include<iostream>
#include<cstdio>
using namespace std;
int e[50001];
int f[50001];
int n;
int t=0;
int dis[50001];
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
int Find(int x)
{
	while (f[x]!=x)
		x=f[x];
	return x;
}
double sqr(int x)
{
   return (double)(x*x);
}
void unions(int x,int y)
{
	f[y]=x;
}
double LCA(int x,int y)
{
	if (x==y) return 0; 
	int u=x;
	int v=y;
	double sum=0;
	double Ans=0;
	int p[10001];
	int t=0;
	if (dis[u]<dis[v])
	{
		while (dis[u]!=dis[v])
			{
			v=f[v];
			t++;
			p[t]=e[v];
			}
	}else 
	{
		while (dis[u]!=dis[v])
			{
			u=f[u];
			t++;
			p[t]=e[u];
			}
	}
	while (u!=v)
	{
		u=f[u];
		v=f[v];
		t++;
		p[t]=e[u];
		t++;
		p[t]=e[v];
	}
	p[t]=e[x];
	t++;
	p[t]=e[y];
    for (int i=1;i<=t;i++)
    	sum+=p[i];
    sum=sum/(double)t;
    for (int i=1;i<=t;i++)
    Ans+=sqr(sum-(double)p[i]);
    return Ans/(double)t;
}
int main()
{
	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);
 scanf("%d",&n);
 for (int i=1;i<=n;i++)
 {
 	char s;
 	int x,y;
 	cin>>s;
    scanf("%d%d",&x,&y);
    if (s=='A')
    {
       t++;
       f[t]=x;
       e[t]=y;
       if (x!=0)
       dis[t]=dis[x]+1;
    }
    else 
    {
     printf("%.6lf\n",LCA(x,y));
    }
 } 
}