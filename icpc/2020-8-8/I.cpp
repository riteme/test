#include <bits/stdc++.h>
#define ll long long
#define vi vector <int>
#define pb push_back
#define mp make_pair
#define mod 998244353
#define rep(i,j,n) for(int i=j;i<=n;i++)
#pragma optimize(3)
using namespace std;
long long pmod(long long x,long long y)
{
    long long z=1;
    while(y)
    {
        if(y&1)
            z=z*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return z;
}

int T,n,x,y,z,m,k;
int C[61][61];
bool vis[70];
long long Ans[70][70];
int p[2][70][70];
bool t[70];
int fa[70];
vi u[70],f[70];
int l[70],r[70];
int op;
bool cloop(int s, int x,int p)
{
    vis[x]=1;
    fa[x] = s;
    for(int i = 0; i<f[x].size(); i++)
    {
        if(f[x][i] == p)
            continue;
        if(vis[f[x][i]])
            return 1;
        if(cloop(s,f[x][i],x))
            return 1;
        u[s].pb(f[x][i]);
    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m>>k;

    long long temp = 2;
    rep(i,0,60)
    {
        C[i][0]=C[i][i] = 1;
        rep(j,1,i-1)
        {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
            if(C[i][j]>=mod)
                C[i][j] -= mod;
        }
    }

    rep(i,1,m)
    {
        cin>>x>>y;
        bool pp=true;
        for(int j=0; j<f[x].size(); j++)
            if(f[x][j]==y)
            {
                pp=false;
                break;
            }
        if(pp)
            f[x].pb(y);
        pp=true;
        for(int j=0; j<f[y].size(); j++)
            if(f[y][j]==x)
            {
                pp=false;
                break;
            }
        if(pp)
            f[y].pb(x);
    }

    rep(i,1,n)
    l[i]=max((int)(f[i].size()),1), r[i]=n-1;
    rep(i,1,k)
    {
        cin>>op>>x>>y;
        if(op==1)
            r[x]=min(r[x],y);
        else
            l[x]=max(l[x],y);
    }

    rep(i,1,n)
    if(l[i]>r[i])
    {
        puts("0");
        return 0;
    }

    memset(vis,0,sizeof vis);
    rep(i,1,n)
    {
        if(!vis[i])
        {
            u[i].pb(i);
            if(cloop(i,i,0))
            {
                puts("0");
                return 0;
            }
        }
    }
    //puts("!!!");

    int N = n;
    rep(i,1,n)
    if(u[i].size()>0)
    {
        p[0][i][0] = 1;
        t[i] = 0;
        for(int j=0;j<u[i].size();j++)
        {
            int x = u[i][j];
            int temp = 0;
            for(int k=0;k<f[x].size();k++)
            {
                if(fa[f[x][k]] == i)
                    temp++;
            }
            l[x] -= temp;
            r[x] -= temp;
            //cout<<i<<' '<<x<<' '<<l[x]<<' '<<r[x]<<endl;
            t[i]^=1;
            for(int k=r[x];k>=l[x];k--)
            for(int nn=n;nn>=k;nn--)
                p[t[i]][i][nn] = (p[t[i]][i][nn] + 1ll*p[t[i]^1][i][nn-k]*C[nn][k]) % mod;
            memset(p[t[i]^1][i],0,sizeof p[t[i]^1][i]);
        }
    }
    else N--;
    if(N==1)
    {
        puts("1");
        return 0;
    }

    Ans[0][0] = 1;
    /*rep(v,1,n)
    {
        rep(j,1,N-1)
            cout<<p[t[v]][v][j]<<' ';
        cout<<endl;
    }*/
    rep(v,1,n)
    {
        if(u[v].size()==0)
        {
            rep(j,0,N-2)
                Ans[v][j]=Ans[v-1][j];
            continue;
        }
        for(int i=N-2;i>=0;i--)
        {
            for(int j=i;j>=0;j--)
                Ans[v][i] = (Ans[v][i] + Ans[v-1][i-j] * p[t[v]][v][j+1] % mod * C[N-2-i+j][j]) % mod;
        }
    }
    cout<<Ans[n][N-2]<<endl;
}
