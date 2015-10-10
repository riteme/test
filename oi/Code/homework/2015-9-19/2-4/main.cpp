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

int fib(int a,int b,int n,int nmax){
	if (n>nmax) {
	    return a;
	}
	int tmp=b;
	b=a;
	a+=tmp;
	return fib(a,b,n+1,nmax);
}

int main(int argc, char const *argv[])
{
	auto io =StreamRedirect("fibonacci.in","fibonacci.out");

	int nmonth=0;
	while (cin>>nmonth) {
		cout<<fib(1,0,1,nmonth)<<endl;
	} // while
	
	
	return 0;
}