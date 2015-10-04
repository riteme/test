#include <cmath>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool IsPrime(const long long n){	
	if (n<=1) {
	    return false;
	}

	long long upBound=std::sqrt(n);

	for (long long i=2;
	     i<=upBound;
	     i++) {
	    if (n%i==0) {
	        return false;
	    }
	}  // for

	return true;
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);

	unordered_map<char,long long> countMap;
	string word;
	cin>>word;

	for (auto c : word) {
	    countMap[c]++;
	}  // foreach in word

	long long maxn,minn;
	for (auto &e : countMap) {
	    if (e.second>maxn) {
	        maxn=e.second;
	    }else if(e.second<minn){
	    	minn=e.second;
	    }
	}  // foreach in countMap

	auto num=maxn-minn;
	if (IsPrime(num)) {
	    cout<<"Lucky Word"<<endl;
	    cout<<num<<endl;
	}else{
		cout<<"No Answer"<<endl;
		cout<<0<<endl;
	}
	
	return 0;
}
