#include<bits/stdc++.h>

using namespace std;

#define rep(i,j,n) for(int i=j;i<=n;i++)

long long n,uk;
int x,y;
long long p[61][2];
long long f(long long n,long long k)
{
    if(p[n][k==uk]) return p[n][k==uk];
    if(n==1)
    {
        if(k==2)
            return 1;
        if(k==-2)
            return 3;
        if(k==0)
            return 6;
        return 0;
    }
    if(k>=(1ll << n+1)) return 0;
    if(-k>=(1ll << n+1)) return 0;
    if(k>=(1ll<<n)) return p[n][k==uk] = f(n-1,k-(1<<n));
    if(-k>=(1ll<<n)) return p[n][k==uk] = f(n-1,k+(1<<n))+(1<<2*n-1)*((k+(1<<n+1))/2);
    return p[n][k==uk] = 2*f(n-1,k)+(k<0 ? f(n-1,k+(1<<n)) : f(n-1,k-(1<<n)))+ max((1ll<<n-1)-abs(k)/2, 0ll)*(1ll<<(2*n)) - (k<0 ? k/2 * (1ll<<(2*n - 1))  : 0) ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>uk;

    cout<<(uk%2==0 ? f(n,uk) : 0)<<endl;

}
