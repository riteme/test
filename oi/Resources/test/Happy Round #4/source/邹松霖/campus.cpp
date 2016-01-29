#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int map[2000][2000];
int ans[10000];
int max(int x,int y,int x1,int y1)
{
   if ((x>y)&&(x>x1)&&(x>y1))return x;
    if ((y>x)&&(y>x1)&&(y>y1))return y;
     if ((x1>y)&&(x1>x)&&(x1>y1))return x1;
     return y1;
}
int main()
{
    freopen("campus.in","r",stdin);
    freopen("campus.out","w",stdout);
    int pos=0;
	int n,m,a,b,w,i,j,k,ii;
    scanf("%d %d",&n,&m);
     for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
         map[i][j]=-900000;
	for(ii=1;ii<=n-1;ii++)
    {
    scanf("%d %d %d",&a,&b,&w);
    map[a][b]=w;
    map[b][a]=w;
    }
   k=1;
   
      for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
        {
        if (i!=j)
		map[i][j]=max(map[i][k]+map[k][j],map[i][k],map[k][j],map[i][j]);  
		
		}
 for(ii=1;ii<=m;ii++)
 {
  scanf("%d %d",&a,&b);
  ans[++pos]=map[a][b];
  
 }
    for(ii=1;ii<=pos;ii++)   
	 cout<<ans[ii]<<endl;
	 fclose(stdin);fclose(stdout);
}

