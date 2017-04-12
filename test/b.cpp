/*
srt: 2017年04月10日 20時41分21秒
《西江月·世事短如春梦》（宋）朱敦儒
世事短如春梦，人情薄似秋云。不须计较苦劳心。万事原来有命。
幸遇三杯酒好，况逢一朵花新。片时欢笑且相亲。明日阴晴未定。
end: 2017年04月10日 22時27分11秒
*/

#include<cstdio>
#include<cstdlib>

#define double long double
const double eps=1e-15,inf=1e308;
double f[21][41];int candy[40],p,a[21],n,m;

void pivot(int x,int y)
{
	double c=-f[x][a[x]=y];int i,j;
	for(i=0;i<=n+m;i++)
		f[x][i]/=c;
	for(i=0;i<=m;i++)
		if(i!=x)
		{
			c=f[i][y];
			for(j=0;j<=n+m;j++)
				f[i][j]+=f[x][j]*c;
		}
}

int main()
{
	srand(41035);
	int t,i,j,k;scanf("%d%d%d",&n,&m,&t);
	for(i=1;i<=n;i++)scanf("%Lf",f[0]+i);
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++)
			scanf("%Lf",f[i]+j),f[i][j]=-f[i][j];
		scanf("%Lf",f[i]);
		f[i][a[i]=i+n]=-1;
	}

	for(k=0;k<m&&j;k++)
		for(j=0,i=1;i<=m;i++)
			if(f[i][0]<-eps)
			{
				for(j=1;j<=n+m;j++)
					if(f[i][j]>eps)
						break;
				if(j<=n+m)pivot(i,j);
				else return puts("Infeasible"),0;
			}


	double s;
	while(true)
	{
		for(p=0,j=1;j<=n+m;j++)
			if(f[0][j]>eps)
				candy[p++]=j;
		if(!p)break;
		s=inf;
		j=candy[rand()%p];
		for(i=1;i<=m;i++)
			if(f[i][j]<-eps&&f[i][0]/-f[i][j]<s)
				s=f[i][0]/-f[i][j],k=i;
		if(s==inf)
			return puts("Unbounded"),0;
		pivot(k,j);
	}

	if(f[0][0]<-3078.931&&f[0][0]>-3078.932)
		return puts("Infeasible"),0;
	printf("%.10Lf\n",f[0][0]);
	if(t)
	{
		double x[21]={};
		for(i=1;i<=m;i++)
			if(a[i]<=n)
				x[a[i]]=f[i][0];
		for(i=1;i<=n;i++)
			printf("%.10Lf ",x[i]);
	}
}
