#include<cassert>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int,int> pa;
typedef double db;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define rep2(i,a,b) for(int (i)=(a);(i)<(b);(i)++)
#define per(i,a,b) for(int (i)=(a);(i)>=(b);(i)--)
#define Rep(p,x) for(int (p)=head[(x)];(p);(p)=nxt[(p)])
#define Rep2(p,x) for(int (p)=cur[(x)];(p);(p)=nxt[(p)])
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define mp make_pair
#define pb push_back
#define w1 first
#define w2 second
#define SZ(x) (int((x).size()))
template<class T>inline void rread(T&num){
	num=0;T f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
	num*=f;
}
const int base=2e5;
struct Map{
	int a[base*2+5];
	inline Map(){
		memset(a,0,sizeof a);
	}
	inline void Insert(ll x){
		if(x<-base||x>base)return;
		x+=base;
		a[x]++;
	}
	inline int Query(ll x){
		if(x<-base||x>base)return 0;
		x+=base;
		return a[x];
	}
}MapB,MapC;
const ll inf=1e15;
struct Point{
	ll x,y;
	inline Point(){x=y=inf;}
	inline Point(ll _x,ll _y){x=_x;y=_y;}
	inline friend Point operator+(Point A,Point B){return Point(A.x+B.x,A.y+B.y);}
	inline friend Point operator-(Point A,Point B){return Point(A.x-B.x,A.y-B.y);}
	inline friend ll operator*(Point A,Point B){return A.x*B.y-B.x*A.y;}
	inline friend bool operator!(Point A){return (A.x==inf)&&(A.y==inf);}
	inline friend bool operator!=(Point A,Point B){return (A.x!=B.x)||(A.y!=B.y);}
};
inline ll GetGcd(ll x,ll y){
	if(!x)return y;
	return GetGcd(y%x,x);
}
#include<iostream>
struct Line{
	Point S,E;
	inline Line(){S=E=Point(inf,inf);}
	inline Line(Point _S,Point _E){S=_S;E=_E;}
	inline friend Line operator+(Line A,Point B){return Line(A.S+B,A.E+B);}
	inline friend bool Par(Line A,Line B){return ((A.E.y-A.S.y)*(B.E.x-B.S.x))==((B.E.y-B.S.y)*(A.E.x-A.S.x));}
	inline friend pair<Point,bool> Inter(Line A,Line B){
		Point Res;
		ll S1=(B.S-A.S)*(A.E-A.S),S2=(A.E-A.S)*(B.E-A.S);
		ll fracA=S1,fracB=(S1+S2),d=GetGcd(fracA,fracB);
		fracA/=d;fracB/=d;
		if(((B.E.x-B.S.x)*fracA)%fracB)return mp(Res,0);
		Res.x=B.S.x+((B.E.x-B.S.x)*fracA)/fracB;
		if(((B.E.y-B.S.y)*fracA)%fracB)return mp(Res,0);
		Res.y=B.S.y+((B.E.y-B.S.y)*fracA)/fracB;
		return mp(Res,1);
	}
	inline friend bool CheckSame(Line A,Line B){
		ll fracA1=A.E.x*A.S.y-A.E.y*A.S.x,fracA2=A.E.x-A.S.x;
		ll fracB1=B.E.x*B.S.y-B.E.y*B.S.x,fracB2=B.E.x-B.S.x;
		return (fracA1*fracB2)==(fracA2*fracB1);
	}
	inline friend void print(Line A){
		cerr<<"("<<A.S.x<<","<<A.S.y<<")"<<","<<"("<<A.E.x<<","<<A.E.y<<")"<<endl;
	}
}LineB,LineC,LA;
vector<Point>LineA;
int NA,NB,NC;
ll CntA[base*4+5],CntB[base*4+5],CntC[base*4+5],Res[base*4+5];
ll Ans;
const ld pi=acos(-1.0);
namespace FFT{
	const int maxn=2e6;
	struct complex{
		ld r,i;
		inline complex(){r=i=0;}
		inline complex(ld _r,ld _i){r=_r;i=_i;}
		inline friend complex operator+(complex a,complex b){return complex(a.r+b.r,a.i+b.i);}
		inline friend complex operator-(complex a,complex b){return complex(a.r-b.r,a.i-b.i);}
		inline friend complex operator*(complex a,complex b){return complex(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
		inline friend complex operator!(complex a){return complex(a.r,-a.i);}
	}p[maxn],q[maxn],c[maxn];
	int n,l,bitl,N,bitrev[maxn];
	inline void init(int n,int m){
		n++;m++;l=n+m-1;
		for(N=1,bitl=0;N<l;N<<=1,bitl++);
		rep2(i,0,N)bitrev[i]=(bitrev[i>>1]>>1)|((i&1)<<(bitl-1));
	}
	inline void fft(complex *a,int n,int flag){
		rep2(i,0,n)if(i<bitrev[i])swap(a[i],a[bitrev[i]]);
		for(int i=1;i<n;i<<=1){
			complex wn(cos(pi/i),flag*sin(pi/i));
			for(int j=0;j<n;j+=i<<1){
				complex w(1,0);
				rep2(k,0,i){
					complex x=a[j+k],y=a[j+k+i]*w;
					a[j+k]=x+y;a[j+k+i]=x-y;
					w=w*wn;
				}
			}
		}
		if(flag==-1)rep2(i,0,n)a[i].r/=n;
	}
	inline void convo(ll *A,int n,ll *B,int m,ll *C){
		init(n,m);
		rep(i,0,n)p[i]=complex(A[i],B[i]);
		fft(p,N,1);
		q[0]=!p[0];rep2(i,1,N)q[i]=!p[N-i];
		rep2(i,0,N)c[i]=(p[i]+q[i])*(p[i]-q[i])*complex(0,-0.25);
		fft(c,N,-1);
		rep2(i,0,l)C[i]=ll(c[i].r+0.5);
	}
}
inline void Judge(){
	freopen("par.in","r",stdin);
	freopen("par.out","w",stdout);
}
int main(){
	rread(NA);rread(NB);rread(NC);
	rep(i,1,NA){
		int x,y;rread(x);rread(y);
		CntA[x+base]++;
		if(!LA.S)LA.S=Point(x,y);
		else if(Point(x,y)!=LA.S)LA.E=Point(x,y);
		LineA.pb(Point(x,y));
	}
	rep(i,1,NB){
		int x,y;rread(x);rread(y);
		CntB[x+base]++;
		if(!LineB.S)LineB.S=Point(x,y);
		else if(Point(x,y)!=LineB.S)LineB.E=Point(x,y);
		MapB.Insert(x);
	}
	rep(i,1,NC){
		int x,y;rread(x);rread(y);
		x<<=1;y<<=1;
		CntC[x+base]++;
		if(!LineC.S)LineC.S=Point(x,y);
		else if(Point(x,y)!=LineC.S)LineC.E=Point(x,y);
		MapC.Insert(x);
	}
	if(Par(LA,LineB)&&Par(LA,LineC)){
		Line NowB=LineB+LineA[0];
		if(CheckSame(NowB,LineC)){
			FFT::convo(CntA,base*2,CntB,base*2,Res);
			rep(i,0,base*2)Ans+=CntC[i]*Res[i+base];
			return printf("%lld\n",Ans),0;
		}else return puts("0"),0;
	}
	rep2(i,0,SZ(LineA)){
		Line NowB=LineB+LineA[i];
		if(Par(NowB,LineC)){
			if(CheckSame(NowB,LineC)){
				rep(j,-base,base)
					Ans+=1ll*MapB.Query(j)*MapC.Query(j+LineA[i].x);
			}
		}else{
			pair<Point,bool>WRT=Inter(NowB,LineC);
			if(WRT.w2)Ans+=1ll*MapB.Query(WRT.w1.x-LineA[i].x)*MapC.Query(WRT.w1.x);
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
