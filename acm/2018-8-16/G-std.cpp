#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
  
#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
  
namespace KDT {
    const double alpha=0.75;
    const int DIM=2;
    struct point {
        int A[DIM],max[DIM],min[DIM];
        int l,r; int size; int val,MAX;
        void init(int _val) {
            l=r=0; val=_val; initval();
        }
        void initval() {
            int i; size=1; MAX=val;
            REP(i,DIM) min[i]=max[i]=A[i];
        }
    } T[maxn]; int TOT;
    int Cur;
    bool cmp(int x,int y) {
        return T[x].A[Cur]<T[y].A[Cur];
    }
    void update(int x) {
        int i; T[x].initval();
        int l=T[x].l,r=T[x].r;
        if (l) T[x].size+=T[l].size,max_(T[x].MAX,T[l].MAX);
        if (r) T[x].size+=T[r].size,max_(T[x].MAX,T[r].MAX);
        REP(i,DIM) {
            if (l) {
                T[x].max[i]=max(T[x].max[i],T[l].max[i]);
                T[x].min[i]=min(T[x].min[i],T[l].min[i]);
            }
            if (r) {
                T[x].max[i]=max(T[x].max[i],T[r].max[i]);
                T[x].min[i]=min(T[x].min[i],T[r].min[i]);
            }
        }
    }
    int id[maxn],tot;
    void build(int &x,int l,int r,int cur) { //should have id
        x=0; if (l>r) return;
        int m=(l+r)/2; Cur=cur;
        nth_element(id+l,id+m,id+r+1,cmp);
        x=id[m];
        build(T[x].l,l,m-1,cur^1);
        build(T[x].r,m+1,r,cur^1);
        update(x);
    }
    void getid(int x) { //没有顺序=_=
        id[++tot]=x;
        if (T[x].l) getid(T[x].l);
        if (T[x].r) getid(T[x].r);
    }
    void rebuild(int &x,int cur) {
        tot=0; getid(x);
        build(x,1,tot,cur);
    }
    void insert(int &x,int now,int cur) {
        if (!x) {x=now; return;}
        Cur=cur;
        if (cmp(now,x)) insert(T[x].l,now,cur^1);
        else insert(T[x].r,now,cur^1);
        update(x);
        if (T[x].size*alpha+3<max(T[T[x].l].size,T[T[x].r].size))
            rebuild(x,cur);
    }
    void addnode(int &x,int px,int py,int val) {
        TOT++; T[TOT].A[0]=px; T[TOT].A[1]=py;
        T[TOT].init(val); insert(x,TOT,0);
    }
    int x1,y1;//check两个=_=
    int check(int x,int y) {
        return x<=x1&&y<=y1;
    }
    int ok(point &A) {
        return check(A.A[0],A.A[1]);
    }
    int allin(point &A) {
        return  A.max[0]<=x1&&A.max[1]<=y1;
    }
    int allout(point &A) {
        return  x1<A.min[0]||y1<A.min[1];
    }
    int query(int x) {
        if (!x) return 0;
        if (allin(T[x])) return T[x].MAX;
        if (allout(T[x])) return 0;
        int ret=0;
        if (ok(T[x])) max_(ret,T[x].val);
        if (T[x].size==1) return ret;
        max_(ret,query(T[x].l));
        max_(ret,query(T[x].r));
        return ret;
    }
}
vector<int> Aid[maxn],Bid[maxn],Cid[maxn];
int A[maxn],B[maxn],C[maxn],D[maxn];
int root[maxn];
inline int lowbit(int x) {
    return x&-x;
}
void update(int x,int y,int z,int val) {
    for (; x<=n; x+=lowbit(x)) KDT::addnode(root[x],y,z,val);
}
int query(int x,int y,int z) {
    int ret=0; KDT::x1=y; KDT::y1=z;
    for (; x; x-=lowbit(x)) max_(ret,KDT::query(root[x]));
    return ret;
}
struct node {
    int px,py,pz,val;
    bool operator < (const node &B) const{
        if (px!=B.px) return px<B.px;
        if (py!=B.py) return py<B.py;
        return pz<B.pz;
    }
};
vector<node> now;
map<node,int> MP;
int main() {
    int i,ans=0;
    scanf("%d",&n);
 // FOR(i,1,n) A[i]=(i+1)/2;
 // FOR(i,1,n) B[i]=(i+1)/2;
 // FOR(i,1,n) C[i]=(i+1)/2;
 // FOR(i,1,n) D[i]=(i+1)/2;
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) scanf("%d",&B[i]);
    FOR(i,1,n) scanf("%d",&C[i]);
    FOR(i,1,n) scanf("%d",&D[i]);
    FOR(i,1,n) Aid[A[i]].push_back(i);
    FOR(i,1,n) Bid[B[i]].push_back(i);
    FOR(i,1,n) Cid[C[i]].push_back(i);
//  startTimer();
    FOR(i,1,n) {
        now.clear();
        for (int px:Aid[D[i]])
            for (int py:Bid[D[i]])
                for (int pz:Cid[D[i]]) {
                    node nxt;
                    nxt.px=px; nxt.py=py; nxt.pz=pz;
                    nxt.val=query(px-1,py-1,pz-1)+1;
                    if (nxt.val>MP[nxt])
                        now.push_back(nxt);
                }
        for (auto t:now) {
            update(t.px,t.py,t.pz,t.val);
            max_(ans,t.val);
        }
    } printf("%d\n",ans);
//  printTimer();
}
