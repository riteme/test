// easy
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	double x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;

	double result=sqrt(pow(fabs(x1-x2),2)+pow(fabs(y1-y2),2));
	printf("%.3f\n", result);

	return 0;
}
