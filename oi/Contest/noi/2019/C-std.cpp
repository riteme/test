#include <bits/stdc++.h>
#define N 200005
#define ll long long
#define getchar nc
using namespace std;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(register ll x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[20];register int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
int T,n,k,l,a[N],b[N],ar[N],br[N],va[N],vb[N],vis[N];
ll ans;
inline bool cmpa(register int x,register int y)
{
    return a[x]>a[y];
}
inline bool cmpb(register int x,register int y)
{
    return b[x]>b[y];
}
struct node{
    int pos,val;
    inline bool operator < (const node &it) const {
        return val<it.val;
    }
};
inline bool chkmax(register int &a,register int b)
{
    return a<b?a=b,1:0;
}
int main()
{
    T=read();
    while(T--)
    {
        n=read(),k=read(),l=read();
        for(register int i=1;i<=n;++i)
            a[i]=read(),ar[i]=i,va[i]=vb[i]=vis[i]=0;
        for(register int i=1;i<=n;++i)
            b[i]=read(),br[i]=i;
        sort(ar+1,ar+1+n,cmpa);
        sort(br+1,br+1+n,cmpb);
        for(register int i=1;i<=k;++i)
            va[ar[i]]=1,vb[br[i]]=1;
        ans=0;
        priority_queue<int> pa,pb;
        priority_queue<node> qa,qb;
        for(register int i=1;i<=n;++i)
            if(va[i]&&vb[i])
                qb.push((node){i,a[i]+b[i]}),vis[i]=1;
        if(qb.size()>=l)
        {
            for(register int i=1;i<=n;++i)
            {
                if(va[i])
                    ans+=a[i];
                if(vb[i])
                    ans+=b[i];
            }
        }
        else
        {
            for(register int i=1,tot=0;i<=k;++i)
                if(!vb[ar[i]])
                {
                    if(tot<k-l)
                        ans+=a[ar[i]],vis[ar[i]]=1,pa.push(b[ar[i]]);
                    else
                        qa.push((node){ar[i],a[ar[i]]+b[ar[i]]});
                    ++tot;
                }
            for(register int i=1,tot=0;i<=n;++i)
                if(!va[br[i]])
                {
                    if(tot<k-l)
                        ans+=b[br[i]],vis[br[i]]=1,pb.push(a[br[i]]);
                    else
                        qb.push((node){br[i],a[br[i]]+b[br[i]]});
                    ++tot;
                }
            int af=1,bf=1;
            while(l--)
            {
                while(af<=k&&vis[ar[af]])
                    ++af;
                while(bf<=k&&vis[br[bf]])
                    ++bf;
                while(!qa.empty()&&vis[qa.top().pos]&&!(va[qa.top().pos]&&vb[qa.top().pos]))
                    qa.pop();
                while(!qb.empty()&&vis[qb.top().pos]&&!(va[qb.top().pos]&&vb[qb.top().pos]))
                    qb.pop();
                int maxx=0,typ=-1;
                if(!qa.empty())
                    maxx=qa.top().val,typ=0;
                if(!qb.empty()&&chkmax(maxx,qb.top().val))
                    typ=1;
                if(!pa.empty()&&af<=k&&chkmax(maxx,pa.top()+a[ar[af]]))
                    typ=2;
                if(!pb.empty()&&bf<=k&&chkmax(maxx,pb.top()+b[br[bf]]))
                    typ=3;
                ans+=maxx;
                if(typ==0)
                    vis[qa.top().pos]=1,qa.pop();
                else if(typ==1)
                    vis[qb.top().pos]=1,qb.pop();
                else if(typ==2)
                    vis[ar[af]]=1,pa.pop(),pa.push(b[ar[af]]);
                else
                    vis[br[bf]]=1,pb.pop(),pb.push(a[br[bf]]);
            }
        }
        write(ans),puts("");
    }
    return 0;
}
