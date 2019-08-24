
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define _(d) while(d((ch=getchar()-48)>=0))
inline int get(){
    char ch;_(!);int x=ch;
    _() x=(x<<3)+(x<<1)+ch;return x;
}
typedef long long ll;
const int N=1001,M=7,S=128,D=1e9+7;
int n,m,k,e[M],tt,lt,st[S],po[1<<(M<<1)];
int mt[S][M],sta[M+1];bool v1[N][M],v2[N][M];
int rs[N][M][S],gp[N][S],gi[N][S];
vector<int>ss[M],ma[S];
inline int get(int x,int y){
    return x>>(y<<1)&3;
}
inline void add(int &x,int y){
    if((x+=y)>=D) x-=D;
}
inline void set(int &x,int y,int v){
    y<<=1,x^=(x>>y&3^v)<<y;
}
void solve(bool (*v)[M]){
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            int *f=rs[i][j],*la=(j==1?rs[i-1][m]:rs[i][j-1]),s=0;
            memset(f+1,0,tt<<2);
            if(!v[i][j]) set(s,j-1,1),set(s,j,2),add(f[po[s]],1);
            for(int k=1,sa,va,s1,s2;k<=tt;++k){
                sa=st[k],va=la[k];
                if(j==1&&get(sa,m)||!va) continue;
                if(j==1) sa<<=2;
                s1=get(sa,j-1),s2=get(sa,j);
                if(!s1&&!s2) add(f[po[sa]],va);
                if(v[i][j]) continue;
                if(!s1&&!s2){
                    s=sa,set(s,j-1,1),set(s,j,2);
                    add(f[po[s]],va);
                }if(!s1&&s2){
                    s=sa,add(f[po[s]],va);
                    set(s,j-1,s2),set(s,j,0);
                    add(f[po[s]],va);
                }if(s1&&!s2){
                    s=sa,add(f[po[s]],va);
                    set(s,j-1,0),set(s,j,s1);
                    add(f[po[s]],va);
                }if(s1==1&&s2==1){
                    s=sa,set(s,j-1,0),set(s,j,0);
                    set(s,mt[k][j],1),add(f[po[s]],va);
                }if(s1==2&&s2==2){
                    s=sa,set(s,j-1,0),set(s,j,0);
                    set(s,mt[k][j-1],2),add(f[po[s]],va);
                }if(s1==2&&s2==1){
                    s=sa,set(s,j-1,0),set(s,j,0);
                    add(f[po[s]],va);
                }
            }
        }
}
 
int ca[M],cp[M],cv[M];
inline int find(int x){
    return cp[x]==x?x:cp[x]=find(cp[x]);
}
bool check(int i1,int i2){
    for(int i=0;i<m;++i) cp[i]=i;
    for(int i=0;i<m;++i){
        int v1=get(st[i1],i),v2=get(st[i2],i);
        if(bool(v1)!=bool(v2)) return 0;
        cv[i]=bool(v1);
        if(v1==1) cp[find(mt[i1][i])]=find(i);
        if(v2==1) cp[find(mt[i2][i])]=find(i);
    }int as=0;
    for(int i=0;i<m;++i)
        if(cv[i]) as+=cp[i]==i;
    return as==1;
}
void predeal(){
    for(int s=0,al=pow(3,m+1);s<al;++s){
        int u=0,a=0;
        for(int i=0,g=s;i<=m;++i){
            e[i]=g%3,g/=3,a|=e[i]<<(i<<1);
            u+=(e[i]==1)-(e[i]==2);
            if(u<0) break;
        }if(u) continue;++tt,lt+=s<al/3;
        st[tt]=a,po[a]=tt;
        for(int i=0;i<=m;++i){
            if(e[i]==1) sta[++u]=i;
            if(e[i]==2) mt[tt][sta[u]]=i,mt[tt][i]=sta[u--];
        }
    }solve(v1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=lt;++j)
            gp[i][j]=rs[i][m][j];
    solve(v2);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=lt;++j)
            gi[i][j]=rs[n-i+1][m][j];
    for(int i=1;i<=lt;++i){
        for(int j=1;j<=m;++j)
            if(get(st[i],j-1)) ss[j].push_back(i);
        for(int j=1;j<=lt;++j)
            if(check(i,j)) ma[i].push_back(j);
    }
}
int main(){
    n=get(),m=get(),k=get();
    for(int i=1,x,y;i<=k;++i){
        x=get(),y=get();
        v1[x][y]=v2[n-x+1][y]=1;
    }
    predeal();
    for(int Q=get(),x,y,as;Q--;){
        x=get(),y=get();as=0;
        for(int j=0,s=ss[y].size();j<s;++j)
            for(int cu=ss[y][j],k=0,s2=ma[cu].size();k<s2;++k)
                add(as,ll(gp[x][cu])*gi[x+1][ma[cu][k]]%D);
        printf("%d\n",as);
    }
    return 0;
}
