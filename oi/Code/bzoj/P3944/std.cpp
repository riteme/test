#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 5000000
using namespace std;
int n;
int prime[M/5],tot;
long long phi[M],mu[M];
bool not_prime[M];
map<int,long long> _phi,_mu;
void Linear_Shaker()
{
    long long i,j;
    phi[1]=1;mu[1]=1;
    for(i=2;i<M;i++)
    {
        if(!not_prime[i])
        {
            phi[i]=i-1;
            mu[i]=-1;
            prime[++tot]=i;
        }
        for(j=1;prime[j]*i<M;j++)
        {
            not_prime[prime[j]*i]=true;
            if(i%prime[j]==0)
            {
                phi[prime[j]*i]=phi[i]*prime[j];
                mu[prime[j]*i]=0;
                break;
            }
            phi[prime[j]*i]=phi[i]*(prime[j]-1);
            mu[prime[j]*i]=-mu[i];
        }
    }
    for(i=1;i<M;i++)
    {
        phi[i]+=phi[i-1];
        mu[i]+=mu[i-1];
    }
}
long long Calculate_Phi(long long n)
{
    map<int,long long>::iterator it;
    if(n<M)
        return phi[n];
    if((it=_phi.find(n))!=_phi.end())
        return it->second;
    long long i,last,re=(long long)n*(n+1)>>1;
    for(i=2;i<=n;i=last+1)
    {
        last=n/(n/i);
        re-=(last-i+1)*Calculate_Phi(n/i);
    }
    return _phi[n]=re;
}
long long Calculate_Mu(long long n)
{
    map<int,long long>::iterator it;
    if(n<M)
        return mu[n];
    if((it=_mu.find(n))!=_mu.end())
        return it->second;
    long long i,last,re=1;
    for(i=2;i<=n;i=last+1)
    {
        last=n/(n/i);
        re-=(last-i+1)*Calculate_Mu(n/i);
    }
    return _mu[n]=re;
}
int main()
{
    int T;
    Linear_Shaker();
    for(cin>>T;T;T--)
    {
        scanf("%d",&n);
        printf("%lld %lld\n",Calculate_Phi(n),Calculate_Mu(n));
    }
}
