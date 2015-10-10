#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAGIC_NUMBER 6174

void ReadDigits(int n,int digits[]){
	for (int i=0;
	     i<4;
	     i++) {
	    digits[i]=n%10;
		n/=10;
	}  // for
}

int MakeMaxNumber(int digits[],int n){
	int tmp=0;
	for (int i=n-1;
	     i>=0;
	     i--) {
	    tmp*=10;
		if (digits[i]!=0) {
			tmp+=digits[i];
		}
	}  // for

	return tmp;
}

int MakeMinNumber(int digits[],int n){
	int tmp=0;
	for (int i=0;
	     i<n;
	     i++) {
		tmp*=10;
		tmp+=digits[i];
	}  // for

	return tmp;
}

int main(int argc, char const *argv[])
{
	int n;
	cin>>n;

	if (int(log10(n))!=3 || n%1111==0) {
	    cout<<"Input error"<<endl;
	    return 0;
	}

	int cnt=0;
	int digits[4];
	while (n!=MAGIC_NUMBER&&cnt<10) {
		ReadDigits(n,digits);
		std::sort(std::begin(digits),std::end(digits));

		int maxN=MakeMaxNumber(digits,4);
		int minN=MakeMinNumber(digits,4);

		n=maxN-minN;
		cnt++;

		cout<<maxN<<" - "<<minN<<" = "<<n<<endl;
	}   // while

	cout<<cnt<<endl;

	return 0;
}