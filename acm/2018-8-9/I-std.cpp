#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
 
int n, D;
struct E{
  int to, id;
};
int cnt=1, an[2][404000];
vector<E>G[202000];
 
int die[202000], sz[202000];
void getsz(int x,int fff){
  sz[x]=1;
  for (auto o:G[x]){
    int y=o.to;
    if (y==fff||die[y]) continue;
    getsz(y,x); sz[x]+=sz[y];
  }
}
int getrt(int x,int fff,int totsz){
  for (auto o:G[x]){
    int y=o.to;
    if (y==fff||die[y]) continue;
    if (sz[y]*2>=totsz) return getrt(y,x,totsz);
  }
  return x;
}
 
int dep[202000], mxd[202000];
void getdp(int x,int fff){
  mxd[x]=dep[x];
  for (auto o:G[x]){
    int y=o.to;
    if (y==fff||die[y]) continue;
    dep[y]=dep[x]+1;
    getdp(y,x);
    mxd[x]=max(mxd[x],mxd[y]);
  }
}
int sum[202000], tmp[202000];
void ins(int x,int fff,int fl){
  if (x<=n) tmp[dep[x]]+=fl;
  for (auto o:G[x]){
    int y=o.to;
    if (y==fff||die[y]) continue;
    ins(y,x,fl);
  }
}
 
void realadd(int len){
  for (int i=len;i>=0;--i){
    sum[i]+=tmp[i]+=tmp[i+1];
  }
}
 
void gao(int id,int *sum,int d=D){
  if (d<0) return;
  an[0][id]+= sum[0]-sum[d];
  an[1][id]+= sum[d]-sum[d+1];
}
 
void dfs(int x,int fff,int id){
  gao(id,sum,D-dep[x]);
  for (auto o:G[x]){
    int y=o.to;
    if (y==fff||die[y]) continue;
    dfs(y,x,o.id^1);
  }
}
 
void doit(int x){
  //printf(" %d\n",x);
  die[x]=1;
  dep[x]=0; getdp(x,0);
  
  for (auto o:G[x]){
    int y=o.to;
    if (die[y]) continue;
    ins(y,x,1);
    realadd(mxd[y]);
    gao(o.id,tmp);
    memset(tmp,0,sizeof (int)*(mxd[y]+3));
  }
  if (x<=n) ++sum[0];
  //if (x==2){for (int i=0;i<=6;++i) printf(" %d",sum[i]); puts("");}
  for (auto o:G[x]){
    int y=o.to;
    if (die[y]) continue;
    ins(y,x,-1);
    realadd(mxd[y]);
    memset(tmp,0,sizeof (int)*(mxd[y]+3));
    dfs(y,x,o.id^1);
    if (die[y]) continue;
    ins(y,x,1);
    realadd(mxd[y]);
    memset(tmp,0,sizeof (int)*(mxd[y]+3));
  }
  
  memset(sum,0,sizeof (int)*(mxd[x]+3));
  
  for (auto o:G[x]){
    int y=o.to;
    if (die[y]) continue;
    getsz(y,x);
    doit(getrt(y,x,sz[y]));
  }
}
 
ll ans;
int pw[202000];
 
ll F(int x){
  if (x<2) return 0;
  return pw[x]-1-x;
}
 
int main(){
  // freopen("in.cpp","r",stdin);
  cin>>n;
  int u, v;
  for (int i=1;i<n;++i){
    scanf("%d%d",&u,&v);
    G[u].push_back((E){v,++cnt}); G[v].push_back((E){u,++cnt});
  }
  cin>>D;
  int fl=D&1; D=D+1>>1;
  getsz(1,0);
  doit(getrt(1,0,sz[1]));
  
  //cerr<<fl<<endl;
  
  pw[0]=1;
  for (int i=1;i<n*2;++i) pw[i]=pw[i-1]*2%mod;
  if (!fl){
    for (int x=1;x<=n;++x){
      int s0=x<=n, s1=0;
      for (auto o:G[x]){
        s0+= an[0][o.id];
        s1+= an[1][o.id];
      }
      if (s1<2) continue;
      ll res= F(s1);
      for (auto o:G[x]){
        int x= an[1][o.id];
        if (x<2) continue;
        res-= F(x);
      }
      ans+=res%mod *pw[s0]%mod;
    }
  }else{
    for (int i=1;i<n;++i){
      int a=i<<1|0, b=i<<1|1;
      int s0= an[0][a]+an[0][b];
      int s1= an[1][a]+an[1][b];
      if (s1<2) continue;
      ll res= F(s1)-F(an[1][a])-F(an[1][b]);
      ans+= res%mod *pw[s0]%mod;
    }
  }
  
  if (0){
    for (int x=1;x<n*2;++x){
      printf("%d ::",x);
      for (auto o:G[x]){
        printf(" %d[%d](%d,%d)",o.to,o.id,an[0][o.id],an[1][o.id]);
      }
      puts("");
    }
  }
  ans=(ans%mod+mod)%mod;
  cout<<ans<<endl;
}
