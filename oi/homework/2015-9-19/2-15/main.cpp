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

long long mut(long long n,long long result=1){
	if(n<=1){
		return result;
	}
	result*=n;
	return mut(n-1,result);
}

int main(int argc, char **argv) {
    auto io=StreamRedirect("zero.in","zero.out");

	long long n;
	while (cin>>n) {
		long long m=mut(n);
		int cnt=0;
		// cout<<m<<endl;
		while (m%10==0) {
			cnt++;
			m/=10;
		} // while
		cout<<m%10<<' '<<cnt<<endl;
	} // while
	

    return 0;
}  // function main
