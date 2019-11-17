#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define M 100010
#pragma comment(linker, "/STACK:16777216")
struct node{
    int v,next;
}edge[M*2];
int head[M],tot;
void insert(int u,int v){
    edge[tot].v=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}
int n;
long long ans;
int dfs(int u,int pre){
    int son,tmp=0,i,v;
    for(i=head[u];i!=-1;i=edge[i].next){
        v=edge[i].v;
        if(v==pre) continue;
        son=dfs(v,u);
        tmp+=son;
        ans+=(long long)(n-tmp-1)*son;
    }
    return tmp+1;
}
int main(){
    int u,v,i;
    while(scanf("%d",&n)!=EOF){
        tot=0;
        ans=0;
        memset(head,-1,sizeof(head));
        for(i=1;i<n;i++){
            scanf("%d%d",&u,&v);
            insert(u,v);
            insert(v,u);
        }
        dfs(1,-1);
        long long sum=1ll*n*(n-1)*(n-2)/6;
        printf("%lld\n",sum-ans);
    }
    return 0;
}
