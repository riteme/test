#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

bool cmp(const double a,const double b){
	return a>b;
}

double *d;
double *r;

int main(){
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	
	int n;
	scanf("%d",&n);
	
//	double d[n+1];
//	double r[n+1];
	d=new double[n+1];
	r=new double[n+1];
	double sum=0.0;
	for(int i=1;i<=n;i++){
		int tmp;
		scanf("%d",&tmp);
		
		d[i]=double(tmp);
		r[i]=d[i];
		sum+=d[i];
	}
	
	std::sort(d+1,d+n+1);
	std::sort(r+1,r+n+1,cmp);
	
	double m=n*sum;
	
	double result=0.0;
	for(int i=1;i<=n;i++){
		double ratio=((r[i] / sum) * m)/sum;
		result+=d[i] * (ratio * ratio);
	}
	
	printf("%.4f",result);
	
	fclose(stdin);
	fclose(stdout);
	return 0; 
}
