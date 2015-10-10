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

bool IsPrime(long long num){
	long long sqrted=sqrt(num);

	for (int i=2;
	     i<=sqrted;
	     i++) {
	    if (num%i==0) {
	        return false;
	    }
	}  // for
	
	return true;
}

int main(int argc, char **argv) {
	auto io=StreamRedirect("double.in","double.out");

	int m;
	while (cin>>m) {
		for (int n=m-2;
		     n>=2;
		     n--) {
		    if (IsPrime(n) && IsPrime(n+2)) {
		        cout<<n<<' '<<n+2<<endl;
		        break;
		    }
		}  // for
	} // while

    return 0;
}  // function main
