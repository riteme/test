#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 111
#define inf 1<<30

struct Edge{
    int u,v;
    double w;
}edge[MAXN*MAXN];

struct Node {
    double x,y;
} node[MAXN];

int n,m;
double In[MAXN];
int pre[MAXN],visited[MAXN],ID[MAXN];
//root表示根结点，n是顶点树，m是边数
//最小树形图邻接表版本，三步走，找最小入弧，找有向环，缩环为点
double Directed_MST(int root,int n,int m)
{
    int u,v,i,ansi;
    double cnt=0;
    while(true) {
        //找最小入边
        for(i=0; i<n; i++)In[i]=inf;
        for(i=0; i<m; i++) {
            u=edge[i].u;
            v=edge[i].v;
            if(edge[i].w<In[v]&&u!=v) {
                pre[v]=u;//u->v;
                if(u==root)//记录是root从哪一条边到有效点的（这个点就是实际的起点）
                    ansi=i;
                In[v]=edge[i].w;
            }
        }
        for(i=0; i<n; i++) {
            if(i==root)continue;
            if(In[i]==inf)return -1;//说明存在点没有入边
        }
        //找环
        int cntcode=0;
        memset(visited,-1,sizeof(visited));
        memset(ID,-1,sizeof(ID));
        In[root]=0;
        //标记每一个环
        for(i=0; i<n; i++) {
            cnt+=In[i];
            v=i;
            while(visited[v]!=i&&ID[v]==-1&&v!=root) {
                visited[v]=i;
                v=pre[v];
            }
            //说明此时找到一个环
            if(v!=root&&ID[v]==-1) {
                //表示这是找到的第几个环，给找到的环的每个点标号
                for(u=pre[v]; u!=v; u=pre[u]) {
                    ID[u]=cntcode;
                }
                ID[v]=cntcode++;
            }
        }
        if(cntcode==0)break;//说明不存在环
        for(i=0; i<n; i++) {
            if(ID[i]==-1)
                ID[i]=cntcode++;
        }
        //缩点，重新标记
        for(i=0; i<m; i++) {
            int v=edge[i].v;
            edge[i].u=ID[edge[i].u];
            edge[i].v=ID[edge[i].v];
            //说明原先不在同一个环
            if(edge[i].u!=edge[i].v) {
                edge[i].w-=In[v];
            }
        }
        n=cntcode;
        root=ID[root];
    }
    return cnt;
}

double Get_dist(int i,int j)
{
    double d1=(node[i].x-node[j].x)*(node[i].x-node[j].x);
    double d2=(node[i].y-node[j].y)*(node[i].y-node[j].y);
    return sqrt(d1+d2);
}

int main()
{
    double ans;
    while(~scanf("%d%d",&n,&m)){
        for(int i=0;i<n;i++)scanf("%lf%lf",&node[i].x,&node[i].y);
        for(int i=0;i<m;i++){
            scanf("%d%d",&edge[i].u,&edge[i].v);
            edge[i].u--;
            edge[i].v--;
            if(edge[i].u!=edge[i].v)edge[i].w=Get_dist(edge[i].u,edge[i].v);
            else edge[i].w=inf;//消除自环
        }
        ans=Directed_MST(0,n,m);
        if(ans==-1){
            puts("poor snoopy");
        }else
            printf("%.2f\n",ans);
    }
    return 0;
}
