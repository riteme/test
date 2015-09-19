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

unsigned count(long long n,unsigned cnt=0){
	if(n!=1){
		if (n%2==0) {
		    n/=2;
		}else{
			n=n*3+1;
		}
		count(n,cnt+1);
	}else{
		return cnt;
	}
}

int main(int argc, char const *argv[])
{
	auto io=StreamRedirect("number.in","number.out");
	
	long long n=1;
	while (cin>>n) {
		cout<<count(n)<<endl;
	} // while

	return 0;
}