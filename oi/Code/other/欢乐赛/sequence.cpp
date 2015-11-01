#include <climits>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ntype;

ntype FindMaxCrossSubarray(ntype *d,int l,int m,int r){
	ntype result=0;
	
	ntype sum=0;
	for(int i=m;i>=l;i--){
		sum+=d[i];
		
		if(sum>result)
			result=sum;
	}
	
	sum=result;
	for(int i=m+1;i<=r;i++){
		sum+=d[i];
		
		if(sum>result){
			result=sum;
		}
	}
	
	return result;
} 

ntype FindMaxSubarray(ntype *d,int l,int r){
	if(r<=l) return d[l];
	
	int m=(l+r)/2;
	int lmax=FindMaxSubarray(d,l,m);
	int rmax=FindMaxSubarray(d,m+1,r);
	int mmax=FindMaxCrossSubarray(d,l,m,r);
//	printf("l: %d, m: %d, r: %d\n",lmax,mmax,rmax); 
	
	return std::max(std::max(lmax,rmax),mmax);
}

ntype *data;
ntype *d;

int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	
	int n;
	scanf("%d",&n);
	
//	ntype data[n];
//	ntype d[n];
	data=new ntype[n];
	d=new ntype[n];
	scanf("%lld",data);
	for(int i=1;i<n;i++){
		scanf("%lld",&data[i]);
	}
	for(int i=1;i<n;i++){
		d[i]=std::max(data[i-1],data[i]);
	}
	
//	for(int i=1;i<n;i++){
//		printf("%d ",d[i]);
//	}
//	printf("\n");
	
	printf("%lld",FindMaxSubarray(d,1,n-1));
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
