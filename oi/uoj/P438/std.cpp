// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;
int to[100005],Next[100005],last[50005],edge,dp[50005],w[100005],sum,ans,son[50005],tot,n,m,x,y,z,mx,ma=0,ff=1,ww[50005];
void add(int x,int y,int z){
    to[++edge]=y;
    Next[edge]=last[x];
    last[x]=edge;
    w[edge]=z;
}
void dfs1(int x,int fa){
    for (int i=last[x];i;i=Next[i])
    if (to[i]!=fa){
        dfs1(to[i],x);
        son[x]++;
    }
}
void dfs(int x,int fa,int s){
    int a[son[x]+5],f[son[x]+5],cnt=0;
    memset(f,0,sizeof(f));
    for (int i=last[x];i;i=Next[i])
    if (to[i]!=fa){
        dfs(to[i],x,s);
        a[++cnt]=dp[to[i]]+w[i];
    }
    a[0]=0;
    sort(a+1,a+cnt+1);
    int i=1,lasti=0,top=0,ss[cnt+5];
    while (cnt>0 ) if (a[cnt]>=s) tot++,f[cnt--]=1;else break;
    int j=cnt;
    for (int i=1;i<=cnt;i++)
    {
        if (f[i]) continue;
        while (top && ss[top]<=i) top--;
        while (a[i]+a[j]>=s && j>i) ss[++top]=j,j--;
        if (!top) continue;
        ++tot;
        f[ss[top--]]=1;f[i]=1;
    }
    dp[x]=0;
    for (int k=cnt;k;k--)
    if (!f[k]){
        dp[x]=a[k];
        break;
    }
}
void dfs2(int x,int fa,int d){
    if (d>ma) ma=d,mx=x;
    for (int i=last[x];i;i=Next[i])
        if (to[i]!=fa)
            dfs2(to[i],x,d+w[i]);
}
bool pf(int x){
    tot=0;
    dfs(1,0,x);
    if (tot>=m) return true;
    return false;
}
bool pf2(int x){
    int i=1,j=n-1,tot=0;
    while (ww[j]>=x) j--,tot++;
    while (i<j){
        while (ww[i]+ww[j]<x && i<j) i++;
        if (i<j && ww[i]+ww[j]>=x){
            tot++;
            i++;j--;
        }
    }
    if (tot>=m) return true;
    return false;
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++){
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
        if (x!=1 && y!=1) ff=0;
        sum+=z;
    }
    if (m==1){
        dfs2(1,0,0);
        dfs2(mx,0,0);
        printf("%d",ma);
    }else if (ff && n>1000){
        for (int i=1;i<n;i++) ww[i]=w[i*2];
        sort(ww+1,ww+n);
        int l=1,r=sum/m;
        while (l<=r){
            int mid=(l+r)>>1;
            if (pf2(mid)){
                l=mid+1;
                ans=mid;
            }else r=mid-1;
        }
        printf("%d",ans);
    }else{
        dfs1(1,0);
        int l=1,r=sum/m;
        while (l<=r){
            int mid=(l+r)>>1;
            if (pf(mid)){
                l=mid+1;
                ans=mid;
            }else r=mid-1;
        }
        printf("%d",ans);
    }
    return 0;
}
