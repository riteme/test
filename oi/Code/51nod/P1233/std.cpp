#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=1e6+5,mo=1e9+7;

typedef long long LL;

int n,m,k,Fac[N],Inv[N],Fac_Inv[N],ans,mu[N],tot,pr[N],g[N];

bool bz[N];

bool init()
{
    mu[1]=1;
    for (int i=2;i<=n+1;i++)
    {
        if (!bz[i])
        {
            pr[tot++]=i; mu[i]=-1;
        }
        for (int j=0;j<tot;j++)
        {
            int I=i*pr[j];
            if (I>n+1) break;
            bz[I]=1;
            if (i%pr[j]==0)
            {
                mu[I]=0;
                break;
            }
            mu[I]=-mu[i];
        }
    }
    Fac[0]=Inv[1]=Fac[1]=Fac_Inv[1]=Fac_Inv[0]=1;
    for (int i=2;i<=n+1;i++)
    {
        Fac[i]=(LL)Fac[i-1]*i%mo;
        Inv[i]=(LL)Inv[mo%i]*(mo-mo/i)%mo;
        Fac_Inv[i]=(LL)Fac_Inv[i-1]*Inv[i]%mo;
    }
}

int C(int n,int m)
{
    return (LL)Fac[n]*Fac_Inv[m]%mo*Fac_Inv[n-m]%mo;
}

int calc(int n,int m)
{
    if (n+1<k) return 0;
    ans=0;
    n++; m++;
    for (int i=1;i<=m;i++)
    {
        int t1=((LL)(n/i-1)*(n/i)%mo*Inv[2]%mo*i+(LL)(n%i)*(n/i))%mo,t2=((LL)(m/i-1)*(m/i)%mo*Inv[2]%mo*i+(LL)(m%i)*(m/i))%mo;
        g[i]=(LL)t1*t2%mo;
    }
    for (int i=k-1;i<=m;i++)
    {
        int t=0;
        for (int j=1;j*i<=m;j++)
        {
            if (mu[j]>0) t=(t+g[i*j])%mo;
            else if (mu[j]<0) t=(t-g[i*j]+mo)%mo;
        }
        ans=(ans+(LL)t*C(i-1,k-2))%mo;
    }
    ans=(ans+ans)%mo;
    ans=(ans+(LL)m*C(n,k))%mo;
    if (m>=k) ans=(ans+(LL)n*C(m,k))%mo;
    return ans;
}

int main()
{
    scanf("%d%d%d",&m,&n,&k);
    if (m>n) n^=m^=n^=m;
    init();
    printf("%d\n",(calc(n,m)-calc(n-2,m-2)+mo)%mo);
    return 0;
}
