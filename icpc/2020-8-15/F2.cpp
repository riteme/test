
#include<iostream>
#include<cstdio>
 
#define mul(x,y) ((x)*(x)*(x)*(y))
#define abs(x) ((x)<0?0-(x):(x))
 
using namespace std;
 
const int maxn=50010;
const double eps = 1e-6;
 
double x[maxn],w[maxn];
 
int n;
 
double res(double s){
	double sum=0,p;
	for(int i=0;i<n;i++){
		p=abs(x[i]-s);
		sum+=mul(p,w[i]);
	}
	return sum;
} 
 
int main(){
	int t,tt;
	double sum;
	scanf("%d",&t);
	for(tt=1;tt<=t;tt++){
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%lf%lf",&x[i],&w[i]);
		double sum1,sum2,mid1,mid2,l=x[0],r=x[n-1];
		while(l<=r){
			mid1=(l+r)/2;
			mid2=(l+mid1)/2;
			sum1=res(mid1);
			sum2=res(mid2);
			if(mid2-eps<mid1 && mid1<mid2+eps) break;
			if(sum1>sum2) r=mid1; 
			else l=mid2;
		}
		printf("Case #%d: %.0lf\n",tt,min(sum1,sum2));
	}
	return 0;
}
