#include <iostream>
#include <cmath>

using namespace std;

typedef FILE* FilePtr;

class StreamRedirect
{
public:
	StreamRedirect(const std::string &in,const std::string &out){
		if (!in.empty()) {    
		freopen(in.data(),"r",stdin);
		}
		if (!out.empty()) {
		freopen(out.data(),"w",stdout);
		}
	}
	~StreamRedirect(){
		fclose(stdin);
		fclose(stdout);
	}
};

long long mut(long long n,long long result=1){
	if (n<=1) {
	    return result;
	}
	result*=n;
	return mut(n-1,result);
}

long long fact(long long n,long long result=0){
	if(n<=1){
		return result+1;
	}
	result+=mut(n);
	return fact(n-1,result);
}

int main(int argc, char const *argv[])
{
	auto ui=StreamRedirect("fact.in","fact.out");

	long long n;
	while (cin>>n) {
		cout<<fact(n)%1000000<<endl;	
	} // while
	
	return 0;
}