#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,x,y) for (int i=x; i<=y; ++i)
#define repd(i,x,y) for (int i=x; i>=y; --i)
#define mid ((l+r)>>1)
#define lson l,mid,t<<1
#define rson mid+1,r,t<<1|1

using namespace std;

int get()
{
    char c;
    while (!isdigit(c=getchar()));
    int k=c-'0';
    for (; isdigit(c=getchar()); k=k*10+c-'0');
    return k;
}

const int N=1e5+10,P=998244353,T=1<<18|1;
int n,m,inv[N],tr[T],ans[N];
bool flag[N];
struct ques
{
    int id,op,l,r;
    bool operator<(const ques &t) const
    {
        return id<t.id;
    }
} q[N];

bool le_l(const ques &a,const ques &b)
{
    return a.l<b.l || (a.l==b.l && a.op<b.op);
}

bool le_r(const ques &a,const ques &b)
{
    return a.r<b.r || (a.r==b.r && a.op<b.op);
}

void ins(int &p,int q)
{
    ~p? 0:p=0,p=(p*(1ll-q+P)+(1ll-p+P)*q)%P;
}

void clear(int l=1,int r=n,int t=1)
{
    if (tr[t]==-1)
        return;
    tr[t]=-1;
    if (l<r)
        clear(lson),clear(rson);
}

void modify(int p,int c,int l=1,int r=n,int t=1)
{
    ins(tr[t],c);
    if (l<r)
        p<=mid? modify(p,c,lson):modify(p,c,rson);
}

int query(int ql,int qr,int l=1,int r=n,int t=1)
{
    if (tr[t]==-1)
        return 0;
    if (ql<=l && r<=qr)
        return tr[t];
    int k=0;
    if (ql<=mid)
        ins(k,query(ql,qr,lson));
    if (mid<qr)
        ins(k,query(ql,qr,rson));
    return k;
}

void solve1(int l,int r)
{
    if (l==r)
        return;
    solve1(l,mid);
    solve1(mid+1,r);
    inplace_merge(q+l,q+mid+1,q+r+1,le_l);
    clear();
    rep(i,l,r)
        if (q[i].id<=mid && q[i].op)
            modify(q[i].r,q[i].op);
        else if (q[i].id>mid && !q[i].op && q[i].l>1)
            ins(ans[q[i].id],query(q[i].l-1,q[i].r-1));
    clear();
    rep(i,l,r)
        if (q[i].id<=mid && q[i].op)
            modify(q[i].r,(q[i].op<<1)%P);
        else if (q[i].id>mid && !q[i].op && q[i].l>1)
            ins(ans[q[i].id],query(q[i].r,n));
}

void solve2(int l,int r)
{
    if (l==r)
        return;
    solve2(l,mid);
    solve2(mid+1,r);
    inplace_merge(q+l,q+mid+1,q+r+1,le_r);
    clear();
    repd(i,r,l)
        if (q[i].id<=mid && q[i].op)
            modify(q[i].l,q[i].op);
        else if (q[i].id>mid && !q[i].op)
            ins(ans[q[i].id],query(q[i].l,q[i].r));
}

int main()
{
    n=get(),m=get();
    inv[1]=1;
    rep(i,2,n)
        inv[i]=(P-P/i)*1ll*inv[P%i]%P;
    rep(i,1,m)
    {
        q[i].id=i,q[i].op=get(),q[i].l=get(),q[i].r=get();
        if (q[i].op>1)
            ans[i]=1,q[i].op=0,flag[i]=q[i].l==1;
        else
            ans[i]=-1,q[i].op=inv[q[i].r-q[i].l+1];
    }
    solve1(1,m);
    sort(q+1,q+1+m);
    solve2(1,m);
    int cnt=0;
    rep(i,1,m)
        if (~ans[i])
            printf("%d\n",flag[i] && cnt? (1-ans[i]+P)%P:ans[i]);
        else
            cnt^=1;
    return 0;
}