#include <bits/stdc++.h>
#define vi vector <int>
#define pb push_back
#define rep(i,j,n) for(int i=j;i<=n;i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
#pragma optimize(3)
using namespace std;

typedef long double ld;
typedef long long ll;
ll qmul(ll a,ll b,ll m)
{
    a%=m;
    b%=m;
    ll r = a*b, s=ld(a) * b /m;

    return ((r-m*s)%m+m)%m;
}

ll qpow(ll x,ll y,ll m)
{
    ll z=1;
    x%=m;
    while(y)
    {
        if(y&1)
            z=qmul(z,x,m);
        x = qmul(x,x,m);
        y >>=1;
    }
    return z;
}

bool miller_rabin(ll n,ll base)
{
    ll n2 = n - 1, s=0;
    while(n2%2 == 0)
        n2>>=1, s++;
    ll t = qpow(base,n2,n);
    if(t == 1 || t == n-1)
        return true;
    for(s--; s>=0; s--)
    {
        if((t = qmul(t,t,n)) == n-1)
            return true;
    }
    return false;
}

int num = 0, mp2;
long long sum = 0;
ll mod;
int mp[2000];
bool prime[2501];
int p[2200];
bool is_prime(ll n)
{
    if(n<2500 && prime[n]) return 1;
    rep(i,1,p[0])
    {
        if(n%p[i] == 0) return 0;
    }

    return 1;
}

ll f(ll x,ll m)
{
    return (qmul(x,x,m)+1)%m;
}
ll rho(ll n)
{
    /*if(is_prime(n))
        return n;*/
    if(n%2 == 0)
        return 2;
    for(int i = 1;; i++)
    {
        ll x=i, y=f(x,n), p =__gcd(y-x,n);
        while(p == 1)
        {
            x=f(x,n);
            y=f(f(y,n),n);
            p=__gcd((y-x+n) % n,n)%n;
        }
        if(p!=0 && p!=n)
            return p;
    }
}
void prew()
{
    memset(prime,1,sizeof prime);
    rep(i,2,2500)
    {
        for(int j=2;j*j<=i;j++)
        {
            if(i%j==0)
            {
                prime[i]=0;
                break;
            }
        }
        if(prime[i]) p[++p[0]]=i;
    }

}

void find(long long n)
{
    rep(i,1,p[0])
    {
        while(n%p[i]==0)
        {
            num++;
            sum+=p[i];
            if(sum>2500) return;
            mp[i]++;
            n/=p[i];
        }
    }
    if(n>1) sum=2501;
}
int T;
long long n,m,k;
bool v[100000000];
int main()
{
    ios::sync_with_stdio(0);
    prew();
    cin>>mod;
    cin>>T;
    while(T--)
    {
        cin>>n;
        mp2=0;
        int mp3=0;
        bool pp =false;
        ll n0=n;
        ll mod3=(mod%3==2 ? (mod+1)/3 : (2*mod+1)/3);
        while(!pp)
        {
            ll nn=n;
            rep(k,1,8)
            {
                sum = 2*mp2+3*mp3,num = mp2+mp3;
                memset(mp,0,sizeof mp);
                find(nn);
                if(sum<=2500)
                {
                    pp=true;
                    break;
                }
                nn = n+mod*k;
            }
            if(pp) break;
            if(mp2==200)
            {
                n0=qmul(n0,mod3,mod);
                n=n0;
                mp3++;
                mp2=0;
            }
            else
            {
                n=qmul(n,(mod+1)/2,mod);
                mp2++;
            }
        }
            cout<<num<<' ';
        rep(i,1,mp2)
            cout<<2<<(i==num?'\n':' ');
        num-=mp2;
        rep(i,1,mp3)
            cout<<3<<(i==num?'\n':' ');
        num-=mp3;
        rep(i,1,2500)
        {
            while(mp[i])
                {cout<<p[i]<<(num==1?'\n':' ');mp[i]--;num--;}
            if(!num) break;
        }
    }
}
