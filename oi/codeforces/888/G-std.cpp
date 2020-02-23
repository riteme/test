#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define LL long long 
#define LD long double
const int N=6000005;
int n,l[N],r[N],tot,ch[N][2],a[N],rt;
void insert(int &now,int i,int dep)
{
    if(!now)now=++tot;
    l[now]=min(l[now],i);
    r[now]=max(r[now],i);
    if(dep<0)return;
    bool d=(a[i]&(1<<dep));
    insert(ch[now][d],i,dep-1);
}
int query(int now,int val,int dep)
{
    if(dep<0)return 0;
    int V=(1<<dep);
    bool d=(val&V);
    if(ch[now][d])return query(ch[now][d],val,dep-1);
    return query(ch[now][!d],val,dep-1)+V;
}
LL ans=0;
void dfs(int now,int dep)
{
    if(!now)return;
    int sum=0x7fffffff;
    if(r[ch[now][1]])
        for(int i=l[ch[now][0]];i<=r[ch[now][0]];i++)
            sum=min(sum,query(ch[now][1],a[i],dep-1));
    if(sum!=0x7fffffff)ans+=sum+(1<<dep);
    dfs(ch[now][0],dep-1);
    dfs(ch[now][1],dep-1);
}
int main()
{
    memset(l,0x3f,sizeof(l));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        insert(rt,i,30);
    dfs(rt,30);
    cout<<ans<<endl;
    return 0;
}
