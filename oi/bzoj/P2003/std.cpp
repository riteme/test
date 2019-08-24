#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
   
#define N 210
#define f(a) a[0][0]
   
int n,m,p;
int c[N][N],v[N][N],a[N][N],l[N][N],r[N][N];
   
int check(int x)
{
    return (x&1) ? -1 : 1;
}
   
int dfs(int d)
{
    if (d>=m)
        return true;
    for (int k=0;k<p;k++)
    {
        bool res(true);
        a[0][d]=k;
        for (int i=1;i<n;i++)
        {
            int r1=(c[i][d]+f(a)*check(i+d+1)+a[0][d]*check(i))*(-check(d));
            int r2=(c[i][d]+f(a)*check(i+d+1)+a[0][d]*check(i)-(p-1))*(-check(d));
            if (r1>r2)
                swap(r1,r2);
            l[d][i]=max(l[d-1][i],r1);
            r[d][i]=min(r[d-1][i],r2);
            if (l[d][i]>r[d][i])
            {
                res=false;
                break;
            }
        }
        if (res)
            if (dfs(d+1))
                return 1;
    }
    return 0;
}
   
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
        {
            scanf("%d",&v[i][j]);
            r[j][i]=p-1;
        }
    for (int i=1;i<n;i++)
        for (int j=1;j<m;j++)
            c[i][j]=v[i][j]-(c[i-1][j]+c[i][j-1]+c[i-1][j-1]);
    for (int ii=0;ii<p;ii++)
    {
        f(a)=ii;
        if (dfs(1))
        {
            for (int i=1;i<n;i++)
                a[i][0]=l[m-1][i];
            for (int j=1;j<n;j++)
                for (int k=1;k<m;k++)
                    a[j][k]=c[j][k]+check(k)*a[j][0]+check(j)*a[0][k]+check(j+k+1)*f(a);
            break;
        }
    }
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            printf("%d%s",a[i][j],j+1==m?"\n":" ");
    return 0;
}
