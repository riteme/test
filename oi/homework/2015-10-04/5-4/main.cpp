#include <cmath>
#include <cfloat>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

bool IsPalindromic(int n){
	string numstr=to_string(n);
	string left=numstr.substr(0,numstr.size()/2);
	string right=numstr.substr(numstr.size()/2+numstr.size()%2,numstr.size()/2);
	std::reverse(right.begin(),right.end());

	return left==right;
}

bool IsSqrted(int n){
	double sn=std::sqrt(n);
	return sn==double((int)sn);
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	for (int i=10;
	     i<=999999;
	     i++) {
	    if (IsSqrted(i)&&IsPalindromic(i)) {
	        cout<<i<<' ';
	    }
	}  // for
	cout<<endl;

	return 0;
}