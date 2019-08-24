#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=1;i<=n;++i)
#define mp make_pair
#define pb push_back
#define x0 gtmsub
#define y0 gtmshb
#define x1 gtmjtjl
#define y1 gtmsf
#define SUMLEN 42
const int N=3000;
const int MOD=998244353;
namespace AC{
struct Node {
    int next[26];
    int terminal,fail;
}node[SUMLEN];
bool legal[SUMLEN];
int top; //初始化:
int newnode() {
    top++;
    for(int i=0;i<26;i++)node[top].next[i]=0;
    node[top].terminal=node[top].fail=0;
    return top;
}
void add(char *st,int ti) {
    int len=strlen(st),x=1;
    for(int i=0;i<len;i++) {
        int ind=st[i]-'a';
        if (!node[x].next[ind])
            node[x].next[ind]=newnode();
        x=node[x].next[ind];
    }
    node[x].terminal|=1;
}
int q[SUMLEN],head,tail;
int trans[SUMLEN][26];
void build() {
    head=0,tail=1; q[1]=1;
    while (head!=tail) {
        int x=q[++head];
        node[x].terminal|=node[node[x].fail].terminal; //根据具体情况
        for(int i=0;i<26;i++)
            if (node[x].next[i]) {
                if (x==1)node[node[x].next[i]].fail=1;
                else {
                    int y=node[x].fail;
                    while (y) {
                        if (node[y].next[i]) {
                            node[node[x].next[i]].fail=node[y].next[i];
                            break;
                        }
                        y=node[y].fail;
                    }
                    if (!node[node[x].next[i]].fail)node[node[x].next[i]].fail=1;
                }
                q[++tail]=node[x].next[i];
            }
    }
    for(int i=1;i<=top;i++)if(node[i].terminal)legal[i]=1;
    for(int i=1;i<=top;i++)
        for(int j=0;j<26;j++){
            int now=i;
            while (now!=0 && node[now].next[j]==0)now=node[now].fail;
            if (now!=0)now=node[now].next[j]; else now=1;
            trans[i][j]=now;
        }
}
};
int tmp[45],M;
struct Matrix
{
    int a[45][45];
    friend Matrix operator*(const Matrix&a,const Matrix&b)
    {
        Matrix c;rep(i,M)rep(j,M)c.a[i][j]=0;
        rep(i,M)rep(k,M)rep(j,M)c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%MOD;
        return c;
    }
    void update(const Matrix&_a)
    {
        rep(i,M)tmp[i]=0;//_a.print();
        rep(i,M)rep(j,M)tmp[j]=(tmp[j]+1ll*a[1][i]*_a.a[i][j])%MOD;
        rep(i,M)a[1][i]=tmp[i];
    }
    void print() const {rep(i,M)rep(j,M)printf("%d%c",a[i][j]," \n"[j==M]);puts("");}
}a[N],f[N],rf[N],ans,tree[2][N<<2];
int fuck[N];
struct EDGE { int adj, next; string s;} edge[N*2];
int n, m, top, id[N],dfn[N],gh[N], c[N], deep[N], father[N], size[N], son[N], Top[N];
void addedge(int x, int y, string s) {
    edge[++top].adj = y;
    edge[top].next = gh[x];
    edge[top].s=s;
    gh[x] = top;
}
void dfs(int x, int root=0) {
    father[x] = root; deep[x] = deep[root] + 1;
    son[x] = 0; size[x] = 1; int dd = 0;
    for (int p=gh[x]; p; p=edge[p].next)
        if (edge[p].adj != root) {
            dfs(edge[p].adj, x);
             
            for(int i=1;i<=AC::top;i++)
                for(auto c:edge[p].s)
                {
                    if (AC::legal[i])a[edge[p].adj].a[i][i]++;
                    else a[edge[p].adj].a[i][AC::trans[i][c-'a']]++;
                }
            if (size[edge[p].adj] > dd) {
                son[x] = edge[p].adj;
                dd = size[edge[p].adj];
            }
            size[x] += size[edge[p].adj];
        }
}
void split(int x, int tp) {
    Top[x] = tp;dfn[x]=++top;id[top]=x;
    if (son[x]) split(son[x], tp);
    for (int p=gh[x]; p; p=edge[p].next)
        if (edge[p].adj != father[x] && edge[p].adj != son[x])
            split(edge[p].adj, edge[p].adj);
}
void build(int p,int le,int ri)
{
    if(le==ri){tree[0][p]=tree[1][p]=a[id[le]];return;}
    int mid=(le+ri)>>1;
    build(p<<1,le,mid);
    build(p<<1|1,mid+1,ri);
    tree[0][p]=tree[0][p<<1]*tree[0][p<<1|1];
    tree[1][p]=tree[1][p<<1|1]*tree[1][p<<1];
}
void work(int p,int le,int ri,int ll,int rr,Matrix&ans,int tag)
{
    if(ll<=le&&ri<=rr){ans.update(tree[tag^1][p]);return;}
    int mid=(le+ri)>>1;
    if(tag==1)
    {
        if(ll<=mid)work(p<<1,le,mid,ll,rr,ans,tag);
        if(rr>mid)work(p<<1|1,mid+1,ri,ll,rr,ans,tag);
    }
    else
    {
        if(rr>mid)work(p<<1|1,mid+1,ri,ll,rr,ans,tag);
        if(ll<=mid)work(p<<1,le,mid,ll,rr,ans,tag);
    }
}
int lca(int x, int y,Matrix&ans) {
    int tx = Top[x], ty = Top[y],tag=0,cnt=0;
    while (tx != ty) {
        if (deep[tx] < deep[ty]) {
            swap(tx, ty);
            swap(x, y);
            tag^=1;
        }
        if(tag==0)ans.update(rf[x]);
        else fuck[++cnt]=x;
        //printf("%d %d\n",x,Top[x]);
        x = father[tx];
        tx = Top[x];
    }
    if (deep[x] < deep[y]) swap(x, y),tag^=1;
    if(x!=y)work(1,1,n,dfn[y]+1,dfn[x],ans,tag);
    for(int i=cnt;i;i--)ans.update(f[fuck[i]]);
    return y;
}
int q;
int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<n;i++)
    {
        int x,y;
        char s[50];
        scanf("%d%d%s",&x,&y,s);
        string ss="";
        for(int i=0;i<strlen(s);i++)ss+=s[i];
        addedge(x,y,ss);
        addedge(y,x,ss);
    }
    AC::top=-1; AC::newnode(); AC::newnode();
    for(int i=1;i<=m;i++)
    {
        char s[50]; scanf("%s",s);
        AC::add(s,i);
    }
    AC::build();
     
    top=0; dfs(1); split(1,1);
    M=AC::top;
    rep(i,M)a[1].a[i][i]=1;
    rep(i,n)if(Top[id[i]]==id[i])f[id[i]]=rf[id[i]]=a[id[i]];else f[id[i]]=f[id[i-1]]*a[id[i]],rf[id[i]]=a[id[i]]*rf[id[i-1]];
    build(1,1,n);
    //rep(i,n)a[i].print();
    //a[3].print();
    //f[5].print();
    //rep(j,M)printf("%d%c",AC::legal[j]," \n"[j==M]);
    //Matrix tmp;memset(tmp.a,0,sizeof(tmp));
    //tmp=a[3]*a[2]*a[5];
    //puts("FUCK");tmp.print();
    rep(i,q)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        memset(ans.a,0,sizeof(ans.a));
        ans.a[1][1]=1;
        lca(x,y,ans);
        //rep(j,M)printf("%d%c",ans.a[1][j]," \n"[j==M]);
        int ANS=0;
        rep(j,M)if(AC::legal[j])ANS=(ANS+ans.a[1][j])%MOD;
        printf("%d\n",ANS);
    }
    return 0;
}
