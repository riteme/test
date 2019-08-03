#include<unordered_map>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<iostream>
 
#define nn 2010
#define A 23333
#define C 998244353
#define Mod 1000000007
using namespace std;
 
int n,m,q,tot,l[nn],as;
struct Edge{int to,old;}e[nn*2];
inline void Lnk(int x,int y) {e[++tot].to=y,e[tot].old=l[x],l[x]=tot;}
 
 
unordered_map<int,int>::iterator i1,i2;
unordered_map<int,int> f[nn][13],v,g[13];
 
inline void Dfs(int x,int y){
    f[x][1][A]=1;
//    printf("%d\n",f[x][1][A]);
    for (int i=l[x];i;i=e[i].old)if(e[i].to!=y){
        int v=e[i].to;
        Dfs(v,x);
         
        for (int j=12;j>=2;j--)
        for (int k=1;k<j;k++){
            for (i1=f[v][k].begin();i1!=f[v][k].end();i1++)
            for (i2=f[x][j-k].begin();i2!=f[x][j-k].end();i2++){
                int h1=(*i1).first,h2=(*i2).first;
                int f1=(*i1).second,f2=(*i2).second;
                int h=h2*1ll*(h1^C)%Mod;
                if (!f[x][j][h]) f[x][j][h]=0;
                f[x][j][h]=(f[x][j][h]+f1*1ll*f2%Mod)%Mod;
            }
        }
    }
}
 
inline int Get(int x,int y){
    int rs=A;
    for (int i=l[x];i;i=e[i].old)if(e[i].to!=y){
        rs=rs*1ll*(Get(e[i].to,x)^C)%Mod;
    }
    return(rs);
}
 
int main()
{
//    freopen("1.in","r",stdin);
//    printf("%d\n",clock());
 
    scanf("%d",&n);
    for (int i=1;i<n;i++){
        int x,y;scanf("%d%d",&x,&y);
        Lnk(x,y),Lnk(y,x);
    }
    Dfs(1,0);
/*
    for (int i=1;i<=n;i++){
        printf("%d:\n",i);
        for (int j=1;j<=4;j++){
            printf("%d: ",j);
            for (i1=f[i][j].begin();i1!=f[i][j].end();i1++)
                printf("%d %d   ",(*i1).first,(*i1).second);
            puts("");
        }
        puts("");
    }
*/
    for (int i=1;i<=12;i++)
    for (int j=1;j<=n;j++)
    for (i1=f[j][i].begin();i1!=f[j][i].end();i1++)
        g[i][(*i1).first]=(g[i][(*i1).first]+(*i1).second)%Mod;
 
    scanf("%d",&q);
    for (int i=1;i<=q;i++){
        scanf("%d",&m);
        memset(l,0,4*(m+1)),tot=0;
        for (int i=1;i<m;i++){
            int x,y;scanf("%d%d",&x,&y);
            Lnk(x,y),Lnk(y,x);
        }
        v.clear();
        as=0;
        for (int i=1;i<=m;i++){
            int h=Get(i,0);
            if (!v[h]){
                v[h]=1;
                as=(as+g[m][h])%Mod;
            }
        }
        printf("%d\n",as);
    }
 
//    printf("%d\n",clock());
}
