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

bool IsPrime(int n){

	if (n<4) {
	    return true;
	}

	int sqrted=sqrt(n);
	for (int i=2;
	     i<=sqrted;
	     i++) {
	    if (n%i==0) {
	        return false;
	    }
	}  // for
	    return true;
	
}

int rotate(int n){
	return (n%10)*10+n/10;
}

int main(int argc, char const *argv[])
{
	auto io=StreamRedirect("","prime.out");

	for (int i=10;
	     i<=99;
	     i++) {
	    if (IsPrime(i)&&IsPrime(rotate(i))) {
	        cout<<i<<' ';
	    }
	}  // for

	return 0;
}