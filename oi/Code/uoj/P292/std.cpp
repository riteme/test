#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#define LL long long
using namespace std;
int gi() {
	int w=0;bool q=1;char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}
LL gL() {
	LL w=0;bool q=1;char c=getchar();
	while ((c<'0'||c>'9') && c!='-') c=getchar();
	if (c=='-') q=0,c=getchar();
	while (c>='0'&&c <= '9') w=w*10+c-'0',c=getchar();
	return q? w:-w;
}
inline int gc() { char c; while ((c=getchar())!='0'&&c!='1'); return c-'0'; }
const int N=1<<19|1;
LL t1[N],t2[N],T1[N],T2[N];
LL F[N],G[N],S,SS;
int a[N],b[N],c[N];
inline LL solve(int n,int uni,int len,LL m,LL lim,LL start,LL Q) {
	if (lim==-1) return 0;
	int i,j,del,top=0;bool st[60],R;LL all=n,*f=F,*g=G,*d1,*d2,Lim[60];
	__int128 o=start<<(uni+1),p;
	if (lim<=n) {
		a[all=0]=1;Q>>=uni-len;
		for (i=0;i<=n;i++) b[i]=start&1,start>>=1;
		while (m) {
			if (m&1) {
				for (i=all+n;i>=0;i--) c[i]=0;
				for (i=0;i<=all;i++) for (j=0;j<=n;j++) c[i+j]^=a[i]&&b[j];
				all=min(all+n,lim);
				for (i=0;i<=lim;i++) a[i]=c[i];
			}
			for (i=n<<1;i>n;i--) b[i]=0;
			for (i=n<<1;i>=0;i--) b[i]=i&1?0:b[i>>1];
			n=min(n<<1,(int)lim);m>>=1;
		}
		lim=0;
		for (i=0;i<=all;i++,lim+=p==Q) for (p=j=0;j<=len;j++) p=p<<1|(i-j<0?0:a[i-j]);
		return lim;
	}
	Lim[1]=lim;for (i=2;i<60;i++) Lim[i]=max((Lim[i-1]+1)>>1,(LL)uni);
	memset(f,0,sizeof(F));
	for (i=0;i<=all;i++) f[start<<(uni-i)&S]++;
	while (m>1) st[++top]=m&1,m>>=1;
	while (top) {
		swap(f,g);lim=Lim[top];
		memset(f,0,sizeof(F));
		(R=st[top--])?(d1=T1,d2=T2):(d1=t1,d2=t2);
		for (i=0;i<1<<(uni+1);i++) if (g[i]) f[d1[i]]+=g[i],f[d2[i]]+=g[i];
		p=0;for (i=0;i<=(uni<<1|1);i++) p|=(o>>i&1)<<(i<<1);
		all=(all<<1)+(R?uni:0);
		del=max(0LL,all-lim);
		if (R) {
			for (o=i=0;i<=uni;i++) if (start>>i&1) o^=p<<i;
			for (i=1;i<=uni;i++) f[o>>(((uni<<2)+3)-i)&S]++;
			for (i=0;i<del;i++)
				f[(o>>((uni<<2)+2-i))&S]--;
			(o>>=uni*3+1-del)&=SS;
		} else {
			for (i=0;i<del;i++)
				f[(p>>(uni*3+2-i))&S]--;
			o=p>>((uni<<1|1)-del)&SS;
		}
		f[0]--;
		all-=del;
	}
	for (lim=i=0;i<1<<(uni-len);i++) lim+=f[i|Q];
	return lim;
}
int main()
{
	int T=gi(),i,n,len,k,uni;LL m,L,R,start,p,to,Q,s;
	while (T--) {
		n=gi(),m=gL();
		len=gi()-1,R=n*m+1-gL(),L=n*m+1-gL();
		uni=max(n,len);S=(1<<(uni+1))-1;SS=(1ULL<<((uni+1)<<1))-1;
		for (i=0,start=0;i<=n;i++) start|=gc()<<(uni-i);
		for (Q=i=0;i<=len;i++) Q|=gc()<<(uni-i);
		for (s=0;s<1<<(uni+1);s++) {
			for (to=0,k=0;k<=uni;k++) to|=(s>>k&1)<<(k<<1);
			t1[s]=to>>(uni-1)&S;
			t2[s]=to>>uni;
			p=to;to=0;
			for (i=0;i<=uni;i++) if (start>>i&1) to^=p<<i;
			T2[s]=to>>uni&S;
			T1[s]=to>>(uni-1)&S;
		}
		printf("%lld\n",R-L+1<len?0:(solve(n,uni,len,m,R,start,Q)-solve(n,uni,len,m,L-1+len,start,Q)));
	}
	return 0;
}
