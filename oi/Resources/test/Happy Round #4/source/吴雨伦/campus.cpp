#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <queue>
#define ED printf("\n")
using namespace std;

int t[2000][2000];
int n,m,ans;			//n:Nodes m:Asking
int flag[2000];

stack <int> s;

void inp()
{
	int i,ta,tb,tk;
	scanf("%d%d",&n,&m);
	for(i=0;i<n-1;i++)
	{
		scanf("%d%d%d",&ta,&tb,&tk);
		if(t[ta][tb]==0)
		{
			t[ta][tb]=tk;
			t[tb][ta]=tk;
		}

		else if(tk>t[ta][tb])
		{
			t[ta][tb]=tk;
			t[tb][ta]=tk;
		}

	//	printf("Link:%d-%d=%d\n",ta,tb,tk);
	}
}

int way(int a,int b)
{
	int r,lca;

	stack <int> sa,sb;
	stack <int> qb;
	while(a>0) sa.push(a),a=a/2;
	while(b>0) sb.push(b),b=b/2;

	while(sa.size()>0 && sb.size()>0 && sa.top()==sb.top()) sa.pop(),sb.pop();

//	if(sa.size()>0) lca=sa.top();
//	else lca=sb.top();
	
	
	while(sb.size()>0) qb.push(t[sb.top()][sb.top()/2]),sb.pop();

	while(qb.size()>0) s.push(qb.top()),qb.pop();

	while(sa.size()>0) s.push(t[sa.top()][sa.top()/2]),sa.pop();

	//printf("%d\n",lca);
}

int sum(int *ll,int ge,int ed)
{
	int su=0,i;
	for(i=ge;i<=ed;i++) su+=ll[i];
	return su;
}

void fin()
{
	int ma=s.size(),a[50],i,j,xx,tmp;
	for(i=0;i<ma;i++) a[i]=s.top(),s.pop();

	//for(i=0;i<ma;i++) printf("%d ",a[i]);ED;

	xx=a[0];
	for(i=0;i<ma;i++)
		for(j=0;j<ma-i;j++) 	
		{
			tmp=sum(a,j,j+i);
			if(xx<tmp)  xx=tmp;
		}
		
	printf("%d\n",xx);
 
}

void out(int a,int b)
{
	printf("%d\n",t[a][b]);
}

void dfs(int be,int v)
{
	int i,j,k;

	printf("->%d,%d\n",be,v);

	flag[be]=1;

	if(be==ans) 
	{
		printf("Catch~%d\n",v);
		s.push(v);
		return;
	}

	for(i=0;i<=n;i++)
	{
		if(t[be][i]!=0 && flag[i]==0)
		{
			dfs(i,v+t[be][i]);
			flag[i]=0;
		}
	}
}

void js()
{
	int maxx=s.top();
	while(s.size()>0) 
	{
		if(s.top()>maxx) 
			maxx=s.top();
		s.pop();
	}
	printf("%d\n",maxx);
}

void ask()
{
	int i,ta,tb;
	for(i=0;i<m;i++)
	{
		scanf("%d%d",&ta,&tb);
		if(ta==tb) printf("0\n");
		else
		{
			way(ta,tb);
			fin();
		}
		
	}
}

int main()
{
	freopen("campus.in","r",stdin);
	freopen("campus.out","w",stdout);
	inp();
	ask();

	//system("sleep 60");
	
	return 0;

}