#include <iostream>

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

int gcd(int p,int q){
	if (q==0) {
	    return p;
	}
	int r=p%q;
	return gcd(q,r);
}

int min(int p,int q){
	if (p<q) {
	    swap(p,q);
	}

	int i=1;
	for (;
	     (p*i)%q!=0;
	     i++) {
	    
	}  // for
	
	return p*i;
}

int main(int argc, char const *argv[])
{
	auto io=StreamRedirect("math.in","math.out");

	int a,b;
	while (cin>>a>>b) {
		cout<<gcd(a,b)<<' '<<min(a,b)<<endl;
	} // while
	

	return 0;
}