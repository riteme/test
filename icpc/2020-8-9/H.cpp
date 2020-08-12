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
const int N = 1000000;
int C[61][61];
bool vis[70];
long long Ans[70][70];
int p[2][70][70];
bool t[70];
int fa[70];
vi u[70],f[70];
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
}
char s[1010];
int l;

vector<vector<int> > ans;
int mx=0;
int a[12],b[12],v[4];
void ps2()
{
    vi s;
    rep(i,1,a[8])
    s.pb(8);
    rep(i,1,a[5])
    s.pb(5);
    rep(i,1,a[2])
    s.pb(2);
    if(s.size()>mx)
    {
        mx=s.size();
        ans.clear();
        ans.pb(s);
    }
    else if(s.size()==mx)
    {
        ans.pb(s);
    }
}

void ps1()
{
    vi s;
    rep(i,1,a[7])
    s.pb(7);
    rep(i,1,a[4])
    s.pb(4);
    rep(i,1,a[1])
    s.pb(1);
    if(s.size()>mx)
    {
        mx=s.size();
        ans.clear();
        ans.pb(s);
    }
    else if(s.size()==mx)
    {
        ans.pb(s);
    }
}

void ps0()
{
    vi s;
    rep(i,1,a[9])
    s.pb(9);
    rep(i,1,a[6])
    s.pb(6);
    rep(i,1,a[3])
    s.pb(3);
    if(s.size())
    {
        rep(i,1,a[0])
        s.pb(0);
    }
    else
        s.pb(0);
    if(s.size()>mx)
    {
        mx=s.size();
        ans.clear();
        ans.pb(s);
    }
    else if(s.size()==mx)
    {
        ans.pb(s);
    }
}

void ps3()
{
    vi s;
    rep(i,0,9)
    b[i]=0;
    bool con = true;
    int j=0;
    while(con)
    {
        con=false;
        for(int i=9; i>=0; i--)
            if(a[i]>b[i] && i%3 == v[j])
            {
                if(!s.size() && i==0)
                {
                    s.pb(0);
                    con = false;
                    break;
                }
                s.pb(i);
                b[i]++;
                j=(j+1)%3;
                con =true;
            }

    }

    if(s.size()>mx)
    {
        mx=s.size();
        ans.clear();
        ans.pb(s);
    }
    else if(s.size()==mx)
    {
        ans.pb(s);
    }

}

void solve()
{
    int u= 0;
    for(int i=1;i<ans.size();i++)
    {
        for(int j=0;j<mx;j++)
            if(ans[i][j]>ans[u][j])
        {
            u=i;
            break;
        }
        else if(ans[i][j]<ans[u][j]) break;
    }

    rep(i,0,mx-1)
        putchar(ans[u][i]+'0');
    putchar('\n');
}
int main()
{
    ios::sync_with_stdio(0);
    rep(i,0,9)
    cin>>a[i];
    ps0();
    ps1();
    ps2();
    v[0] = 0;
    v[1] = 1;
    v[2] = 2;
    ps3();
    v[0] = 0;
    v[1] = 2;
    v[2] = 1;
    ps3();
    v[0] = 1;
    v[1] = 0;
    v[2] = 2;
    ps3();
    v[0] = 2;
    v[1] = 0;
    v[2] = 1;
    ps3();
    v[0] = 2;
    v[1] = 1;
    v[2] = 0;
    ps3();
    v[0] = 1;
    v[1] = 2;
    v[2] = 0;
    ps3();

    solve();
}
