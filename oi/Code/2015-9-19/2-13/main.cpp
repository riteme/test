#include <iostream>
#include <vector>
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

vector<int> fact(int n){
	vector<int> vec;
	int sqrted=sqrt(n);

	for (int i=2;
	     i<=sqrted;
	     i++) {
	    while (n%i==0) {
	    	vec.push_back(i);
	    	n/=i;
	    } // while
	}  // for
	vec.push_back(n);
	
	return vec;
}

int main(int argc, char const *argv[])
{
	auto io=StreamRedirect("divisor.in","divisor.out");

	int n;
	while (cin>>n) {
		auto v=fact(n);
		for (auto beg=v.begin();
		     beg!=v.end();
		     beg++) {
		    cout<<*beg<<(beg==v.end()-1?"":"*");
		}  // for
		cout<<endl;
	} // while

	return 0;
}