#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int p=997;
ll qmul(ll a,ll b){
    ll ans=1;
    for(;b;b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
    return ans;
}
ll inv[70],xp[1005];
ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
ll ans,l[70],tot,m,n;
ll delta(ll x){
	ll ans=0;
	for(int i=1;i<=tot;i++)
	ans+=gcd(x,l[i]);
	return ans+=x/2;
}
void dfs(int last,int k,int n,ll s,ll f){
    int t=s*inv[n]%p;
    if(n==last)t=t*inv[k+1]%p;
    ans=(ans+t*xp[(f+delta(n))%(p-1)]%p)%p;
    for(int j=last;j<=n-j;j++){
    	ll tmp=delta(j);
        l[++tot]=j;
        int t=s*inv[j]%p;
        if(j==last)dfs(j,k+1,n-j,t*inv[k+1]%p,f+tmp);
        else dfs(j,1,n-j,t*inv[1]%p,f+tmp);
        tot--;
    }
}
int main(){
    //freopen("a.in","r",stdin);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)inv[i]=qmul(i,p-2);
    xp[0]=1;
    for(int i=1;i<=p;i++)xp[i]=(xp[i-1]<<1)%p;
    ll s=1;
    for(int i=1;i<=n;i++)s=s*i%p;
    dfs(1,0,n,s,0);
    for(int i=1;i<=n;i++)ans=ans*inv[i]%p;
    printf("%lld\n",ans);
    return 0;
}
