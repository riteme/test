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

int main(int argc, char const *argv[])
{
	auto io=StreamRedirect("toss.in","toss.out");

	int m,n;
	while (cin>>m>>n) {
		cout<<gcd(m,n)<<endl;
	} // while
	

	return 0;
}