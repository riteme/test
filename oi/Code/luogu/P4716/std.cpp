#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
template<typename T>inline void read(T &x)
{
    T f=1;x=0;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c^48);
    x*=f;
}

inline void write(int u,char ed='\n')
{
    if(!u){putchar(48);putchar(ed);return;}
    static int sta[43],tp;
    for(tp=0;u;u/=10)sta[++tp]=u%10;
    for(;tp;putchar(sta[tp--]^48));
    putchar(ed);
}

using namespace std;

const int MAXN=111,MAXM=1e4+7;

static int n,m,rt;

static struct edge
{
    int u,v,w;
}p[MAXM];

inline void init()
{
    read(n);read(m);read(rt);
    Rep(i,1,m)read(p[i].u),read(p[i].v),read(p[i].w);
}

static int in[MAXN],pre[MAXN],vis[MAXN],id[MAXN];

const int inf=0x3f3f3f3f;

inline long long getans()
{
    static long long ans=0;
    static int cnt=0,u,v,laz;
    while(1)
    {
        Rep(i,1,n)in[i]=inf,id[i]=vis[i]=0;
        Rep(i,1,m)if(p[i].u^p[i].v&&p[i].w<in[p[i].v])
            pre[p[i].v]=p[i].u,in[p[i].v]=p[i].w;
        in[rt]=0;
        Rep(i,1,n)
        {
            if(in[i]==inf)return -1;
            ans+=in[i];
            for(u=i;u^rt&&vis[u]^i&&!id[u];u=pre[u])vis[u]=i;
            if(u^rt&&!id[u])
            {
                id[u]=++cnt;
                for(v=pre[u];v^u;v=pre[v])id[v]=cnt;
            }
        }
        if(!cnt)return ans;
        Rep(i,1,n)if(!id[i])id[i]=++cnt;
        Rep(i,1,m)
        {
            laz=in[p[i].v];
            if((p[i].u=id[p[i].u])^(p[i].v=id[p[i].v]))
                p[i].w-=laz;
        }
        n=cnt;rt=id[rt];cnt=0;
    }
}

inline void solve(){printf("%lld\n",getans());}

int main()
{
    init();
    solve();
    return 0;
}
