#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define mod 1000000007
#define inv 500000004
#define N 70005
using namespace std;

int n,m,cnt,a[N],c[N]; bool vis[N];
int ksm(int x,int y){
	int t=1; for (; y; y>>=1,x=(ll)x*x%mod) if (y&1) t=(ll)t*x%mod;
	return t;
}
void trs(int l,int r){
	if (l==r) return; int mid=(l+r)>>1,i,j,x;
	trs(l,mid); trs(mid+1,r);
	for (i=l,j=mid+1; i<=mid; i++,j++){
		x=(a[i]+a[j])%mod;
		a[i]=(a[i]-a[j]+mod)%mod; a[j]=x;
	}
}
void rsto(int l,int r){
	if (l==r) return; int mid=(l+r)>>1,i,j,x;
	for (i=l,j=mid+1; i<=mid; i++,j++){
		x=(ll)(a[j]-a[i]+mod)*inv%mod;
		a[i]=(ll)(a[i]+a[j])*inv%mod; a[j]=x;
	}
	rsto(l,mid); rsto(mid+1,r);
}
int main(){
	int i,j;
	for (i=2; i<=50000; i++){
		if (!vis[i]) c[++cnt]=i;
		for (j=1; j<=cnt && i*c[j]<=50000; j++){
			vis[i*c[j]]=1;
			if (!(i%c[j])) break;
		}
	}
	c[cnt+1]=50001;
	while (~scanf("%d%d",&n,&m)){
		memset(a,0,sizeof(a));
		for (i=1; c[i]<=m; i++) a[c[i]]=1;
		j=1; while (j<=m) j<<=1; j--;
		trs(0,j);
		for (i=0; i<=j; i++) a[i]=ksm(a[i],n);
		rsto(0,j);
		printf("%d\n",a[0]);
	}
	return 0;
}
