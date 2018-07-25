#include<cstdio>
#include<iostream>
using namespace std;
double F[101][65536];
int N,K,t;
int v[20],d[20],p[20];
int main()
{
	for(int i=1;i<=16;i++)p[i]=1<<(i-1);
	scanf("%d%d",&N,&K);
	for(int i=1;i<=K;i++)
	{
		scanf("%d%d",&v[i],&t);
		while(t)
		{
			d[i]+=p[t];
			scanf("%d",&t);
		}
	}
	for(int i=N;i;i--)
		for(int j=0;j<=p[K+1]-1;j++)
		{
			for(int k=1;k<=K;k++)
				if((d[k]&j)==d[k])
				   F[i][j]+=max(F[i+1][j],F[i+1][j|p[k]]+v[k]);
				else F[i][j]+=F[i+1][j];
			F[i][j]/=K;
		}
	printf("%.6lf",F[1][0]);
	return 0;
}
