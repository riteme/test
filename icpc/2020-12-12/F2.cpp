#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef double db;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;

typedef vector <int> poly;
typedef pair <int,int> pii;

#define	fi first
#define se second
#define rez resize
#define pp pop_back
#define pb push_back
#define mkp make_pair

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define drep(i,l,r) for(int i=r;i>=l;--i)

#define CLEAR(x) memset((x),0,sizeof((x)))
#define COPY(x,y) memcpy((x),(y),sizeof((x)))

const int inf=1e9+7;

template <class T> inline T read() {
	char ch; bool flag=0; T x=0;
	while(ch=getchar(),!isdigit(ch)) if(ch=='-') flag=1;
	while(isdigit(ch)) x=x*10+ch-48,ch=getchar();
	return flag?-x:x;
}
struct {
	inline operator ll() {return read<ll>();}

	inline operator int() {return read<int>();}
	inline operator bool() {return read<bool>();}
	inline operator double() {double _tmp; return scanf("%lf",&_tmp),_tmp;}

	template <class T> inline void operator () (T &x) {x=*this;}
	template <class T,class ...A> inline void operator () (T &x,A &...a)
	{x=*this,this->operator()(a...);}
} IN;

template <class T> inline void chkmax(T &x,T y) {if(x<y) x=y;}
template <class T> inline void chkmin(T &x,T y) {if(x>y) x=y;}

// }}}

const int N=3e2+5;

int n,m;
int b[N],a[N],mat[N][N];

inline void work(int l,int r) {
	if((r - l + 1) % 2 == 1) {
		rep(i, l, r) {
			int flag=((r - i + 1) & 1);
			rep(j,1,n) if(((j-flag)&1)&&a[i]) mat[j][i]=1,--a[i];
		}
		return;
	}
	int now = 1, flag = 0;
	rep(i, l, r) {
		if(now == 0 && flag == 0 && i != l && b[i] + b[i - 1] <= n / 2) {
			now ^= 1, flag = 1;
			drep(j,1,n) if(((j-now)&1)&&a[i]) mat[j][i]=1,--a[i];
		}
		else if(now == 1 && flag == 0 && i != l && b[i] + b[i - 1] <= n / 2 + 1) {
			now ^= 1, flag = 1;
			drep(j,1,n) if(((j-now)&1)&&a[i]) mat[j][i]=1,--a[i];
		}
		else {
			rep(j,1,n) if(((j-now)&1)&&a[i]) mat[j][i]=1,--a[i];
		}
		now ^= 1;
	}
	if(flag == 0) puts("NO"), exit(0);
}

inline void work_l(int r) {
	rep(i, 1, r) {
		int flag=((r - i + 1) & 1);
		rep(j,1,n) if(((j-flag)&1)&&a[i]) mat[j][i]=1,--a[i];
	}
}

inline void work_r(int r) {
	rep(i, r, m) {
		int flag=((i - r + 1) & 1);
		rep(j,1,n) if(((j-flag)&1)&&a[i]) mat[j][i]=1,--a[i];
	}
}

int main() {
	//freopen("data.in", "r", stdin);
	//freopen("data.out", "w", stdout);
	IN(n,m);
	rep(i,1,m) IN(a[i]), b[i] = a[i];
	rep(i,1,m) if(a[i]>(n+1)/2) return puts("No"),0;

	if(n&1) {
		int las=0;
		rep(i,1,m) {
			if(a[i]==(n+1)/2) {
				if(las&&las+1==i) return puts("NO"),0;
				if(las == 0) work_l(i-1);
				else if(i!=1) work(las+1,i-1);
				las=i;
				rep(j,1,n) if(j&1) mat[j][i]=1;
			}
		}
		if(las+1<=m) work_r(las+1);
	} else {
		rep(i,1,m) {
			int flag=(i&1);
			rep(j,1,n) if(((j-flag)&1)&&a[i]) mat[j][i]=1,--a[i];
		}
	}
	puts("Yes");
	rep(i,1,n) {rep(j,1,m) printf("%d",mat[i][j]); puts("");}
    return 0;
}