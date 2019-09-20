#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize("Ofast","inline")
#pragma GCC optimize("-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;

const db pi=acos(-1), eps=1e-4;

struct Po{
  db x, y;
  db len(){ return sqrt(x*x+y*y); }
  db ang(){ return atan2(y,x); }
}st, en, tmp[10], pmt[10];
Po operator + (const Po a,const Po b){
  return (Po){a.x+b.x,a.y+b.y};
}
Po operator - (const Po a,const Po b){
  return (Po){a.x-b.x,a.y-b.y};
}
Po operator * (const Po a,const db k){
  return (Po){a.x*k,a.y*k};
}
Po relen(Po a,db aim){
  return a*(aim/a.len());
}
Po rot(const Po a,const Po b){
  return (Po){a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};
}
db xxx(const Po a,const Po b){
  return a.x*b.y-b.x*a.y;
}
db ddd(const Po a,const Po b){
  return a.x*b.x+a.y*b.y;
}
struct Ci{
  Po o; db r;
}c[555];
int n, cnt=2;

int PandC(Po p,Ci c,Po *res){
  int sz=0;
  Po v=p-c.o; db len=v.len();
  if (len<c.r-eps) return 0;
  v=relen(v,c.r);
  if (len<c.r+eps){
    res[++sz]=c.o+v;
  }else{
    db co=c.r/len, si=sqrt(1-co*co);
    res[++sz]=c.o+rot(v,(Po){co,si});
    res[++sz]=c.o+rot(v,(Po){co,-si});
  }
  return sz;
}

int CandC(Ci a,Ci b,Po *rea,Po *reb){
  int sz=0;
  static Po st[10]; static int tp;
  if (a.r>b.r) swap(a,b), swap(rea,reb);
  
  {
    if (b.r-a.r<eps){
      Po v=a.o-b.o; v=relen(v,a.r);
      for (int si=-1;si<=1;si+=2){
	Po mov=rot(v,(Po){0.,0.+si});
	++sz; rea[sz]=a.o+mov; reb[sz]=b.o+mov;
      }			 
    }else{
      b.r-=a.r;
      tp=PandC(a.o,b,st);
      for (int i=1;i<=tp;++i){
	Po mov=relen(st[i]-b.o,a.r);
	++sz; rea[sz]=a.o+mov; reb[sz]=st[i]+mov;
      }
      b.r+=a.r;
    }
  }
  {
    if (a.r+b.r<eps){
      
    }else{
      b.r+=a.r;
      tp=PandC(a.o,b,st);
      for (int i=1;i<=tp;++i){
	Po mov=relen(b.o-st[i],a.r);
	++sz; rea[sz]=a.o+mov; reb[sz]=st[i]+mov;
      }
      b.r-=a.r;
    }
  }
  return sz;
}

db fuck;
inline bool die(const Po &a,const Po &b,const Ci &c){
  if (abs((c.o.x-a.x)*(b.y-a.y)-(b.x-a.x)*(c.o.y-a.y))>fuck*c.r-eps) return 0;
  if (ddd(c.o-a,b-a)<0&&(c.o-a).len()>c.r-eps) return 0;
  if (ddd(c.o-b,a-b)<0&&(c.o-b).len()>c.r-eps) return 0;
  return 1;
}

bool chk(Po a,Po b){
  static int fl, id[555];
  if (!fl){
    fl=1;
    for (int i=1;i<=n;++i) id[i]=i;
    random_shuffle(id+1,id+n+1);
  }
  fuck=(a-b).len();
  if (fuck<eps) return 1;
  for (int i=1;i<=n;++i)
    if (die(a,b,c[id[i]]))
      return 0;
  return 1;
}

const int LIM=1001000;
#define pdi pair<db,int>
#define fi first
#define se second
vector<pdi>vec[555], G[LIM];
void AE(int u,int v,db w){
  //printf(" %d %d %.5lf\n",u,v,w);
  G[u].push_back((pdi){w,v});
  G[v].push_back((pdi){w,u});
}

db fix(db x){
  return min(fmod(10*pi+x,2*pi),fmod(10*pi-x,2*pi));
}

priority_queue<pdi,vector<pdi>,greater<pdi> >q;
db d[LIM]; bool used[LIM];
void Dj(){
  for (int i=1;i<=cnt;++i){
    d[i]=1e20; used[i]=0;
  }
  d[1]=0; q.push((pdi){0.,1});
  int x, y; db z;
  for (;!q.empty();){
    x=q.top().se; q.pop();
    if (used[x]) continue;
    used[x]=1;
    for (auto o:G[x]){
      y=o.se;
      if (used[y]) continue;
      z=d[x]+o.fi;
      if (z<d[y]){
	d[y]=z; q.push((pdi){z,y});
      }
    }
  }
}

int main(){
  cin>>st.x>>st.y>>en.x>>en.y;
  cin>>n;
  for (int i=1;i<=n;++i)
    cin>>c[i].o.x>>c[i].o.y>>c[i].r;
  for (int i=1;i<=n;++i){
    {
      int sz=PandC(st,c[i],tmp);
      for (int j=1;j<=sz;++j){
	if (!chk(st,tmp[j])) continue;
	vec[i].push_back((pdi){(tmp[j]-c[i].o).ang(),++cnt});
	AE(1,cnt,(tmp[j]-st).len());
      }
    }
    {
      int sz=PandC(en,c[i],tmp);
      for (int j=1;j<=sz;++j){
	if (!chk(en,tmp[j])) continue;
	vec[i].push_back((pdi){(tmp[j]-c[i].o).ang(),++cnt});
	AE(2,cnt,(tmp[j]-en).len());
      }
    }
  }
  if (chk(st,en)) return printf("%.1lf\n",(st-en).len()), 0;
  for (int i=1;i<n;++i)
    for (int j=i+1;j<=n;++j){
      int sz=CandC(c[i],c[j],tmp,pmt);
      for (int k=1;k<=sz;++k){
	Po a=tmp[k], b=pmt[k];
	if (!chk(a,b)) continue;
	vec[i].push_back((pdi){(a-c[i].o).ang(),++cnt});
	vec[j].push_back((pdi){(b-c[j].o).ang(),++cnt});
	AE(cnt-1,cnt,(a-b).len());
      }
    }
  for (int i=1;i<=n;++i){
    if (vec[i].size()<=1) continue;
    sort(vec[i].begin(),vec[i].end());
    for (int it=0;it<vec[i].size();++it){
      pdi u=vec[i][it], v=vec[i][(it+1)%vec[i].size()];
      AE(u.se,v.se,c[i].r*fix(u.fi-v.fi));
    }
  }
  Dj();
  printf("%.1lf\n",d[2]);
}
