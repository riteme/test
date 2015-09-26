#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAGIC_NUMBER 6147

void ReadDigits(int n,int digits[]){
	for (int i=0;
	     n!=0;
	     i++) {
	    digits[i]=n%10;
		n/=10;
	}  // for
}

int MakeMaxNumber(int digits[],int n){
	int tmp=digits[3];
	for (int i=n-2;
	     i>=0;
	     i--) {
	    tmp*=10;
		tmp+=digits[i];
	}  // for

	cout<<tmp<<endl;
	return tmp;
}

int MakeMinNumber(int digits[],int n){
	int tmp=digits[3];
	for (int i=n-2;
	     i>=0;
	     i--) {
		if (digits[i]==0) {
		    tmp*=10;
		}else{
			tmp+=digits[i]*10;
		}
	}  // for

	cout<<tmp<<endl;
	return tmp;
}

int main(int argc, char const *argv[])
{
	int n;
	cin>>n;

	if (int(log10(n))!=3) {
	    cout<<"Input error"<<endl;
	    return 0;
	}

	int cnt=0;
	int digits[4];
	while (n!=MAGIC_NUMBER) {
		ReadDigits(n,digits);
		std::sort(std::begin(digits),std::end(digits));
		int maxN=MakeMaxNumber(digits,4);
		int minN=MakeMinNumber(digits,4);
		n=maxN-minN;
		cnt++;		
	}   // while

	cout<<cnt<<endl;

	return 0;
}